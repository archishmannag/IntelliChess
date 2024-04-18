#ifndef BLACKPLAYER_HPP
#define BLACKPLAYER_HPP

#include <vector>

#include "Player.hpp"

class BlackPlayer : public Player
{
public:
	BlackPlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves);
	std::vector<Piece *> getActivePieces() override;
	Alliance getPlayerAlliance() const override;
	const Player *getOpponent() const override;
};

#endif