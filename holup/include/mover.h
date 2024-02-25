#ifndef MOVER_H
#define MOVER_H

#include <vector>

#include "board.h"
#include "piece_tile.h"
#include "MoveHighlighter.h"

#include "MoveHighlighter.h"

typedef struct
{
	tile_t tile1, tile2;
} move_t;

class Mover
{
private:
	int moves;
	std::vector<move_t> moveStack;
	Board &board;
	move_t *currentMove;
	MoveHighlighter *highlighter;
	bool &isWhiteTurn;

public:
	Mover(Board &board, bool &isWhiteTurn);
	~Mover();
	int move(int rank, int file);
	int undo();
};

#endif