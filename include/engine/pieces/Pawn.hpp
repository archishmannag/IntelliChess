#ifndef PAWN_HPP
#define PAWN_HPP

#include "../board/Board.hpp"

class Pawn : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

public:
	Pawn(const int piecePosition, const Alliance pieceAlliance);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	Pawn *movePiece(const Move *move) const override;
};

#endif