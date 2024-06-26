/**
 * @file AlphaBeta.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the alpha beta pruning algorithm
 * @version 1.0.0
 *
 */

#include "engine/player/ai/AlphaBeta.hpp"
#include "engine/player/ai/StandardBoardEvaluator.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/MoveTransition.hpp"
#include "engine/player/Player.hpp"

/**
 * @brief Functions to compare and sort moves for the alpha beta pruning algorithm
 *
 */
namespace move_sorter
{
    /**
     * @brief Compare two moves
     *
     * @details Uses King threats, castles and mvv-lva
     *
     * @param m1 The first move
     * @param m2 The second move
     * @return bool
     */
    bool compare_moves(const std::shared_ptr<move> &m1, const std::shared_ptr<move> &m2)
    {
        if (board_utils::is_king_threatened_by_move(m1) && !board_utils::is_king_threatened_by_move(m2))
            return true;
        if (!board_utils::is_king_threatened_by_move(m1) && board_utils::is_king_threatened_by_move(m2))
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
        std::sort(sorted_moves.begin(), sorted_moves.end(), compare_moves);
        return sorted_moves;
    }
} // namespace move_sorter

alpha_beta::alpha_beta(const unsigned sd) : search_depth_(sd)
{
}

// Lines wrapped with DEBUG_BUILD are used for logging to console in debug mode for debugging purposes
std::shared_ptr<move> alpha_beta::execute(std::shared_ptr<board> b)
{
#ifdef DEBUG_BUILD
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    std::string s;
#endif // DEBUG_BUILD

    std::shared_ptr<player> current_player = b->get_current_player();
    std::shared_ptr<move> best_move = move::get_null_move();
    int highest_seen_value = std::numeric_limits<int>::min(),
        lowest_seen_value = std::numeric_limits<int>::max(),
        move_counter = 1,
        number_of_moves = b->get_current_player()->get_legal_moves().size(),
        current_value;

#ifdef DEBUG_BUILD
    std::cout << current_player->stringify() << " THINKING with depth = " << search_depth_ << std::endl;
#endif // DEBUG_BUILD

    // Sort moves so that the best moves are evaluated first, and pruning can be done more effectively
    for (std::shared_ptr<move> m : move_sorter::sort(b->get_current_player()->get_legal_moves()))
    {
        move_transition transition = current_player->make_move(m);
        quiescence_count_ = 0;
        if (transition.get_move_status() == move_status::done)
        {
#ifdef DEBUG_BUILD
            std::chrono::time_point<std::chrono::high_resolution_clock> candidate_move_start_time = std::chrono::high_resolution_clock::now();
#endif // DEBUG_BUILD

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

#ifdef DEBUG_BUILD
            s = "\tAlphaBeta(d:" + std::to_string(search_depth_) + ") -> m: (" + std::to_string(move_counter) + '/' + std::to_string(number_of_moves) + ") " + m->stringify() + ", best: " + best_move->stringify() + ' ' + score(current_player, highest_seen_value, lowest_seen_value) + " q: " + std::to_string(quiescence_count_) + ", t: " + std::to_string(static_cast<int>((std::chrono::high_resolution_clock::now() - candidate_move_start_time).count() / 1000)) + "us";
#endif // DEBUG_BUILD
        }

#ifdef DEBUG_BUILD
        else
            s = "\tAlphaBeta(d:" + std::to_string(search_depth_) + ") -> m: (" + std::to_string(move_counter) + '/' + std::to_string(number_of_moves) + ") " + m->stringify() + " is illegal! Best: " + best_move->stringify();
        std::cout << s << std::endl;
        move_counter++;
#endif // DEBUG_BUILD
    }

#ifdef DEBUG_BUILD
    int64_t execution_time = (std::chrono::high_resolution_clock::now() - start_time).count() / 1000000; // Convert nanoseconds to milliseconds
    std::string result = b->get_current_player()->stringify() + " selects " + best_move->stringify() + ", # boards evaluated = " + std::to_string(boards_evaluated_) + ", time taken = " + std::to_string(execution_time) + "ms, rate = " + std::to_string(1000 * boards_evaluated_ / execution_time) + " boards/s";
    std::cout << result << std::endl;
#endif // DEBUG_BUILD

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
    // Stand-pat is the current board's score
    int stand_pat = standard_board_evaluator::evaluate(*b, depth);

    // If equal or higher than beta, no need to search further as it will be pruned
    if (stand_pat >= beta)
        return beta;

    // If higher than alpha, we update alpha to match our new lower bound (or higher in case of max)
    if (alpha < stand_pat)
        alpha = stand_pat;

    // Check for quiescent attacks
    std::vector<std::shared_ptr<move>> attack_moves, moves = b->get_current_player()->get_legal_moves();
    std::copy_if(moves.begin(), moves.end(), std::back_inserter(attack_moves), [](std::shared_ptr<move> m) -> bool
                 { return m->is_attack_move(); });

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

            // If the lowest seen value is lower than alpha, we can prune the search
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

            // If the highest seen value is higher than beta, we can prune the search
            if (highest_seen_value >= beta)
                return beta;
        }
    }
    return highest_seen_value;
}