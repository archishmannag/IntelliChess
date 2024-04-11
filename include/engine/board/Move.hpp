#ifndef MOVE_H
#define MOVE_H

#include "Board.hpp"

class Piece;

class Move
{
protected:
	const Board board;
	const Piece movedPiece;
	const int destinationCoordinate;

	Move(const Board board, const Piece movedPiece, const int destinationCoordinate) : board(board), movedPiece(movedPiece), destinationCoordinate(destinationCoordinate){};
};

class MajorMove : public Move
{
public:
	MajorMove(const Board board, const Piece movedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};
};

class AttackMove : public Move
{
private:
	const Piece attackedPiece;

public:
	AttackMove(const Board board, const Piece movedPiece, const Piece attackedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate), attackedPiece(attackedPiece){};
};

#endif