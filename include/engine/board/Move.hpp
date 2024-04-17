#ifndef MOVE_HPP
#define MOVE_HPP

#include "Board.hpp"

class Piece;

class Move
{
protected:
	const Board board;
	const Piece movedPiece;
	const int destinationCoordinate;

	Move(Board board, Piece movedPiece, int destinationCoordinate);
};

class MajorMove : public Move
{
public:
	MajorMove(Board board, Piece movedPiece, int destinationCoordinate);
};

class AttackMove : public Move
{
private:
	const Piece attackedPiece;

public:
	AttackMove(Board board, Piece movedPiece, Piece attackedPiece, int destinationCoordinate);
};

#endif