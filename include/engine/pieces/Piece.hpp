#ifndef PIIECE_H
#define PIECE_H

#include <list>

#include "../Alliance.hpp"
#include "../board/Board.hpp"
#include "../board/Move.hpp"

class Piece
{
protected:
	const int piecePosition;
	const Alliance pieceAlliance;

	Piece(const int piecePosition, const Alliance pieceAlliance) : piecePosition(piecePosition), pieceAlliance(pieceAlliance){};

public:
	virtual const std::list<Move> calculateLegalMoves(const Board board);
	Alliance getPieceAlliance();
};

#endif