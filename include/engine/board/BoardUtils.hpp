#ifndef BOARDUTILS_HPP
#define BOARDUTILS_HPP

namespace BoardUtils
{
	extern const bool *FIRST_COLUMN, *SECOND_COLUMN, *SEVENTH_COLUMN, *EIGHTH_COLUMN, *SECOND_ROW, *SEVENTH_ROW;

	bool isValidTileCoordinate(int coordinate);
}

#endif