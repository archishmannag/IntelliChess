#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "../board/Board.hpp"

class Bishop : public Piece
{
private:
	const static int CANDIDATE_MOVE_VECTOR_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Bishop(const int piecePosition, const Alliance pieceAlliance);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
};

#endif