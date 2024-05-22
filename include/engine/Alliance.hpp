#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

#include <string>

class Player;
class Board;

enum class Alliance
{
	WHITE,
	BLACK
};

namespace AllianceUtils
{
	int getDirection(Alliance alliance);
	int getOppositeDirection(Alliance alliance);
	bool isWhite(Alliance alliance);
	bool isBlack(Alliance alliance);
	bool isPawnPromotionSquare(Alliance alliance, int position);
	const Player *choosePlayer(Alliance alliance, Board *board);

	std::string stringify(Alliance alliance);
}

#endif