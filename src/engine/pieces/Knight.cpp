/**
 * @file Knight.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of the knight class
 * @version 1.0.0
 *
 */

#include "engine/pieces/Knight.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"

knight::knight(const int pp, const alliance pa, const bool isFirstMove)
    : piece(pp, pa, piece_type::knight, isFirstMove)
{
}

/**
 * @var knight::candidate_move_coordinates
 *
 * @brief The move coordinates for the knight
 *
 * @details
 *
 *              |_|_|_|_|_|_|_|_|
 *              |_|_|X|_|X|_|_|_|
 *              |_|X|_|_|_|X|_|_|
 *              |_|_|_|N|_|_|_|_|
 *              |_|X|_|_|_|X|_|_|
 *              |_|_|X|_|X|_|_|_|
 *              |_|_|_|_|_|_|_|_|
 *              |_|_|_|_|_|_|_|_|
 *
 */
const int knight::candidate_move_coordinates[] = {-17, -15, -10, -6, 6, 10, 15, 17};

std::vector<std::shared_ptr<move>> knight::calculate_legal_moves(std::shared_ptr<board> b)
{
    int candidate_destination_coordinate;
    std::vector<std::shared_ptr<move>> legal_moves;

    for (const int current_candidate_offset : candidate_move_coordinates)
    {
        candidate_destination_coordinate = piece_position_ + current_candidate_offset;
        if (board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
        {
            // Check for edge cases
            if (is_first_column_error(piece_position_, current_candidate_offset) ||
                is_second_column_error(piece_position_, current_candidate_offset) ||
                is_seventh_column_error(piece_position_, current_candidate_offset) ||
                is_eighth_column_error(piece_position_, current_candidate_offset))
                continue;

            const std::shared_ptr<tile> &candidate_destination_tile = b->get_tile(candidate_destination_coordinate);

            if (!candidate_destination_tile->is_tile_occupied())
                legal_moves.push_back(std::make_shared<major_move>(b, shared_from_this(), candidate_destination_coordinate));
            else
            {
                const std::shared_ptr<piece> &piece_at_destination = candidate_destination_tile->get_piece_on_tile();
                if (piece_alliance_ != piece_at_destination->get_piece_alliance())
                    legal_moves.push_back(std::make_shared<major_attack_move>(b, shared_from_this(), piece_at_destination, candidate_destination_coordinate));
            }
        }
    }
    return legal_moves;
}

std::shared_ptr<piece> knight::move_piece(const move *const m) const
{
    return std::make_shared<knight>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false);
}

bool knight::is_first_column_error(const int cp, const int co)
{
    return board_utils::first_column[cp] && (co == -17 || co == -10 || co == 6 || co == 15);
}

bool knight::is_second_column_error(const int cp, const int co)
{
    return board_utils::second_column[cp] && (co == -10 || co == 6);
}

bool knight::is_seventh_column_error(const int cp, const int co)
{
    return board_utils::seventh_column[cp] && (co == 10 || co == -6);
}

bool knight::is_eighth_column_error(const int cp, const int co)
{
    return board_utils::eighth_column[cp] && (co == 17 || co == 10 || co == -6 || co == -15);
}