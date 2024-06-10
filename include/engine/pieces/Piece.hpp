#ifndef PIECE_HPP
#define PIECE_HPP

#include <PreCompiledHeaders.hpp>

#include <engine/Alliance.hpp>

class move;
class board;

enum class piece_type
{
	pawn,
	knight,
	bishop,
	rook,
	queen,
	king
};

class piece : public std::enable_shared_from_this<piece>
{
protected:
	int piece_position_;
	const alliance piece_alliance_;
	bool first_move_;
	const piece_type piece_type_;

	piece(const int pp, const alliance pa, const piece_type pt, bool fm);

public:
	bool operator==(const piece &other);

	virtual std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b);
	virtual std::shared_ptr<piece> move_piece(const move *const m) const;

	int get_piece_position() const;
	alliance get_piece_alliance() const;
	bool is_first_move() const;
	piece_type get_piece_type() const;

	int get_piece_value() const;
	std::string stringify() const;
};

#endif