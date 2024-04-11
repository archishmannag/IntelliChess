#include "../../../include/engine/board/BoardUtils.hpp"

const bool *BoardUtils::initColumn(int columnNumber)
{
	bool *column = new bool[64];
	do
	{
		column[columnNumber] = true;
		columnNumber += 8;
	} while (columnNumber < 64);
	return column;
}

const bool *BoardUtils::FIRST_COLUMN = BoardUtils::initColumn(0);
const bool *BoardUtils::SECOND_COLUMN = BoardUtils::initColumn(1);
const bool *BoardUtils::SEVENTH_COLUMN = BoardUtils::initColumn(6);
const bool *BoardUtils::EIGHTH_COLUMN = BoardUtils::initColumn(7);

bool isValidTileCoordinate(int coordinate)
{
	return coordinate >= 0 && coordinate < 64;
};