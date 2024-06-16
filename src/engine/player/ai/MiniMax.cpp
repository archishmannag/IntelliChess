#include <engine/player/ai/MiniMax.hpp>
#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/board/Board.hpp>
#include <engine/player/Player.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>

mini_max::mini_max(unsigned int sd)
	: search_depth_(sd)
{
}

std::shared_ptr<move> mini_max::execute(std::shared_ptr<board> b)
{
	const auto start_time = std::chrono::high_resolution_clock::now();
	std::shared_ptr<move> best_move = nullptr;
	int highest_seen_value = std::numeric_limits<int>::min(),
		lowest_seen_value = std::numeric_limits<int>::max(),
		current_value;

#ifdef DEBUG_BUILD
	std::cout << b->get_current_player()->stringify() << " THINKING with depth = " << search_depth_ << std::endl;
#endif // DEBUG_BUILD

	std::vector<std::shared_ptr<move>> moves = b->get_current_player()->get_legal_moves();
	for (auto move : moves)
	{
		move_transition transition = b->get_current_player()->make_move(move);
		if (transition.get_move_status() == move_status::done)
		{
			current_value = b->get_current_player()->get_player_alliance() == alliance::white
								? min(transition.get_transition_board(), search_depth_ - 1)
								: max(transition.get_transition_board(), search_depth_ - 1);

			if (b->get_current_player()->get_player_alliance() == alliance::white && highest_seen_value <= current_value)
			{
				highest_seen_value = current_value;
				best_move = move;
			}
			else if (b->get_current_player()->get_player_alliance() == alliance::black && current_value <= lowest_seen_value)
			{
				lowest_seen_value = current_value;
				best_move = move;
			}
		}
	}

	const auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);

	return best_move;
}

int mini_max::min(std::shared_ptr<board> b, unsigned int d)
{
	if (d == 0)
		return standard_board_evaluator::evaluate(*b, d);

	int lowest_seen_value = std::numeric_limits<int>::max();
	for (auto move : b->get_current_player()->get_legal_moves())
	{
		move_transition transition = b->get_current_player()->make_move(move);
		if (transition.get_move_status() == move_status::done)
		{
			int current_value = max(transition.get_transition_board(), d - 1);
			if (current_value <= lowest_seen_value)
				lowest_seen_value = current_value;
		}
	}
	return lowest_seen_value;
}

int mini_max::max(std::shared_ptr<board> b, unsigned int d)
{
	if (d == 0)
		return standard_board_evaluator::evaluate(*b, d);

	int highest_seen_value = std::numeric_limits<int>::min();
	for (auto move : b->get_current_player()->get_legal_moves())
	{
		move_transition transition = b->get_current_player()->make_move(move);
		if (transition.get_move_status() == move_status::done)
		{
			int current_value = min(transition.get_transition_board(), d - 1);
			if (highest_seen_value <= current_value)
				highest_seen_value = current_value;
		}
	}
	return highest_seen_value;
}