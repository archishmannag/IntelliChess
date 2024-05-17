#include "../../include/engine/Alliance.hpp"
#include "../../include/engine/board/Board.hpp"

int AllianceUtils::getDirection(const Alliance alliance)
{
	return alliance == Alliance::WHITE ? -1 : 1;
}

int AllianceUtils::getOppositeDirection(const Alliance alliance)
{
	return alliance == Alliance::WHITE ? 1 : -1;
}

bool AllianceUtils::isWhite(const Alliance alliance)
{
	return alliance == Alliance::WHITE;
}

bool AllianceUtils::isBlack(const Alliance alliance)
{
	return alliance == Alliance::BLACK;
}

const Player *AllianceUtils::choosePlayer(const Alliance alliance, Board *board)
{
	return alliance == Alliance::WHITE ? board->getWhitePlayer() : board->getBlackPlayer();
}