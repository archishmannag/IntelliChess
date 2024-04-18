#ifndef MOVE_HPP
#define MOVE_HPP

#include "Board.hpp"

enum class MoveStatus
{
	DONE,
	ILLEGAL_MOVE,
	LEAVES_PLAYER_IN_CHECK
};

class Piece;

class Move
{
protected:
	const Board board;
	const Piece movedPiece;
	const int destinationCoordinate;

	Move(Board board, Piece movedPiece, int destinationCoordinate);

public:
	int getDestinationCoordinate() const;
	virtual Board *execute() const;
};

class MajorMove : public Move
{
public:
	MajorMove(Board board, Piece movedPiece, int destinationCoordinate);
	Board *execute() const override;
};

class AttackMove : public Move
{
private:
	const Piece attackedPiece;

public:
	AttackMove(Board board, Piece movedPiece, Piece attackedPiece, int destinationCoordinate);
	Board *execute() const override;
};

#endif