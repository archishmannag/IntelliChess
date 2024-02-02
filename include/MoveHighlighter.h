#ifndef MOVEHIGHLIGHTER_H
#define MOVEHIGHLIGHTER_H

#include <vector>

#include "board.h"
#include "piece_tile.h"

class MoveHighlighter
{
private:
	int f, r;
	Board &board;
	std::vector<std::vector<tile_t>> &boardReference;

	void pawnMoves(int r, int f);
	void rookMoves(int r, int f);
	void knightMoves(int r, int f);
	void bishopMoves(int r, int f);
	void kingMoves(int r, int f);
	void noEnPassant();

public:
	MoveHighlighter(Board &board);
	~MoveHighlighter();
	void highlight(int r, int f);
	void noHighlight();
};

#endif