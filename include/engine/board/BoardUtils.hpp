#ifndef BOARDUTILS_HPP
#define BOARDUTILS_HPP

class BoardUtils
{
private:
	BoardUtils();

	static const bool *initColumn(int columnNumber);
	static const bool *initRow(int rowNumber);

public:
	static const bool *FIRST_COLUMN, *SECOND_COLUMN, *SEVENTH_COLUMN, *EIGHTH_COLUMN, *SECOND_ROW, *SEVENTH_ROW;

	static bool isValidTileCoordinate(int coordinate);
};

#endif