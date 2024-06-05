#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <memory>

enum class move_status
{
	done,
	illegal_move,
	leaves_player_in_check
};

class board;
class piece;
class rook;
class pawn;

class move
{
protected:
	std::weak_ptr<board> board_;
	std::shared_ptr<piece> moved_piece_;
	const int destination_coordinate_;
	const bool is_first_move_;

	move(std::shared_ptr<board> b, int dc);
	move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);

public:
	virtual bool operator==(const move &other) const;

	int get_destination_coordinate() const;
	int get_current_coordinate() const;
	std::shared_ptr<piece> get_moved_piece() const;
	std::shared_ptr<board> get_board() const;
	virtual bool is_attack() const;
	virtual bool is_castling_move() const;
	virtual std::shared_ptr<piece> get_attacked_piece() const;
	virtual std::shared_ptr<board> execute() const;
	virtual std::string stringify() const;
};

class major_move final : public move
{
public:
	major_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);

	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class attack_move : public move
{
private:
	std::shared_ptr<piece> attacked_piece_;

public:
	bool operator==(const move &other) const override;

	attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
	bool is_attack() const override;
	std::shared_ptr<piece> get_attacked_piece() const override;
};

class pawn_promotion final : public move
{
private:
	std::shared_ptr<move> input_move_;
	std::shared_ptr<pawn> promoted_pawn_;
	std::shared_ptr<piece> promoted_piece_;

public:
	pawn_promotion(std::shared_ptr<move> im, std::shared_ptr<piece> pp);
	bool operator==(const move &other) const override;
	std::shared_ptr<board> execute() const override;
	bool is_attack() const override;
	std::shared_ptr<piece> get_attacked_piece() const override;
	std::shared_ptr<piece> get_promoted_piece() const;
	std::string stringify() const override;
};

class major_attack_move final : public attack_move
{
public:
	major_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class pawn_move final : public move
{
public:
	pawn_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);
	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class pawn_attack_move : public attack_move
{
public:
	pawn_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class pawn_en_passant_attack_move final : public pawn_attack_move
{
public:
	pawn_en_passant_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc);
	std::shared_ptr<board> execute() const override;
	bool operator==(const move &other) const override;
};

class pawn_jump final : public move
{
public:
	pawn_jump(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc);
	std::shared_ptr<board> execute() const override;
	std::string stringify() const override;
};

class castle_move : public move
{
protected:
	std::shared_ptr<rook> castling_rook_;
	const int castling_rook_start_square_;
	const int castling_rook_destination_;

public:
	castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
	bool operator==(const move &other) const override;
	std::shared_ptr<rook> get_castling_rook() const;
	bool is_castling_move() const override;
	std::shared_ptr<board> execute() const override;
};

class king_side_castle_move final : public castle_move
{
public:
	king_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class queen_side_castle_move final : public castle_move
{
public:
	queen_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd);
	bool operator==(const move &other) const override;
	std::string stringify() const override;
};

class null_move final : public move
{
public:
	null_move();
	std::shared_ptr<board> execute() const override;
	std::string stringify() const override;
};

enum class piece_type;

namespace move_factory
{
	std::shared_ptr<move> create_move(std::shared_ptr<board> b, int cc, int dc);
	std::shared_ptr<move> create_move(std::shared_ptr<board> b, int cc, int dc, piece_type ppt);
} // namespace MoveFactory

#endif