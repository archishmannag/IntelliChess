#include "../../include/engine/Alliance.hpp"

int AllianceUtils::getDirection(const Alliance alliance)
{
	return alliance == Alliance::WHITE ? -1 : 1;
}

bool AllianceUtils::isWhite(const Alliance alliance)
{
	return alliance == Alliance::WHITE;
}

bool AllianceUtils::isBlack(const Alliance alliance)
{
	return alliance == Alliance::BLACK;
}