#include "MoveHighlighter.h"

MoveHighlighter::MoveHighlighter(std::vector<std::vector<square>> *b)
{
	this->board = b;
}
MoveHighlighter::~MoveHighlighter()
{
}

/*
	This function toggles the highlighted cells based on the available moves. It takes the current cell as the input and computes the moves, then highlights them. If the cell is already highlighted, it removes the highlight.

	f = Current file
	r = Current rank
*/
void MoveHighlighter::toggleHighlight(int f, int r)
{
	// * Test - Highlight current cell
	(*board)[f][r].piece_color ^= 1 << 7;
}