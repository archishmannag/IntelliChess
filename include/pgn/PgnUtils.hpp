/**
 * @file PgnUtils.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the PGN utilities
 * @version 1.1.0
 *
 */

#ifndef PGN_UTILS_HPP
#define PGN_UTILS_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class move;
class board;

/**
 * @brief PGN utilities
 *
 */
namespace pgn_utils
{
    /**
     * @brief Save a game to a PGN file
     *
     * @param file_path The path to the pgn file to save
     * @param moves The moves in order
     * @param b The board
     */
    void save_game_to_pgn(const std::string &file_path, const std::vector<std::shared_ptr<move> > &moves, const board &b);
} // namespace pgn_utils

#endif // PGN_UTILS_HPP