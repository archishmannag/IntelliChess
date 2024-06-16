#ifndef KING_HPP
#define KING_HPP

#include <engine/pieces/Piece.hpp>

class king final : public piece
{
private:
	bool castled_,
		king_side_castle_capable_,
		queen_side_castle_capable_;

	static const int candidate_move_coordinates[];

	static bool is_first_column_exclusion(const int cp, const int co);
	static bool is_eighth_column_exclusion(const int cp, const int co);

public:
	king(const int pp, const alliance pa, const bool fm = true, const bool c = false, const bool ksc = true, const bool qsc = true);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;
	void set_king_side_castle_capable(const bool ksc);
	void set_queen_side_castle_capable(const bool qsc);
	bool is_castled() const;
	bool is_king_side_castle_capable() const;
	bool is_queen_side_castle_capable() const;
};

#endif