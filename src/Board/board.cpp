#include "../../include/board.h"

class Board
{
private:
	std::vector<std::vector<tile_t>> board;

public:
	Board()
	{
		// Initialize the board
		board.resize(8);
		for (int i = 0; i < 8; i++)
		{
			board[i].resize(8);
		}

		// Initialize the tiles
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				board[i][j].piece_color = 0;
	}
	~Board()
	{
		// Delete the board
		board.clear();
	}
};