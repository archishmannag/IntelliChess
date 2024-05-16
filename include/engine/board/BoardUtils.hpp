#ifndef BOARDUTILS_HPP
#define BOARDUTILS_HPP

#include <array>
#include <string>
#include <map>

namespace BoardUtils
{
	extern std::array<bool, 64> FIRST_COLUMN, SECOND_COLUMN, SEVENTH_COLUMN, EIGHTH_COLUMN, SECOND_ROW, SEVENTH_ROW;

	extern std::array<std::string, 64> ALGEBRAIC_NOTATION;
	extern std::map<std::string, int> POSITION_TO_COORDINATE;

	bool isValidTileCoordinate(int coordinate);
	int getCoordinateAtPosition(std::string position);
	std::string getPositionAtCoordinate(int coordinate);
	std::array<std::string, 64> initializeAlgebraicNotation();
	std::map<std::string, int> initializePositionToCoordinateMap();
}

#endif