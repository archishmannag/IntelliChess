#include "../../../include/engine/board/BoardUtils.hpp"

namespace
{
	const bool *initColumn(int columnNumber)
	{
		bool *column = new bool[64];
		do
		{
			column[columnNumber] = true;
			columnNumber += 8;
		} while (columnNumber < 64);
		return column;
	}

	const bool *initRow(int rowNumber)
	{
		bool *row = new bool[64];
		int rowStart = rowNumber * 8;
		for (int i = 0; i < 8; i++)
		{
			row[rowStart + i] = true;
		}
		return row;
	}
}

const bool *BoardUtils::FIRST_COLUMN = initColumn(0);
const bool *BoardUtils::SECOND_COLUMN = initColumn(1);
const bool *BoardUtils::SEVENTH_COLUMN = initColumn(6);
const bool *BoardUtils::EIGHTH_COLUMN = initColumn(7);

const bool *BoardUtils::SECOND_ROW = initRow(1);
const bool *BoardUtils::SEVENTH_ROW = initRow(6);

bool BoardUtils::isValidTileCoordinate(int coordinate)
{
	return coordinate >= 0 && coordinate < 64;
};
