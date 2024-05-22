#include <engine/Alliance.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>

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

bool AllianceUtils::isPawnPromotionSquare(const Alliance alliance, const int position)
{
	return (isBlack(alliance) && BoardUtils::EIGHTH_ROW[position]) || (isWhite(alliance) && BoardUtils::FIRST_ROW[position]);
}

const Player *AllianceUtils::choosePlayer(const Alliance alliance, Board *board)
{
	return alliance == Alliance::WHITE ? board->getWhitePlayer() : board->getBlackPlayer();
}

std::string AllianceUtils::stringify(const Alliance alliance)
{
	return alliance == Alliance::WHITE ? "White" : "Black";
}