/**
 * @file BoardUtils.hpp
 * @author your name (you@domain.com)
 * @brief Header files of utility functions related to the Board
 * @version 1.0.0
 *
 */

#ifndef BOARD_UTILS_HPP
#define BOARD_UTILS_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class board;
class king;
class move;

/**
 * @namespace board_utils
 * @brief A namespace containing utility functions related to the board
 *
 */
namespace board_utils
{
    extern std::array<bool, 64>
        first_column, second_column, third_column, fourth_column, fifth_column, sixth_column, seventh_column, eighth_column, ///< Column arrays
        first_row, second_row, third_row, fourth_row, fifth_row, sixth_row, seventh_row, eighth_row;                         ///< Row arrays

    bool is_valid_tile_coordinate(int c);

    /**
     * @brief Get the coodrinate (e.g. 45) coresponding to a position (e.g. "e4")
     *
     * @param p The string position
     * @return The integer coordinate
     */
    int get_coordinate_at_position(std::string p);

    /**
     * @brief Get the position (e.g. "e4") corresponding to a coordinate (e.g. 45)
     *
     * @param c The integer coordinate
     * @return The string position
     */
    std::string get_position_at_coordinate(int c);

    bool is_king_threatened_by_move(std::shared_ptr<move> m);

    /**
     * @brief Checks if the castle is prevented by a pawn attack
     *
     * @details This function checks if the castle is prevented by a pawn attack. This is done by checking if the tile at the from_tile has a pawn.
     * As pawn attacks are different from its moves, pawn attack moves cannot be generated and detected, hence this check.
     *
     *                    O-O-O    O-O
     *                  |r|_|_|X|k|X|_|r|
     *                  |_|_|_|_|P|_|_|_|
     *                  |_|_|_|_|_|_|_|_|
     *                  |_|_|_|_|_|_|_|_|
     *                  |_|_|_|_|_|_|_|_|
     *                  |_|_|_|_|_|_|_|_|
     *                  |_|_|_|_|_|_|_|_|
     *                  |_|_|_|_|K|_|_|_|
     *
     * In above board, the pawn attacks on the marked tiles (X) are not generated and detected by the normal methods, but due to attack, the castle is prevented.
     *
     * @param b The board
     * @param k The player king
     * @param ft The from_tile coordinate
     * @return bool
     */
    bool pawn_castle_attack_check(const board *b, const king *k, const int ft);

    /**
     * @brief The Most Valuable Victim - Least Valuable Aggressor (MVV-LVA) heuristic
     *
     * @details The MVV-LVA heuristic is used to order the captures in the move list. The captures are ordered by the value of the captured piece minus the value of the capturing piece. This helps sort moves in the order of most valuable victim to least valuable aggressor. This ensures that the search algorithm prefers moves where we capture more points while losing the least points.
     *
     * @param m The move
     * @return The MVV-LVA score
     */
    int mvv_lva(const move *m);

    bool game_over(const board *b);

    /**
     * @brief Returns the check and checkmate status of the board for appending to the moves' notation
     *
     * @details This function returns the check and checkmate status of the board for appending to the moves' notation. If the player is in check, the function returns "+". If the player is in checkmate, the function returns "#". If neither case matches, it returns ''.
     *
     * @param b The board
     * @return The check/checkmate status
     */
    std::string calculate_check_and_checkmate(board *b);
} // namespace board_utils

#endif // BOARD_UTILS_HPP