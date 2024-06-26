/**
 * @file StandardBoardEvaluator.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the standard board evaluator
 * @version 1.0.0
 *
 */

#ifndef STANDARD_BOARD_EVALUATOR_HPP
#define STANDARD_BOARD_EVALUATOR_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class board;
class player;

/**
 * @brief Evaluate a board position and return a score
 *
 */
namespace standard_board_evaluator
{
    /**
     * @brief Evaluate a board position and return a score
     *
     * @param b The board
     * @param d The search depth
     * @return The score
     */
    int evaluate(const board &b, int d);
    std::string evaluation_details(const board &b, const int d);
} // namespace standard_board_evaluator

#endif // STANDARD_BOARD_EVALUATOR_HPP