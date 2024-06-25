/**
 * @file Queen.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of the queen class
 * @version 1.0.0
 *
 */

#include "engine/pieces/Queen.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"

/**
 * @var queen::candidate_move_vector_coordinates
 *
 * @brief The move vector coordinates for the queen
 *
 * @details
 *
 *             |X|_|_|X|_|_|X|_|
 *             |_|X|_|X|_|X|_|_|
 *             |_|_|X|X|X|_|_|_|
 *             |X|X|X|Q|X|X|X|X|
 *             |_|_|X|X|X|_|_|_|
 *             |_|X|_|X|_|X|_|_|
 *             |X|_|_|X|_|_|X|_|
 *             |_|_|_|X|_|_|_|X|
 *
 */
const int queen::candidate_move_vector_coordinates[] = {-9, -8, -7, -1, 1, 7, 8, 9};

queen::queen(const int pp, const alliance pa, const bool fm)
    : piece(pp, pa, piece_type::queen, fm)
{
}

std::vector<std::shared_ptr<move>> queen::calculate_legal_moves(std::shared_ptr<board> b)
{
    std::vector<std::shared_ptr<move>> legal_moves;
    int candidate_destination_coordinate;
    for (const int current_candidate_offset : candidate_move_vector_coordinates)
    {
        // Start from the current piece position
        candidate_destination_coordinate = piece_position_;
        while (board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
        {
            // Check for edge cases
            if (is_first_column_error(candidate_destination_coordinate, current_candidate_offset) ||
                is_eighth_column_error(candidate_destination_coordinate, current_candidate_offset))
                break;
            candidate_destination_coordinate += current_candidate_offset;
            if (board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
            {
                const std::shared_ptr<tile> &candidate_destination_tile = b->get_tile(candidate_destination_coordinate);
                if (!candidate_destination_tile->is_tile_occupied())
                    legal_moves.push_back(std::make_shared<major_move>(b, shared_from_this(), candidate_destination_coordinate));
                else
                {
                    const std::shared_ptr<piece> &piece_at_destination = candidate_destination_tile->get_piece_on_tile();
                    if (piece_alliance_ != piece_at_destination->get_piece_alliance())
                        legal_moves.push_back(std::make_shared<major_attack_move>(b, shared_from_this(), piece_at_destination, candidate_destination_coordinate));
                    break;
                }
            }
        }
    }
    return legal_moves;
}

std::shared_ptr<piece> queen::move_piece(const move *const m) const
{
    return std::make_shared<queen>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false);
}

bool queen::is_first_column_error(const int cp, const int co)
{
    return board_utils::first_column[cp] && (co == -1 || co == -9 || co == 7);
}

bool queen::is_eighth_column_error(const int cp, const int co)
{
    return board_utils::eighth_column[cp] && (co == 1 || co == -7 || co == 9);
}