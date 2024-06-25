/**
 * @file AlphaBeta.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the alpha beta pruning algorithm
 * @version 1.0.0
 *
 */

#ifndef ALPHA_BETA_HPP
#define ALPHA_BETA_HPP

#include "PreCompiledHeaders.hpp"

#include "MoveStrategy.hpp"

// Forward declarations
class board;
class move;
class player;

/**
 * @brief The alpha beta pruning algorithm
 *
 */
class alpha_beta final : public move_strategy
{
public:
    /**
     * @param sd The search depth
     */
    alpha_beta(const unsigned sd);
    /**
     * @brief Execute the alpha beta pruning algorithm on a board and return the best move
     *
     * @param b The board
     * @return The best move
     */
    std::shared_ptr<move> execute(std::shared_ptr<board> b) override;

private:
    /**
     * @brief The max function for the alpha beta pruning algorithm
     *
     * @param b
     * @param depth
     * @param alpha
     * @param beta
     * @return The max score
     */
    int max(std::shared_ptr<board> b, int depth, int alpha, int beta);
    /**
     * @brief The min function for the alpha beta pruning algorithm
     *
     * @param b
     * @param depth
     * @param alpha
     * @param beta
     * @return The min score
     */
    int min(std::shared_ptr<board> b, int depth, int alpha, int beta);
    /**
     * @brief The quiescence function to prevent the horizon effect
     *
     * @param b
     * @param depth
     * @param alpha
     * @param beta
     * @return The quiescence score
     */
    int quiescence(std::shared_ptr<board> b, int depth, int alpha, int beta);
    std::string score(std::shared_ptr<player> cp, int highest_seen_value, int lowest_seen_value);

private:
    int search_depth_,          ///< The search depth
        quiescence_count_ = 0,  ///< The quiescence count @todo: use this
        max_quiescence = 25000; ///< The max quiescence value @todo: use this
    long boards_evaluated_ = 0; ///< The number of boards evaluated
};

#endif // ALPHA_BETA_HPP