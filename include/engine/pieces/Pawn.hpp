#ifndef PAWN_HPP
#define PAWN_HPP

#include <engine/pieces/Piece.hpp>

class pawn final : public piece
{
private:
	static const int candidate_move_coordinates[];

public:
	pawn(const int pp, const alliance pa, const bool fm = true);

	std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
	std::shared_ptr<piece> move_piece(const move *const m) const override;
};

#endif