#include <engine/board/Board.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/pieces/Knight.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/pieces/Queen.hpp>
#include <engine/pieces/King.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/player/WhitePlayer.hpp>
#include <engine/player/BlackPlayer.hpp>

/* board_builder */

void board_builder::set_previous_board(std::shared_ptr<board> pb)
{
	previous_board_ = std::move(pb);
}

void board_builder::set_piece(std::shared_ptr<piece> p)
{
	board_config_[p->get_piece_position()] = std::move(p);
	return;
}

void board_builder::set_en_passant_pawn(std::shared_ptr<pawn> ep)
{
	en_passant_pawn_ = std::move(ep);
}

void board_builder::set_move_maker(const alliance mm)
{
	next_move_maker_ = mm;
}

void board_builder::set_transition_move(std::shared_ptr<move> tm)
{
	transition_move_ = std::move(tm);
}

std::shared_ptr<board> board_builder::get_previous_board() const
{
	return previous_board_;
}

alliance board_builder::get_next_move_maker() const
{
	return next_move_maker_;
}

std::shared_ptr<pawn> board_builder::get_en_passant_pawn() const
{
	return en_passant_pawn_;
}

std::shared_ptr<move> board_builder::get_transition_move() const
{
	return transition_move_;
}

std::shared_ptr<board> board_builder::build()
{
	std::shared_ptr<board> b = std::make_shared<board>();
	b->initialize_game_board(*this);
	return b;
}

/* board */

void board::initialize_game_board(const board_builder &b)
{
	previous_board_ = b.get_previous_board();
	en_passant_pawn_ = b.get_en_passant_pawn();
	transition_move_ = b.get_transition_move();
	game_board_ = board::create_game_board(b);
	white_pieces_ = board::calculate_active_pieces(game_board_, alliance::white);
	black_pieces_ = board::calculate_active_pieces(game_board_, alliance::black);
	white_player_ = std::make_shared<white_player>(shared_from_this(), calculate_legal_moves(white_pieces_), calculate_legal_moves(black_pieces_));
	black_player_ = std::make_shared<black_player>(shared_from_this(), calculate_legal_moves(white_pieces_), calculate_legal_moves(black_pieces_));
	current_player_ = (alliance_utils::choose_player(b.get_next_move_maker(), this));
}

std::vector<std::shared_ptr<move>> board::calculate_legal_moves(const std::vector<std::shared_ptr<piece>> &P)
{
	std::vector<std::shared_ptr<move>> legal_moves;
	for (auto &piece : P)
	{
		std::vector<std::shared_ptr<move>> piece_legal_moves = piece->calculate_legal_moves(shared_from_this());
		legal_moves.insert(legal_moves.end(), piece_legal_moves.begin(), piece_legal_moves.end());
	}
	return legal_moves;
}

std::vector<std::shared_ptr<piece>> board::calculate_active_pieces(const std::array<std::shared_ptr<tile>, 64> &gb, alliance a)
{
	std::vector<std::shared_ptr<piece>> active_pieces;
	for (auto &t : gb)
	{
		if (t->is_tile_occupied())
		{
			auto piece = t->get_piece();
			if (piece->get_piece_alliance() == a)
				active_pieces.push_back(piece);
		}
	}
	return active_pieces;
}

std::array<std::shared_ptr<tile>, 64> board::create_game_board(const board_builder &b)
{
	std::array<std::shared_ptr<tile>, 64> game_board;
	;
	for (int i = 0; i < 64; i++)
	{
		auto it = b.board_config_.find(i);
		game_board[i] = it != b.board_config_.end() ? tile::create_tile(i, it->second) : tile::create_tile(i, nullptr);
	}
	return game_board;
}

std::shared_ptr<board> board::get_previous_board() const
{
	return previous_board_;
}

std::shared_ptr<tile> board::get_tile(int tc) const
{
	return game_board_[tc];
}

const std::vector<std::shared_ptr<piece>> &board::get_white_pieces() const
{
	return white_pieces_;
}

const std::vector<std::shared_ptr<piece>> &board::get_black_pieces() const
{
	return black_pieces_;
}

