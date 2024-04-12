#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

#include "../Alliance.hpp"

class Move;
class Board;

class Piece
{
protected:
	const int piecePosition;
	const Alliance pieceAlliance;
	const bool isFirstMove;

	Piece(const int piecePosition, const Alliance pieceAlliance);

public:
	virtual const std::vector<Move> calculateLegalMoves(Board &board);
	int getPiecePosition() const;
	Alliance getPieceAlliance() const;
	bool getIsFirstMove() const;
};

#endif