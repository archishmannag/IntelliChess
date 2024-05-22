#ifndef PAWN_HPP
#define PAWN_HPP

#include <engine/pieces/Piece.hpp>

class Pawn : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

public:
	Pawn(const int piecePosition, const Alliance pieceAlliance);
	Pawn(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	Pawn *movePiece(const Move *move) const override;
};

#endif