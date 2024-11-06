/**
 * @file Rook.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the rook class
 * @version 1.1.0
 *
 */

#include "engine/pieces/Rook.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"

/**
 * @var rook::candidate_move_vector_coordinates
 *
 * @brief The move vector coordinates for the rook
 *
 * @details
 *
 *             |_|_|_|X|_|_|_|_|
 *             |_|_|_|X|_|_|_|_|
 *             |_|_|_|X|_|_|_|_|
 *             |X|X|X|R|X|X|X|X|
 *             |_|_|_|X|_|_|_|_|
 *             |_|_|_|X|_|_|_|_|
 *             |_|_|_|X|_|_|_|_|
 *             |_|_|_|X|_|_|_|_|
 *
 */
const int rook::candidate_move_vector_coordinates[] = { -8, -1, 1, 8 };

rook::rook(const int pp, const alliance pa, const bool fm)
    : piece(pp, pa, piece_type::rook, fm)
{
}

std::vector<std::shared_ptr<move> > rook::calculate_legal_moves(std::shared_ptr<board> b)
{
    std::vector<std::shared_ptr<move> > legal_moves;
    int candidate_destination_coordinate;
    for (const int current_candidate_offset : candidate_move_vector_coordinates)
    {
        // Start from the current piece position
        candidate_destination_coordinate = piece_position_;
        while (board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
        {
            // If error(reached edge), break and go for the next offset
            if (is_first_column_error(candidate_destination_coordinate, current_candidate_offset) || is_eighth_column_error(candidate_destination_coordinate, current_candidate_offset))
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

std::shared_ptr<piece> rook::move_piece(const move *const m) const
{
    return std::make_shared<rook>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false);
}

bool rook::is_first_column_error(const int cp, const int co)
{
    return board_utils::first_column[cp] && (co == -1);
}

bool rook::is_eighth_column_error(const int cp, const int co)
{
    return board_utils::eighth_column[cp] && (co == 1);
}