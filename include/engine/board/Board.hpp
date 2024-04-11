#ifndef BOARD_H
#define BOARD_H

#include "Tile.hpp"

class Board
{
public:
	Tile getTile(const int tileCoordinate) const;
};

#endif