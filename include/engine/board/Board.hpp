#ifndef BOARD_HPP
#define BOARD_HPP

#include "Tile.hpp"

class Board
{
public:
	Tile getTile(const int tileCoordinate) const;
};

#endif