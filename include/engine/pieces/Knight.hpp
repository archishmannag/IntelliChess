#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../board/Board.hpp"

class Knight : public Piece
{
private:
	static const int CANDIDATE_MOVE_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isSecondColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isSeventhColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	Knight(const int piecePosition, const Alliance pieceAlliance);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	Knight *movePiece(const Move *move) const override;
};

#endif