/**
 * @file King.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of the king class
 * @version 1.0.0
 *
 */

#include "engine/pieces/King.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"

/**
 * @var king::candidate_move_coordinates
 *
 * @brief The move coordinates for the king
 *
 * @details
 *
 * 		 |_|_|_|_|_|_|_|_|
 * 		 |_|_|_|_|_|_|_|_|
 * 		 |_|_|X|X|X|_|_|_|
 * 		 |_|_|X|K|X|_|_|_|
 * 		 |_|_|X|X|X|_|_|_|
 * 		 |_|_|_|_|_|_|_|_|
 * 		 |_|_|_|_|_|_|_|_|
 * 		 |_|_|_|_|_|_|_|_|
 *
 */
const int king::candidate_move_coordinates[] = {-9, -8, -7, -1, 1, 7, 8, 9};

king::king(const int pp, const alliance pa, const bool fm, const bool c, const bool ksc, const bool qsc)
    : piece(pp, pa, piece_type::king, fm),
      castled_(c),
      king_side_castle_capable_(ksc),
      queen_side_castle_capable_(qsc)
{
}

std::vector<std::shared_ptr<move>> king::calculate_legal_moves(std::shared_ptr<board> b)
{
    std::vector<std::shared_ptr<move>> legal_moves;
    int candidate_destination_coordinate;
    for (const int current_candidate_offset : candidate_move_coordinates)
    {
        candidate_destination_coordinate = piece_position_ + current_candidate_offset;
        if (board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
        {
            if (is_first_column_error(piece_position_, current_candidate_offset) || is_eighth_column_error(piece_position_, current_candidate_offset))
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

std::shared_ptr<piece> king::move_piece(const move *const m) const
{
    if (!is_castled())
        return std::make_shared<king>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false, m->is_castling_move(), false, false);
    else
        return std::make_shared<king>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false, true, false, false);
}

void king::set_king_side_castle_capability(const bool ksc)
{
    king_side_castle_capable_ = ksc;
}

void king::set_queen_side_castle_capability(const bool qsc)
{
    queen_side_castle_capable_ = qsc;
}

bool king::is_castled() const
{
    return castled_;
}

bool king::is_king_side_castle_capable() const
{
    return king_side_castle_capable_;
}

bool king::is_queen_side_castle_capable() const
{
    return queen_side_castle_capable_;
}

bool king::is_first_column_error(const int cp, const int co)
{
    return board_utils::first_column[cp] && (co == -9 || co == -1 || co == 7);
}

bool king::is_eighth_column_error(const int cp, const int co)
{
    return board_utils::eighth_column[cp] && (co == -7 || co == 1 || co == 9);
}