#ifndef WHITEPLAYER_HPP
#define WHITEPLAYER_HPP

#include <vector>

#include "Player.hpp"

class WhitePlayer : public Player
{
public:
	WhitePlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves);
	std::vector<Piece *> getActivePieces() const override;
	Alliance getPlayerAlliance() const override;
	const Player *getOpponent() const override;
	std::vector<Move *> calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const override;
};

#endif