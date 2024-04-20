#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "../Alliance.hpp"

class Board;
class Move;
class King;
class MoveTransition;
class Piece;

class Player
{
protected:
	bool inCheck;
	Board *board;
	King *playerKing;
	std::vector<Move *> legalMoves;

	static std::vector<Move *> calculateAttacksOnTile(const int piecePosition, std::vector<Move *> opponentMoves);
	King *establishKing();
	bool hasEscapeMoves() const;

public:
	Player(Board *board);
	bool isMoveLegal(const Move *move) const;
	King *getPlayerKing() const;
	std::vector<Move *> getLegalMoves() const;
	bool isInCheck() const;
	bool isInCheckMate() const;
	bool isInStaleMate() const;
	bool isCastled() const;
	MoveTransition makeMove(Move *move) const;

	virtual std::vector<Piece *> getActivePieces() const;
	virtual Alliance getPlayerAlliance() const;
	virtual const Player *getOpponent() const;
	virtual std::vector<Move *> calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const;
};

#endif