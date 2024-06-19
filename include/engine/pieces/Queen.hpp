#ifndef QUEEN_HPP
#define QUEEN_HPP

#include <engine/pieces/Piece.hpp>

class queen final : public piece
{
public:
	queen(const int pp, const alliance pa, const bool fm = true);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;

private:
	static bool is_first_column_exclusion(const int cp, const int co);
	static bool is_eighth_column_exclusion(const int cp, const int co);

private:
	static const int candidate_move_vector_coordinates[];
};

#endif // QUEEN_HPP