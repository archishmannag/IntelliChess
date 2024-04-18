#ifndef WHITEPLAYER_HPP
#define WHITEPLAYER_HPP

#include <vector>

#include "Player.hpp"

class WhitePlayer : public Player
{
public:
	WhitePlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves);
	std::vector<Piece *> getActivePieces() override;
	Alliance getPlayerAlliance() const override;
	const Player *getOpponent() const override;
};

#endif