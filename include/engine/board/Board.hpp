#ifndef BOARD_HPP
#define BOARD_HPP

#include <PreCompiledHeaders.hpp>

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
public: // Getters
	std::shared_ptr<board> get_previous_board() const;
	alliance get_next_move_maker() const;
	const std::unordered_map<int, std::shared_ptr<piece>> &get_board_config() const;
	std::shared_ptr<pawn> get_en_passant_pawn() const;
	std::shared_ptr<move> get_transition_move() const;
	int get_half_move_clock() const;
	int get_full_move_number() const;
	std::shared_ptr<board> build();

public: // Setters
	void set_previous_board(std::shared_ptr<board> pb);
	void set_piece(std::shared_ptr<piece> p);
	void set_en_passant_pawn(std::shared_ptr<pawn> ep);
	void set_move_maker(alliance mm);
	void set_transition_move(std::shared_ptr<move> tm);
	void set_half_move_clock(int hmc);
	void set_full_move_number(int fmn);

private:
	alliance next_move_maker_;
	std::shared_ptr<board> previous_board_ = nullptr;
	std::shared_ptr<pawn> en_passant_pawn_ = nullptr;
	std::shared_ptr<move> transition_move_ = nullptr;
	std::unordered_map<int, std::shared_ptr<piece>> board_config_;
	int half_move_clock_ = 0;
	int full_move_number_ = 1;
};

class board : public std::enable_shared_from_this<board>
{
public: // Getters
	std::shared_ptr<board> get_previous_board() const;
	std::shared_ptr<tile> get_tile(int tc) const;
	int get_half_move_clock() const;
	int get_full_move_number() const;
	std::shared_ptr<move> get_transition_move() const;
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

private: // Member functions
	std::vector<std::shared_ptr<move>> calculate_legal_moves(const std::vector<std::shared_ptr<piece>> &P);
	static std::vector<std::shared_ptr<piece>> calculate_active_pieces(const std::array<std::shared_ptr<tile>, 64> &gb, alliance a);
	static std::array<std::shared_ptr<tile>, 64> create_game_board(const board_builder &b);
	void initialize_game_board(const board_builder &b);

private: // Members
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

	int half_move_clock_ = 0;
	int full_move_number_ = 1;
};

#endif // BOARD_HPP