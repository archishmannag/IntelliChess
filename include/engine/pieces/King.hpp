#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	King(const int piecePosition, const Alliance pieceAlliance);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	King *movePiece(const Move *move) const override;
};

#endif