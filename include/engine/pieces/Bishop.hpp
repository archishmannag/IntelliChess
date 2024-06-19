#ifndef BISHOP_HPP
#define BISHOP_HPP

#include <engine/pieces/Piece.hpp>

class bishop final : public piece
{
public:
	bishop(const int pp, const alliance pa, const bool fm = true);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;

private:
	static bool is_first_column_exclusion(const int cp, const int co);
	static bool is_eighth_column_exclusion(const int cp, const int co);

private:
	const static int candidate_move_vector_coordinates[];
};

#endif // BISHOP_HPP