#include <engine/board/BoardUtils.hpp>

namespace
{
	std::array<bool, 64> initColumn(int columnNumber)
	{
		std::array<bool, 64> column;
		for (int i = 0; i < 64; i++)
		{
			if (i == columnNumber)
			{
				column[i] = true;
				columnNumber += 8;
			}
			else
				column[i] = false;
		}
		return column;
	}

	std::array<bool, 64> initRow(int rowNumber)
	{
		std::array<bool, 64> row;
		int rowStart = rowNumber * 8;
		for (int i = 0; i < 64; i++)
		{
			if (i >= rowStart && i < rowStart + 8)
				row[i] = true;
			else
				row[i] = false;
		}
		return row;
	}
}

std::array<bool, 64> BoardUtils::FIRST_COLUMN = initColumn(0);
std::array<bool, 64> BoardUtils::SECOND_COLUMN = initColumn(1);
std::array<bool, 64> BoardUtils::THIRD_COLUMN = initColumn(2);
std::array<bool, 64> BoardUtils::FOURTH_COLUMN = initColumn(3);
std::array<bool, 64> BoardUtils::FIFTH_COLUMN = initColumn(4);
std::array<bool, 64> BoardUtils::SIXTH_COLUMN = initColumn(5);
std::array<bool, 64> BoardUtils::SEVENTH_COLUMN = initColumn(6);
std::array<bool, 64> BoardUtils::EIGHTH_COLUMN = initColumn(7);

std::array<bool, 64> BoardUtils::FIRST_ROW = initRow(0);
std::array<bool, 64> BoardUtils::SECOND_ROW = initRow(1);
std::array<bool, 64> BoardUtils::THIRD_ROW = initRow(2);
std::array<bool, 64> BoardUtils::FOURTH_ROW = initRow(3);
std::array<bool, 64> BoardUtils::FIFTH_ROW = initRow(4);
std::array<bool, 64> BoardUtils::SIXTH_ROW = initRow(5);
std::array<bool, 64> BoardUtils::SEVENTH_ROW = initRow(6);
std::array<bool, 64> BoardUtils::EIGHTH_ROW = initRow(7);

std::array<std::string, 64> BoardUtils::ALGEBRAIC_NOTATION = BoardUtils::initializeAlgebraicNotation();
std::map<std::string, int> BoardUtils::POSITION_TO_COORDINATE = BoardUtils::initializePositionToCoordinateMap();

bool BoardUtils::isValidTileCoordinate(int coordinate)
{
	return coordinate >= 0 && coordinate < 64;
};

int BoardUtils::getCoordinateAtPosition(std::string position)
{
	return POSITION_TO_COORDINATE.find(position)->second;
}

std::string BoardUtils::getPositionAtCoordinate(int coordinate)
{
	return ALGEBRAIC_NOTATION[coordinate];
}

std::array<std::string, 64> BoardUtils::initializeAlgebraicNotation()
{
	std::array<std::string, 64> algebraicNotation;
	int position = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			algebraicNotation[position++] = std::string(1, 'a' + j) + std::to_string(8 - i);
		}
	return algebraicNotation;
}

std::map<std::string, int> BoardUtils::initializePositionToCoordinateMap()
{
	std::map<std::string, int> positionToCoordinate;
	for (int i = 0; i < 64; i++)
		positionToCoordinate[ALGEBRAIC_NOTATION[i]] = i;
	return positionToCoordinate;
}