#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

class Bishop : public Piece
{
private:
	const static int CANDIDATE_MOVE_VECTOR_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Bishop(const int piecePosition, const Alliance pieceAlliance);
	Bishop(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	Bishop *movePiece(const Move *move) const override;
};

#endif