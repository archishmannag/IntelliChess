#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.hpp"
#include "../board/Board.hpp"
#include "../board/Tile.hpp"

class Knight : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

public:
	Knight(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance){};

	const std::list<Move> calculateLegalMoves(const Board board) override;
};

#endif