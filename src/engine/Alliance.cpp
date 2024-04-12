#include "../../include/engine/Alliance.hpp"

const int AllianceUtils::getDirection(const Alliance alliance)
{
	return alliance == Alliance::WHITE ? -1 : 1;
}

const bool AllianceUtils::isWhite(const Alliance alliance)
{
	return alliance == Alliance::WHITE;
}

const bool AllianceUtils::isBlack(const Alliance alliance)
{
	return alliance == Alliance::BLACK;
}