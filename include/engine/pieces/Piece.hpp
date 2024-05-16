#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>
#include <string>

#include "../Alliance.hpp"

class Move;
class Board;

enum class PieceType
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

class Piece
{
protected:
	int piecePosition;
	const Alliance pieceAlliance;
	bool isFirstMove;
	const PieceType pieceType;

	Piece(const int piecePosition, const Alliance pieceAlliance, const PieceType pieceType, bool isFirstMove);

public:
	bool operator==(const Piece &other);

	virtual std::vector<Move *> calculateLegalMoves(Board &board);
	virtual Piece *movePiece(const Move *move) const;

	int getPiecePosition() const;
	Alliance getPieceAlliance() const;
	bool getIsFirstMove() const;
	PieceType getPieceType() const;

	int getPieceValue() const;
	std::string stringify() const;
};

#endif