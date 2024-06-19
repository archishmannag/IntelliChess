#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <PreCompiledHeaders.hpp>

#include "../Alliance.hpp"

class board;
class move;
class king;
class move_transition;
class piece;

class player
{
public:
	player(std::shared_ptr<board> b);
	bool is_move_legal(const move *m) const;
	std::shared_ptr<king> get_player_king() const;
	const std::vector<std::shared_ptr<move>> &get_legal_moves() const;
	bool is_in_check() const;
	bool is_is_checkmate() const;
	bool is_in_stalemate() const;
	bool is_castled() const;
	bool is_castle_capable() const;
	bool is_king_side_castle_capable() const;
	bool is_queen_side_castle_capable() const;
	move_transition make_move(std::shared_ptr<move> m) const;
	move_transition unmake_move(std::shared_ptr<move> m) const;

	virtual std::vector<std::shared_ptr<piece>> get_active_pieces() const;
	virtual alliance get_player_alliance() const;
	virtual std::weak_ptr<player> get_opponent() const;
	virtual std::vector<std::shared_ptr<move>> calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const;
	virtual std::string stringify() const;

protected:
	static std::vector<std::shared_ptr<move>> calculate_attacks_on_tile(const int pp, std::vector<std::shared_ptr<move>> om);
	std::shared_ptr<king> establish_king();
	bool has_escape_coves() const;
	bool fifty_move_rule() const;

protected:
	bool checked_;
	std::weak_ptr<board> board_;
	std::shared_ptr<king> player_king_;
	std::vector<std::shared_ptr<move>> legal_moves_;
};

#endif // PLAYER_HPP