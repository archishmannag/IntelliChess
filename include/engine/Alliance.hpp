#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

enum class Alliance
{
	WHITE,
	BLACK
};

namespace AllianceUtils
{
	const int getDirection(const Alliance alliance);
	const bool isWhite(const Alliance alliance);
	const bool isBlack(const Alliance alliance);
}

#endif