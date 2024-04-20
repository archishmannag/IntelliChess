#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

class Queen : public Piece
{
private:
	static const int CANDIDATE_MOVE_VECTOR_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Queen(const int piecePosition, const Alliance pieceAlliance);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	Queen *movePiece(const Move *move) const override;
};

#endif