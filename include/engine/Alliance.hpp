#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

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
}

#endif