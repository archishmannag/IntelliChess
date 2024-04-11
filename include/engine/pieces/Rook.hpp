#ifndef ROOK_HPP
#define ROOK_HPP

#include "../board/Board.hpp"

class Rook : public Piece
{
private:
	static const int CANDIDATE_MOVE_VECTOR_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Rook(const int piecePosition, const Alliance pieceAlliance);
	const std::vector<Move> calculateLegalMoves(Board &board) override;
};

#endif