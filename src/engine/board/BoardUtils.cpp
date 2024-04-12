#include <stdexcept>

#include "../../../include/engine/board/BoardUtils.hpp"

BoardUtils::BoardUtils()
{
	throw std::runtime_error("Cannot instantiate BoardUtils");
}

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

const bool *BoardUtils::initRow(int rowNumber)
{
	bool *row = new bool[64];
	int rowStart = rowNumber * 8;
	for (int i = 0; i < 8; i++)
	{
		row[rowStart + i] = true;
	}
	return row;
}

const bool *BoardUtils::FIRST_COLUMN = BoardUtils::initColumn(0);
const bool *BoardUtils::SECOND_COLUMN = BoardUtils::initColumn(1);
const bool *BoardUtils::SEVENTH_COLUMN = BoardUtils::initColumn(6);
const bool *BoardUtils::EIGHTH_COLUMN = BoardUtils::initColumn(7);

const bool *BoardUtils::SECOND_ROW = BoardUtils::initRow(1);
const bool *BoardUtils::SEVENTH_ROW = BoardUtils::initRow(6);

bool isValidTileCoordinate(int coordinate)
{
	return coordinate >= 0 && coordinate < 64;
};