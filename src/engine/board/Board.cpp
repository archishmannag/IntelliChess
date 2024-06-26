/**
 * @file Board.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the board and board-builder class
 * @version 1.0.0
 *
 */

#include "engine/board/Board.hpp"
#include "engine/pieces/Piece.hpp"
#include "engine/pieces/Pawn.hpp"
#include "engine/pieces/Rook.hpp"
#include "engine/pieces/Knight.hpp"
#include "engine/pieces/Bishop.hpp"
#include "engine/pieces/Queen.hpp"
#include "engine/pieces/King.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/Tile.hpp"
#include "engine/player/WhitePlayer.hpp"
#include "engine/player/BlackPlayer.hpp"

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

void board_builder::set_half_move_clock(int hmc)
{
    half_move_clock_ = hmc;
}

void board_builder::set_full_move_number(int fmn)
{
    full_move_number_ = fmn;
}

std::shared_ptr<board> board_builder::get_previous_board() const
{
    return previous_board_;
}

alliance board_builder::get_next_move_maker() const
{
    return next_move_maker_;
}

const std::unordered_map<int, std::shared_ptr<piece>> &board_builder::get_board_config() const
{
    return board_config_;
}

std::shared_ptr<pawn> board_builder::get_en_passant_pawn() const
{
    return en_passant_pawn_;
}

std::shared_ptr<move> board_builder::get_transition_move() const
{
    return transition_move_;
}

int board_builder::get_half_move_clock() const
{
    return half_move_clock_;
}

int board_builder::get_full_move_number() const
{
    return full_move_number_;
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

    std::vector<std::shared_ptr<move>> white_legal_moves = calculate_legal_moves(white_pieces_),
                                       black_legal_moves = calculate_legal_moves(black_pieces_);

    white_player_ = std::make_shared<white_player>(shared_from_this(), white_legal_moves, black_legal_moves);
    black_player_ = std::make_shared<black_player>(shared_from_this(), white_legal_moves, black_legal_moves);
    current_player_ = (alliance_utils::choose_player(b.get_next_move_maker(), this));
    half_move_clock_ = b.get_half_move_clock();
    full_move_number_ = b.get_full_move_number();
}

std::vector<std::shared_ptr<move>> board::calculate_legal_moves(const std::vector<std::shared_ptr<piece>> &pieces)
{
    std::vector<std::shared_ptr<move>> legal_moves;
    for (const std::shared_ptr<piece> &p : pieces)
    {
        std::vector<std::shared_ptr<move>> piece_legal_moves = p->calculate_legal_moves(shared_from_this());
        legal_moves.insert(legal_moves.end(), piece_legal_moves.begin(), piece_legal_moves.end());
    }
    return legal_moves;
}

std::vector<std::shared_ptr<piece>> board::calculate_active_pieces(const std::array<std::shared_ptr<tile>, 64> &gameboard, alliance a)
{
    std::vector<std::shared_ptr<piece>> active_pieces;
    for (const std::shared_ptr<tile> &t : gameboard)
    {
        if (t->is_tile_occupied())
        {
            const std::shared_ptr<piece> &piece_on_tile = t->get_piece_on_tile();
            if (piece_on_tile->get_piece_alliance() == a)
                active_pieces.push_back(piece_on_tile);
        }
    }
    return active_pieces;
}

std::array<std::shared_ptr<tile>, 64> board::create_game_board(const board_builder &b)
{
    std::array<std::shared_ptr<tile>, 64> game_board;
    const std::unordered_map<int, std::shared_ptr<piece>> &board_config = b.get_board_config();
    std::unordered_map<int, std::shared_ptr<piece>>::const_iterator it;
    for (int i = 0; i < 64; i++)
    {
        it = board_config.find(i);
        // If the ith tile has a piece on it, create a tile with that piece, empty otherwise
        game_board[i] = (it != board_config.end())
                            ? tile::create_tile(i, it->second)
                            : tile::create_tile(i);
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

int board::get_half_move_clock() const
{
    return half_move_clock_;
}

int board::get_full_move_number() const
{
    return full_move_number_;
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

std::shared_ptr<move> board::get_transition_move() const
{
    return transition_move_;
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

/**
 * @details   Standard starting board:
 *
 *            |r|n|b|q|k|b|n|r|
 *            |p|p|p|p|p|p|p|p|
 *            |-|-|-|-|-|-|-|-|
 *            |-|-|-|-|-|-|-|-|
 *            |-|-|-|-|-|-|-|-|
 *            |-|-|-|-|-|-|-|-|
 *            |P|P|P|P|P|P|P|P|
 *            |R|N|B|Q|K|B|N|R|
 */
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