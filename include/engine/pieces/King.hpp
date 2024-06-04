#ifndef KING_HPP
#define KING_HPP

#include <engine/pieces/Piece.hpp>

class king : public piece
{
private:
	bool castled_;

	static const int candidate_move_coordinates[];

	static bool is_first_column_exclusion(const int cp, const int co);
	static bool is_eighth_column_exclusion(const int cp, const int co);

public:
	king(const int pp, const alliance pa, const bool fm = true, const bool c = false);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;
	bool is_castled() const;
};

#endif