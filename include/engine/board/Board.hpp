#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <array>
#include <string>
#include <memory>

#include <engine/Alliance.hpp>

class move;
class pawn;
class tile;
class piece;
class player;
class white_player;
class black_player;
class board;

class board_builder
{
private:
	alliance next_move_maker_;
	std::shared_ptr<board> previous_board_ = nullptr;
	std::shared_ptr<pawn> en_passant_pawn_ = nullptr;
	std::shared_ptr<move> transition_move_ = nullptr;

public:
	std::map<int, std::shared_ptr<piece>> board_config_;

	void set_previous_board(std::shared_ptr<board> pb);
	void set_piece(std::shared_ptr<piece> p);
	void set_en_passant_pawn(std::shared_ptr<pawn> ep);
	void set_move_maker(alliance mm);
	void set_transition_move(std::shared_ptr<move> tm);
	std::shared_ptr<board> get_previous_board() const;
	alliance get_next_move_maker() const;
	std::shared_ptr<pawn> get_en_passant_pawn() const;
	std::shared_ptr<move> get_transition_move() const;
	std::shared_ptr<board> build();
};

class board : public std::enable_shared_from_this<board>
{
private:
	friend class board_builder;

	std::shared_ptr<board> previous_board_ = nullptr;

	std::shared_ptr<pawn> en_passant_pawn_ = nullptr;
	std::shared_ptr<move> transition_move_ = nullptr;

	std::array<std::shared_ptr<tile>, 64> game_board_;
	std::vector<std::shared_ptr<piece>> white_pieces_;
	std::vector<std::shared_ptr<piece>> black_pieces_;

	std::shared_ptr<white_player> white_player_;
	std::shared_ptr<black_player> black_player_;
	std::weak_ptr<player> current_player_;

	std::vector<std::shared_ptr<move>> calculate_legal_moves(const std::vector<std::shared_ptr<piece>> &P);
	static std::vector<std::shared_ptr<piece>> calculate_active_pieces(const std::array<std::shared_ptr<tile>, 64> &gb, alliance a);
	static std::array<std::shared_ptr<tile>, 64> create_game_board(const board_builder &b);
	void initialize_game_board(const board_builder &b);

public:
	std::shared_ptr<board> get_previous_board() const;
	std::shared_ptr<tile> get_tile(int tc) const;
	const std::vector<std::shared_ptr<piece>> &get_white_pieces() const;
	const std::vector<std::shared_ptr<piece>> &get_black_pieces() const;
	const std::vector<std::shared_ptr<piece>> get_all_pieces() const;
	std::shared_ptr<player> get_white_player() const;
	std::shared_ptr<player> get_black_player() const;
	std::shared_ptr<player> get_current_player() const;
	std::vector<std::shared_ptr<move>> get_all_legal_moves() const;
	std::shared_ptr<pawn> get_en_passant_pawn() const;
	static std::shared_ptr<board> create_standard_board();
	std::string stringify() const;
};

#endif