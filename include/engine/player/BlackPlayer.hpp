#ifndef BLACKPLAYER_HPP
#define BLACKPLAYER_HPP

#include <vector>

#include "Player.hpp"

class BlackPlayer : public Player
{
public:
	BlackPlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves);
	std::vector<Piece *> getActivePieces() const override;
	Alliance getPlayerAlliance() const override;
	const Player *getOpponent() const override;
	std::vector<Move *> calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const override;
	std::string stringify() const override;
};

#endif