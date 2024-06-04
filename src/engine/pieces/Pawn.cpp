#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Queen.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/pieces/Knight.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>

const int pawn::candidate_move_coordinates[] = {8, 16, 7, 9};

pawn::pawn(const int pp, const alliance pa, const bool fm)
	: piece(pp, pa, piece_type::pawn, fm)
{
}

std::vector<std::shared_ptr<move>> pawn::calculate_legal_moves(std::shared_ptr<board> b)
{
	std::vector<std::shared_ptr<move>> legal_moves;
	int candidate_destination_coordinate, behind_candidate_destination_coordinate;
	for (const int current_candidate_offset : candidate_move_coordinates)
	{
		candidate_destination_coordinate = piece_position_ + (current_candidate_offset * alliance_utils::get_direction(piece_alliance_));
		if (!board_utils::is_valid_tile_coordinate(candidate_destination_coordinate))
			continue;

		if (current_candidate_offset == 8 && !b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
		{
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
			else
				legal_moves.push_back(std::make_shared<pawn_move>(b, shared_from_this(), candidate_destination_coordinate));
		}
		else if (current_candidate_offset == 16 &&
				 is_first_move() &&
				 ((board_utils::second_row[piece_position_] && alliance_utils::is_black(piece_alliance_)) ||
				  (board_utils::seventh_row[piece_position_] && alliance_utils::is_white(piece_alliance_))))
		{
			behind_candidate_destination_coordinate = piece_position_ + (alliance_utils::get_direction(piece_alliance_) * 8);
			if (!b->get_tile(behind_candidate_destination_coordinate)->is_tile_occupied() && !b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
				legal_moves.push_back(std::make_shared<pawn_jump>(b, shared_from_this(), candidate_destination_coordinate));
		}
		else if (current_candidate_offset == 7 &&
				 !((board_utils::eighth_column[piece_position_] && alliance_utils::is_white(piece_alliance_)) ||
				   (board_utils::first_column[piece_position_] && alliance_utils::is_black(piece_alliance_))))
		{
			if (b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
			{
				auto piece_on_candidate = b->get_tile(candidate_destination_coordinate)->get_piece();
				if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
				{
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
					else
						legal_moves.push_back(std::make_shared<pawn_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
				}
			}
			else if (b->get_en_passant_pawn() != nullptr && b->get_en_passant_pawn()->get_piece_position() == piece_position_ + alliance_utils::get_opposite_direction(piece_alliance_))
			{
				auto piece_on_candidate = b->get_en_passant_pawn();
				if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
					legal_moves.push_back(std::make_shared<pawn_en_passant_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
			}
		}
		else if (current_candidate_offset == 9 &&
				 !((board_utils::eighth_column[piece_position_] && alliance_utils::is_black(piece_alliance_)) ||
				   (board_utils::first_column[piece_position_] && alliance_utils::is_white(piece_alliance_))))
		{
			if (b->get_tile(candidate_destination_coordinate)->is_tile_occupied())
			{
				auto piece_on_candidate = b->get_tile(candidate_destination_coordinate)->get_piece();
				if (piece_alliance_ != piece_on_candidate->get_piece_alliance())
				{
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
					else
						legal_moves.push_back(std::make_shared<pawn_attack_move>(b, shared_from_this(), piece_on_candidate, candidate_destination_coordinate));
				}
			}
			else if (b->get_en_passant_pawn() != nullptr && b->get_en_passant_pawn()->get_piece_position() == piece_position_ - alliance_utils::get_opposite_direction(piece_alliance_))
			{
				auto piece_on_candidate = b->get_en_passant_pawn();
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