const std::vector<std::shared_ptr<piece>> board::get_all_pieces() const
{
	std::vector<std::shared_ptr<piece>> all_pieces;
	all_pieces.insert(all_pieces.end(), white_pieces_.begin(), white_pieces_.end());
	all_pieces.insert(all_pieces.end(), black_pieces_.begin(), black_pieces_.end());
	return all_pieces;
}

std::shared_ptr<player> board::get_white_player() const
{
	return white_player_;
}

std::shared_ptr<player> board::get_black_player() const
{
	return black_player_;
}

std::shared_ptr<player> board::get_current_player() const
{
	return current_player_.lock();
}

std::vector<std::shared_ptr<move>> board::get_all_legal_moves() const
{
	std::vector<std::shared_ptr<move>> all_legal_moves,
		whiteLegalMoves = white_player_->get_legal_moves(),
		blackLegalMoves = black_player_->get_legal_moves();
	all_legal_moves.insert(all_legal_moves.end(), whiteLegalMoves.begin(), whiteLegalMoves.end());
	all_legal_moves.insert(all_legal_moves.end(), blackLegalMoves.begin(), blackLegalMoves.end());
	return all_legal_moves;
}

std::shared_ptr<pawn> board::get_en_passant_pawn() const
{
	return en_passant_pawn_;
}

std::shared_ptr<board> board::create_standard_board()
{
	board_builder builder;

	// Black Pieces
	builder.set_piece(std::make_shared<rook>(0, alliance::black));
	builder.set_piece(std::make_shared<knight>(1, alliance::black));
	builder.set_piece(std::make_shared<bishop>(2, alliance::black));
	builder.set_piece(std::make_shared<queen>(3, alliance::black));
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	builder.set_piece(std::make_shared<bishop>(5, alliance::black));
	builder.set_piece(std::make_shared<knight>(6, alliance::black));
	builder.set_piece(std::make_shared<rook>(7, alliance::black));
	builder.set_piece(std::make_shared<pawn>(8, alliance::black));
	builder.set_piece(std::make_shared<pawn>(9, alliance::black));
	builder.set_piece(std::make_shared<pawn>(10, alliance::black));
	builder.set_piece(std::make_shared<pawn>(11, alliance::black));
	builder.set_piece(std::make_shared<pawn>(12, alliance::black));
	builder.set_piece(std::make_shared<pawn>(13, alliance::black));
	builder.set_piece(std::make_shared<pawn>(14, alliance::black));
	builder.set_piece(std::make_shared<pawn>(15, alliance::black));

	// White Pieces
	builder.set_piece(std::make_shared<pawn>(48, alliance::white));
	builder.set_piece(std::make_shared<pawn>(49, alliance::white));
	builder.set_piece(std::make_shared<pawn>(50, alliance::white));
	builder.set_piece(std::make_shared<pawn>(51, alliance::white));
	builder.set_piece(std::make_shared<pawn>(52, alliance::white));
	builder.set_piece(std::make_shared<pawn>(53, alliance::white));
	builder.set_piece(std::make_shared<pawn>(54, alliance::white));
	builder.set_piece(std::make_shared<pawn>(55, alliance::white));
	builder.set_piece(std::make_shared<rook>(56, alliance::white));
	builder.set_piece(std::make_shared<knight>(57, alliance::white));
	builder.set_piece(std::make_shared<bishop>(58, alliance::white));
	builder.set_piece(std::make_shared<queen>(59, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_piece(std::make_shared<bishop>(61, alliance::white));
	builder.set_piece(std::make_shared<knight>(62, alliance::white));
	builder.set_piece(std::make_shared<rook>(63, alliance::white));

	// Starting player is white
	builder.set_move_maker(alliance::white);

	return builder.build();
}

std::string board::stringify() const
{
	std::string board_string = "";
	for (int i = 0; i < 64; i++)
	{
		board_string += game_board_[i]->stringify();
		if ((i + 1) % 8 == 0)
			board_string += "\n";
	}
	return board_string;
}