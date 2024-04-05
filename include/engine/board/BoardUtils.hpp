#ifndef BOARDUTILS_H
#define BOARDUTILS_H

class BoardUtils
{
private:
	BoardUtils() = delete;
	~BoardUtils() = delete;

	static const bool *initColumn(int columnNumber);

public:
	static const bool *FIRST_COLUMN, *SECOND_COLUMN, *SEVENTH_COLUMN, *EIGHTH_COLUMN;

	static bool isValidTileCoordinate(int coordinate);
};

#endif