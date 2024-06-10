#include <engine/player/WhitePlayer.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Rook.hpp>

white_player::white_player(std::shared_ptr<board> b, std::vector<std::shared_ptr<move>> wslm, std::vector<std::shared_ptr<move>> bslm)
	: player(b)
{
	player_king_ = establish_king();
	checked_ = !calculate_attacks_on_tile(player_king_->get_piece_position(), bslm).empty();
	std::vector<std::shared_ptr<move>> king_castle_moves = calculate_king_castles(bslm);
	wslm.insert(wslm.end(), king_castle_moves.begin(), king_castle_moves.end());
	legal_moves_ = wslm;
}

std::vector<std::shared_ptr<piece>> white_player::get_active_pieces() const
{
	return board_.lock()->get_white_pieces();
}

alliance white_player::get_player_alliance() const
{
	return alliance::white;
}

std::weak_ptr<player> white_player::get_opponent() const
{
	return board_.lock()->get_black_player();
}

std::vector<std::shared_ptr<move>> white_player::calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const
{
	std::vector<std::shared_ptr<move>> king_castles;
	if (player_king_->is_first_move() &&
		!is_in_check() &&
		!is_castled() &&
		is_castle_capable())
	{
		// White king side castle
		if (!board_.lock()->get_tile(61)->is_tile_occupied() &&
			!board_.lock()->get_tile(62)->is_tile_occupied())
		{
			std::shared_ptr<tile> rook_tile = board_.lock()->get_tile(63);
			if (rook_tile->is_tile_occupied() &&
				rook_tile->get_piece()->is_first_move() &&
				rook_tile->get_piece()->get_piece_type() == piece_type::rook)
			{
				if (calculate_attacks_on_tile(61, ol).empty() &&
					calculate_attacks_on_tile(62, ol).empty() &&
					!board_utils::is_king_pawn_trap(board_.lock().get(), player_king_.get(), 52))
					king_castles.push_back(std::make_shared<king_side_castle_move>(board_.lock(), player_king_, 62, std::dynamic_pointer_cast<rook>(rook_tile->get_piece()), rook_tile->get_tile_coordinate(), 61));
			}
			else
				player_king_->set_king_side_castle_capable(false);
		}
		// White queen side castle
		if (!board_.lock()->get_tile(59)->is_tile_occupied() &&
			!board_.lock()->get_tile(58)->is_tile_occupied() &&
			!board_.lock()->get_tile(57)->is_tile_occupied())
		{
			std::shared_ptr<tile> rook_tile = board_.lock()->get_tile(56);
			if (rook_tile->is_tile_occupied() &&
				rook_tile->get_piece()->is_first_move() &&
				rook_tile->get_piece()->get_piece_type() == piece_type::rook)
			{
				if (calculate_attacks_on_tile(59, ol).empty() &&
					calculate_attacks_on_tile(58, ol).empty() &&
					calculate_attacks_on_tile(57, ol).empty() &&
					!board_utils::is_king_pawn_trap(board_.lock().get(), player_king_.get(), 52))
					king_castles.push_back(std::make_shared<queen_side_castle_move>(board_.lock(), player_king_, 58, std::dynamic_pointer_cast<rook>(rook_tile->get_piece()), rook_tile->get_tile_coordinate(), 59));
			}
			else
				player_king_->set_queen_side_castle_capable(false);
		}
	}
	return king_castles;
}

std::string white_player::stringify() const
{
	return std::string("White");
}