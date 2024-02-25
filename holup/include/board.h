#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdint>

#include "piece_tile.h"

class Board
{
private:
	int file = 5, rank = 5;
	std::vector<std::vector<tile_t>> board;

public:
	Board();
	~Board();
	void initialize();
	std::vector<std::vector<tile_t>> getBoard();
	std::vector<std::vector<tile_t>> &getBoardReference();
	int getRank();
	int getFile();
	void setRank(int rank);
	void setFile(int file);
};

#endif