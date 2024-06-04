#include <engine/player/BlackPlayer.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Rook.hpp>

black_player::black_player(std::shared_ptr<board> b, std::vector<std::shared_ptr<move>> wslm, std::vector<std::shared_ptr<move>> bslm)
	: player(b)
{
	player_king_ = establish_king();
	checked_ = !calculate_attacks_on_tile(player_king_->get_piece_position(), wslm).empty();
	std::vector<std::shared_ptr<move>> king_castle_moves = calculate_king_castles(wslm);
	bslm.insert(bslm.end(), king_castle_moves.begin(), king_castle_moves.end());
	legal_moves_ = bslm;
}

std::vector<std::shared_ptr<piece>> black_player::get_active_pieces() const
{
	return board_.lock()->get_black_pieces();
}

alliance black_player::get_player_alliance() const
{
	return alliance::black;
}

std::weak_ptr<player> black_player::get_opponent() const
{
	return board_.lock()->get_white_player();
}

std::vector<std::shared_ptr<move>> black_player::calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const
{
	std::vector<std::shared_ptr<move>> king_castles;
	if (player_king_->is_first_move() && !is_in_check() && !is_castled())
	{
		// Black king side castle
		if (!board_.lock()->get_tile(5)->is_tile_occupied() && !board_.lock()->get_tile(6)->is_tile_occupied())
		{
			std::shared_ptr<tile> rook_tile = board_.lock()->get_tile(7);
			if (rook_tile->is_tile_occupied() && rook_tile->get_piece()->is_first_move() && rook_tile->get_piece()->get_piece_type() == piece_type::rook)
				if (calculate_attacks_on_tile(5, ol).empty() && calculate_attacks_on_tile(6, ol).empty())
					king_castles.push_back(std::make_shared<king_side_castle_move>(board_.lock(), player_king_, 6, std::dynamic_pointer_cast<rook>(rook_tile->get_piece()), rook_tile->get_tile_coordinate(), 5));
		}
		// Black queen side castle
		if (!board_.lock()->get_tile(3)->is_tile_occupied() && !board_.lock()->get_tile(2)->is_tile_occupied() && !board_.lock()->get_tile(1)->is_tile_occupied())
		{
			std::shared_ptr<tile> rook_tile = board_.lock()->get_tile(0);
			if (rook_tile->is_tile_occupied() && rook_tile->get_piece()->is_first_move() && rook_tile->get_piece()->get_piece_type() == piece_type::rook)
				if (calculate_attacks_on_tile(3, ol).empty() && calculate_attacks_on_tile(2, ol).empty() && calculate_attacks_on_tile(1, ol).empty())
					king_castles.push_back(std::make_shared<queen_side_castle_move>(board_.lock(), player_king_, 2, std::dynamic_pointer_cast<rook>(rook_tile->get_piece()), rook_tile->get_tile_coordinate(), 3));
		}
	}
	return king_castles;
}

std::string black_player::stringify() const
{
	return std::string("Black");
}