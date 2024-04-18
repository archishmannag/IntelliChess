#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "../pieces/King.hpp"
#include "../board/MoveTransition.hpp"

class Board;
class Move;

class Player
{
private:
	const bool inCheck;

	King *establishKing();
	static std::vector<Move *> calculateAttacksOnTile(const int piecePosition, std::vector<Move *> opponentMoves);

protected:
	const Board *board;
	const King *playerKing;
	std::vector<Move *> legalMoves;

	bool hasEscapeMoves() const;

public:
	Player(Board *board, std::vector<Move *> legalMoves, std::vector<Move *> opponentMoves);
	bool isMoveLegal(const Move *move) const;
	const King *getPlayerKing() const;
	std::vector<Move *> getLegalMoves() const;
	bool isInCheck() const;
	bool isInCheckMate() const;
	bool isInStaleMate() const;
	bool isCastled() const;
	MoveTransition makeMove(Move *move) const;

	virtual std::vector<Piece *> getActivePieces();
	virtual Alliance getPlayerAlliance() const;
	virtual const Player *getOpponent() const;
};

#endif