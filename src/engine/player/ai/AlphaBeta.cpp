#include <engine/player/ai/AlphaBeta.hpp>
#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/player/Player.hpp>

namespace move_sorter
{

	int compare_moves(const std::shared_ptr<move> &m1, const std::shared_ptr<move> &m2)
	{
		if (board_utils::king_threat(m1) && !board_utils::king_threat(m2))
			return true;
		if (!board_utils::king_threat(m1) && board_utils::king_threat(m2))
			return false;

		if (m1->is_castling_move() && !m2->is_castling_move())
			return true;
		if (!m1->is_castling_move() && m2->is_castling_move())
			return false;

		return board_utils::mvv_lva(m1.get()) > board_utils::mvv_lva(m2.get());
	}

	std::vector<std::shared_ptr<move>> sort(const std::vector<std::shared_ptr<move>> &moves)
	{
		std::vector<std::shared_ptr<move>> sorted_moves = moves;
		std::stable_sort(sorted_moves.begin(), sorted_moves.end(), compare_moves);
		return sorted_moves;
	}
} // namespace move_sorter

alpha_beta::alpha_beta(const unsigned sd) : search_depth_(sd)
{
}

std::shared_ptr<move> alpha_beta::execute(std::shared_ptr<board> b)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
	std::shared_ptr<player> current_player = b->get_current_player();
	std::shared_ptr<move> best_move = move::get_null_move();
	int highest_seen_value = std::numeric_limits<int>::min(),
		lowest_seen_value = std::numeric_limits<int>::max(),
		move_counter = 1,
		number_of_moves = b->get_current_player()->get_legal_moves().size(),
		current_value;
	std::string s;

	std::cout << current_player->stringify() << " THINKING with depth = " << search_depth_ << std::endl;

	for (std::shared_ptr<move> m : move_sorter::sort(b->get_current_player()->get_legal_moves()))
	{
		move_transition transition = current_player->make_move(m);
		quiescence_count_ = 0;
		if (transition.get_move_status() == move_status::done)
		{
			std::chrono::time_point<std::chrono::high_resolution_clock> candidate_move_start_time = std::chrono::high_resolution_clock::now();
			current_value = current_player->get_player_alliance() == alliance::white
								? min(transition.get_transition_board(), search_depth_ - 1, highest_seen_value, lowest_seen_value)
								: max(transition.get_transition_board(), search_depth_ - 1, highest_seen_value, lowest_seen_value);
			if (current_player->get_player_alliance() == alliance::white && current_value > highest_seen_value)
			{
				highest_seen_value = current_value;
				best_move = m;
				if (transition.get_transition_board()->get_black_player()->is_is_checkmate())
					break;
			}
			else if (current_player->get_player_alliance() == alliance::black && current_value < lowest_seen_value)
			{
				lowest_seen_value = current_value;
				best_move = m;
				if (transition.get_transition_board()->get_white_player()->is_is_checkmate())
					break;
			}
			s = "\tAlphaBeta(d:" + std::to_string(search_depth_) + ") -> m: (" + std::to_string(move_counter) + '/' + std::to_string(number_of_moves) + ") " + m->stringify() + ", best: " + best_move->stringify() + ' ' + score(current_player, highest_seen_value, lowest_seen_value) + " q: " + std::to_string(quiescence_count_) + ", t: " + std::to_string(static_cast<int>((std::chrono::high_resolution_clock::now() - candidate_move_start_time).count() / 1000)) + "us";
		}
		else
			s = "\tAlphaBeta(d:" + std::to_string(search_depth_) + ") -> m: (" + std::to_string(move_counter) + '/' + std::to_string(number_of_moves) + ") " + m->stringify() + " is illegal! Best: " + best_move->stringify();
		std::cout << s << std::endl;
		move_counter++;
	}
	auto execution_time = (std::chrono::high_resolution_clock::now() - start_time).count() / 1000000; // Convert nanoseconds to milliseconds
	std::string result = b->get_current_player()->stringify() + " selects " + best_move->stringify() + ", # boards evaluated = " + std::to_string(boards_evaluated_) + ", time taken = " + std::to_string(execution_time) + "ms, rate = " + std::to_string(1000 * boards_evaluated_ / execution_time) + " boards/s";
	std::cout << result << std::endl;
	return best_move;
}

std::string alpha_beta::score(std::shared_ptr<player> cp, int highest_seen_value, int lowest_seen_value)
{
	std::string s = "[score: ";
	if (cp->get_player_alliance() == alliance::white)
		s += std::to_string(highest_seen_value) + ']';
	else
		s += std::to_string(lowest_seen_value) + ']';
	return s;
}

int alpha_beta::quiescence(std::shared_ptr<board> b, int depth, int alpha, int beta)
{
	int stand_pat = standard_board_evaluator::evaluate(*b, depth);
	if (stand_pat >= beta)
		return beta;
	if (alpha < stand_pat)
		alpha = stand_pat;
	std::vector<std::shared_ptr<move>> attack_moves, moves = b->get_current_player()->get_legal_moves();
	std::copy_if(moves.begin(), moves.end(), std::back_inserter(attack_moves), [](std::shared_ptr<move> m) -> bool
				 { return m->is_attack(); });
	for (std::shared_ptr<move> m : move_sorter::sort(attack_moves))
	{
		move_transition transition = b->get_current_player()->make_move(m);
		if (transition.get_move_status() == move_status::done)
		{
			int score = -quiescence(transition.get_transition_board(), depth - 1, -beta, -alpha);
			if (score >= beta)
				return beta;
			if (score > alpha)
			{
				quiescence_count_++;
				alpha = score;
			}
		}
	}
	return alpha;
}

int alpha_beta::min(std::shared_ptr<board> b, int depth, int alpha, int beta)
{
	if (depth == 0 || board_utils::game_over(b.get()))
	{
		boards_evaluated_++;
		return standard_board_evaluator::evaluate(*b, depth) /* + quiescence(b, depth, alpha, beta) */;
	}
	int lowest_seen_value = beta;
	for (std::shared_ptr<move> m : move_sorter::sort(b->get_current_player()->get_legal_moves()))
	{
		move_transition transition = b->get_current_player()->make_move(m);
		if (transition.get_move_status() == move_status::done)
		{
			lowest_seen_value = std::min(lowest_seen_value, max(transition.get_transition_board(), depth - 1, alpha, lowest_seen_value));
			if (lowest_seen_value <= alpha)
				return alpha;
		}
	}
	return lowest_seen_value;
}

int alpha_beta::max(std::shared_ptr<board> b, int depth, int alpha, int beta)
{
	if (depth == 0 || board_utils::game_over(b.get()))
	{
		boards_evaluated_++;
		return standard_board_evaluator::evaluate(*b, depth) /* + quiescence(b, depth, alpha, beta) */;
	}
	int highest_seen_value = alpha;
	for (std::shared_ptr<move> m : move_sorter::sort(b->get_current_player()->get_legal_moves()))
	{
		move_transition transition = b->get_current_player()->make_move(m);
		if (transition.get_move_status() == move_status::done)
		{
			highest_seen_value = std::max(highest_seen_value, min(transition.get_transition_board(), depth - 1, highest_seen_value, beta));
			if (highest_seen_value >= beta)
				return beta;
		}
	}
	return highest_seen_value;
}