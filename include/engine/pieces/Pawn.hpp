#ifndef PAWN_HPP
#define PAWN_HPP

#include "../board/Board.hpp"

class Pawn : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

public:
	Pawn(const int piecePosition, const Alliance pieceAlliance);
	const std::vector<Move> calculateLegalMoves(Board &board) override;
};

#endif