#ifndef MOVE_HPP
#define MOVE_HPP

#include <typeinfo>
#include <string>

enum class MoveStatus
{
	DONE,
	ILLEGAL_MOVE,
	LEAVES_PLAYER_IN_CHECK
};

class Board;
class Piece;
class Rook;

class Move
{
protected:
	const Board *board;
	const Piece *movedPiece;
	const int destinationCoordinate;
	const bool isFirstMove;

	Move(Board *board, int destinationCoordinate);
	Move(Board *board, Piece *movedPiece, int destinationCoordinate);

public:
	virtual bool operator==(const Move &other) const;

	int getDestinationCoordinate() const;
	int getCurrentCoordinate() const;
	Piece *getMovedPiece() const;
	virtual bool isAttack() const;
	virtual bool isCastlingMove() const;
	virtual Piece *getAttackedPiece() const;
	virtual Board *execute() const;
	virtual std::string stringify() const;
};

class MajorMove : public Move
{
public:
	MajorMove(Board *board, Piece *movedPiece, int destinationCoordinate);

	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class AttackMove : public Move
{
private:
	const Piece *attackedPiece;

public:
	bool operator==(const Move &other) const override;

	AttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate);
	bool isAttack() const override;
	Piece *getAttackedPiece() const override;
};

class MajorAttackMove : public AttackMove
{
public:
	MajorAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate);
	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class PawnMove : public Move
{
public:
	PawnMove(Board *board, Piece *movedPiece, int destinationCoordinate);
	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class PawnAttackMove : public AttackMove
{
public:
	PawnAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate);
	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class PawnEnPassantAttackMove : public PawnAttackMove
{
public:
	PawnEnPassantAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate);
	Board *execute() const override;
	bool operator==(const Move &other) const override;
};

class PawnJump : public Move
{
public:
	PawnJump(Board *board, Piece *movedPiece, int destinationCoordinate);
	Board *execute() const override;
	std::string stringify() const override;
};

class CastleMove : public Move
{
protected:
	const Rook *castleRook;
	const int castleRookStart;
	const int castleRookDestination;

public:
	CastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination);
	bool operator==(const Move &other) const override;
	Rook *getCastleRook() const;
	bool isCastlingMove() const override;
	Board *execute() const override;
};

class KingSideCastleMove : public CastleMove
{
public:
	KingSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination);
	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class QueenSideCastleMove : public CastleMove
{
public:
	QueenSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination);
	bool operator==(const Move &other) const override;
	std::string stringify() const override;
};

class NullMove : public Move
{
public:
	NullMove();
	Board *execute() const override;
	std::string stringify() const override;
};

namespace MoveFactory
{
	Move *createMove(Board *board, int currectCoordinate, int destinationCoordinate);
} // namespace MoveFactory

#endif