#ifndef KNIGHT_H
#define KNIGHT_H

#include "../board/Board.hpp"
#include "../board/BoardUtils.hpp"
#include "Piece.hpp"

class Knight : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isSecondColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isSeventhColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Knight(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance){};

	const std::list<Move> calculateLegalMoves(Board &board) override;
};

#endif