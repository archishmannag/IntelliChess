#ifndef ROOK_HPP
#define ROOK_HPP

#include <engine/pieces/Piece.hpp>

class rook final : public piece
{
private:
	static const int candidate_move_vector_coordinates[];

	static bool is_first_column_exclusion(const int cp, const int co);
	static bool is_eighth_column_exclusion(const int cp, const int co);

public:
	rook(const int pp, const alliance pa, const bool fm = true);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;
};

#endif