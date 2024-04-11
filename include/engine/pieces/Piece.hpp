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

	Piece(const int piecePosition, const Alliance pieceAlliance);

public:
	virtual const std::vector<Move> calculateLegalMoves(Board &board);
	Alliance getPieceAlliance();
};

#endif