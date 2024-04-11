#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "../board/Board.hpp"

class Queen : public Piece
{
private:
	static const int CANDIDATE_MOVE_VECTOR_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Queen(const int piecePosition, const Alliance pieceAlliance);
	const std::vector<Move> calculateLegalMoves(Board &board) override;
};

#endif