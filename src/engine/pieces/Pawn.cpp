/**
 * @file Pawn.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the pawn class
 * @version 1.1.0
 *
 */

#include "engine/pieces/Pawn.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"
#include "engine/pieces/Bishop.hpp"
#include "engine/pieces/Knight.hpp"
#include "engine/pieces/Queen.hpp"
#include "engine/pieces/Rook.hpp"

/**
 * @var pawn::candidate_move_coordinates
 *
 * @brief The move coordinates for the pawn
 *
 * @details
 *
 *                 |_|_|_|_|_|_|_|_|
 *                 |_|_|_|X|_|_|_|_|
 *                 |_|_|X|X|X|_|_|_|
 *                 |_|_|_|P|_|_|_|_|
 *                 |_|_|_|_|_|_|_|_|
 *                 |_|_|_|_|_|_|_|_|
 *                 |_|_|_|_|_|_|_|_|
 *                 |_|_|_|_|_|_|_|_|
 *
 *     It includes the normal move path, the double move path, and the attack move paths.
 *
 */
const int pawn::candidate_move_coordinates[] = { 8, 16, 7, 9 };

pawn::pawn(const int pp, const alliance pa, const bool fm)
    : piece(pp, pa, piece_type::pawn, fm)
{
}

std::vector<std::shared_ptr<move> > pawn::calculate_legal_moves(std::shared_ptr<board> b)
{
    std::vector<std::shared_ptr<move> > legal_moves;
    int candidate_destination_coordinate, behind_candidate_destination_coordinate; // Behind coordinate for pawn jumps
    for (const int current_candidate_offset : candidate_move_coordinates)
    {
        // Pawns are the only pieces which are unidirectional. Hence we need to consider the direction of move by considering the alliance of the piece
        candidate_destination_coordinate = piece_position_ + (current_candidate_offset * alliance_utils::get_direction(piece_alliance_));

        if (!board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
            continue;

        // Case 1: Normal move - Move forward by 1 tile if the destination tile is not occupied
        if (current_candidate_offset == 8 && !b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
        {
            // If the destination tile is a promotion square, then we need to create a pawn promotion move, else a normal pawn move
            if (alliance_utils::is_pawn_promotion_square(piece_alliance_, candidate_destination_coordinate))
            {
                legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_move>(b,
                                                                                                   shared_from_this(),
                                                                                                   candidate_destination_coordinate),
                                                                       std::make_shared<queen>(candidate_destination_coordinate,
                                                                                               piece_alliance_,
                                                                                               false)));
                legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_move>(b,
                                                                                                   shared_from_this(),
                                                                                                   candidate_destination_coordinate),
                                                                       std::make_shared<rook>(candidate_destination_coordinate,
                                                                                              piece_alliance_,
                                                                                              false)));
                legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_move>(b,
                                                                                                   shared_from_this(),
                                                                                                   candidate_destination_coordinate),
                                                                       std::make_shared<knight>(candidate_destination_coordinate,
                                                                                                piece_alliance_,
                                                                                                false)));
                legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_move>(b,
                                                                                                   shared_from_this(),
                                                                                                   candidate_destination_coordinate),
                                                                       std::make_shared<bishop>(candidate_destination_coordinate,
                                                                                                piece_alliance_,
                                                                                                false)));
            }
            // Normal move
            else
                legal_moves.push_back(std::make_shared<pawn_move>(b, shared_from_this(), candidate_destination_coordinate));
        }

        // Case 2: Double move - Move forward by 2 tiles if the destination tile is not occupied and the piece is in the starting position
        else if (current_candidate_offset == 16 && is_first_move() && ((board_utils::second_row[piece_position_] && alliance_utils::is_black(piece_alliance_)) || (board_utils::seventh_row[piece_position_] && alliance_utils::is_white(piece_alliance_))))
        {
            behind_candidate_destination_coordinate = piece_position_ + (alliance_utils::get_direction(piece_alliance_) * 8);
            if (!b->get_tile(behind_candidate_destination_coordinate)->is_tile_occupied() && !b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
                legal_moves.push_back(std::make_shared<pawn_jump>(b, shared_from_this(), candidate_destination_coordinate));
        }

        // Case 3 and 4: Attack moves - Calculation of promotion, normal and en passant attack moves
        else if (current_candidate_offset == 7 && !((board_utils::eighth_column[piece_position_] && alliance_utils::is_white(piece_alliance_)) || (board_utils::first_column[piece_position_] && alliance_utils::is_black(piece_alliance_))))
        {
            if (b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
            {
                const std::shared_ptr<piece> &piece_on_candidate = b->get_tile(candidate_destination_coordinate)->get_piece_on_tile();
                if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
                {
                    // Promotion attack move
                    if (alliance_utils::is_pawn_promotion_square(piece_alliance_, candidate_destination_coordinate))
                    {
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<queen>(candidate_destination_coordinate,
                                                                                                       piece_alliance_,
                                                                                                       false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<rook>(candidate_destination_coordinate,
                                                                                                      piece_alliance_,
                                                                                                      false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<knight>(candidate_destination_coordinate,
                                                                                                        piece_alliance_,
                                                                                                        false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<bishop>(candidate_destination_coordinate,
                                                                                                        piece_alliance_,
                                                                                                        false)));
                    }
                    // Normal attack move
                    else
                        legal_moves.push_back(std::make_shared<pawn_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
                }
            }
            // En passant attack move
            else if (b->get_en_passant_pawn() != nullptr && b->get_en_passant_pawn()->get_piece_position() == piece_position_ + alliance_utils::get_opposite_direction(piece_alliance_))
            {
                const std::shared_ptr<piece> &piece_on_candidate = b->get_en_passant_pawn();
                if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
                    legal_moves.push_back(std::make_shared<pawn_en_passant_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
            }
        }

        else if (current_candidate_offset == 9 && !((board_utils::eighth_column[piece_position_] && alliance_utils::is_black(piece_alliance_)) || (board_utils::first_column[piece_position_] && alliance_utils::is_white(piece_alliance_))))
        {
            if (b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
            {
                const std::shared_ptr<piece> &piece_on_candidate = b->get_tile(candidate_destination_coordinate)->get_piece_on_tile();
                if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
                {
                    // Promotion attack move
                    if (alliance_utils::is_pawn_promotion_square(piece_alliance_, candidate_destination_coordinate))
                    {
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<queen>(candidate_destination_coordinate,
                                                                                                       piece_alliance_,
                                                                                                       false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<rook>(candidate_destination_coordinate,
                                                                                                      piece_alliance_,
                                                                                                      false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<knight>(candidate_destination_coordinate,
                                                                                                        piece_alliance_,
                                                                                                        false)));
                        legal_moves.push_back(std::make_shared<pawn_promotion>(std::make_shared<pawn_attack_move>(b,
                                                                                                                  shared_from_this(),
                                                                                                                  piece_on_candidate,
                                                                                                                  candidate_destination_coordinate),
                                                                               std::make_shared<bishop>(candidate_destination_coordinate,
                                                                                                        piece_alliance_,
                                                                                                        false)));
                    }
                    // Normal attack move
                    else
                        legal_moves.push_back(std::make_shared<pawn_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
                }
            }
            // En passant attack move
            else if (b->get_en_passant_pawn() != nullptr && b->get_en_passant_pawn()->get_piece_position() == piece_position_ - alliance_utils::get_opposite_direction(piece_alliance_))
            {
                const std::shared_ptr<piece> &piece_on_candidate = b->get_en_passant_pawn();
                if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
                    legal_moves.push_back(std::make_shared<pawn_en_passant_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
            }
        }
    }
    return legal_moves;
}

std::shared_ptr<piece> pawn::move_piece(const move *const m) const
{
    return std::make_shared<pawn>(m->get_destination_coordinate(), m->get_moved_piece()->get_piece_alliance(), false);
}