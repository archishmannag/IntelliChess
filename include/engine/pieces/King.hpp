#ifndef KING_HPP
#define KING_HPP

#include <engine/pieces/Piece.hpp>

class King : public Piece
{
private:
	bool isCastled;

	static const int CANDIDATE_MOVE_COORDINATES[];

	static bool isFirstColumnExclusion(const int currentPosition, const int candidateOffset);
	static bool isEighthColumnExclusion(const int currentPosition, const int candidateOffset);

public:
	King(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove = true, const bool isCastled = false);

	std::vector<Move *> calculateLegalMoves(Board &board) override;
	King *movePiece(const Move *move) const override;
	bool getIsCastled() const;
};

#endif