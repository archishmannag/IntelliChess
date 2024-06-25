/**
 * @file FenUtils.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the FEN utilities
 * @version 1.0.0
 *
 */

#ifndef FEN_UTILS_HPP
#define FEN_UTILS_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class board;

/**
 * @brief FEN utilities
 *
 */
namespace fen_utils
{
    /**
     * @brief Convert a FEN string to a board
     *
     * @param fen The FEN string
     * @return The board
     */
    std::shared_ptr<board> fen_to_board(const std::string &fen);
    /**
     * @brief Convert a board to a FEN string
     *
     * @param b The board
     * @return FEN string
     */
    std::string board_to_fen(const board &b);
} // namespace fen_utils

#endif // FEN_UTILS_HPP