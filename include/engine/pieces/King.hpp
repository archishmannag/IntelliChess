#ifndef KING_HPP
#define KING_HPP

#include "../board/Board.hpp"

class King : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	King(const int piecePosition, const Alliance pieceAlliance);
	const std::vector<Move> calculateLegalMoves(Board &board) override;
};

#endif