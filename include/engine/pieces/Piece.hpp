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
	const int piecePosition;
	const Alliance pieceAlliance;
	const bool isFirstMove;
	PieceType pieceType;

	Piece(const int piecePosition, const Alliance pieceAlliance);

public:
	virtual std::vector<Move *> calculateLegalMoves(Board &board);
	int getPiecePosition() const;
	Alliance getPieceAlliance() const;
	bool getIsFirstMove() const;
	std::string stringify() const;
};

#endif