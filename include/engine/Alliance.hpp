#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

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
	bool isWhite(Alliance alliance);
	bool isBlack(Alliance alliance);
	const Player *choosePlayer(Alliance alliance, Board *board);
}

#endif