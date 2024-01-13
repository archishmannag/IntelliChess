#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <ncurses.h>
#include <vector>
#include <string>
#include <wchar.h>
#include <iostream>

#include "MoveHighlighter.h"
#include "TerminalSizeWatcher.h"

class ChessGame
{
private:
	int file = 5, rank = 5, height, width, x, y;
	WINDOW *movingWindow = NULL;

	typedef enum
	{
		pawn = 1,
		rook = 2,
		knight = 4,
		bishop = 8,
		queen = 16,
		king = 32
	} piece;

	typedef enum
	{
		isWhitePiece = 64,
		isHighlighted = 128
	} pieceFlags;

	std::vector<std::vector<square>> board = std::vector<std::vector<square>>(8, std::vector<square>(8));
	TerminalSizeWatcher *watcher;
	MoveHighlighter *highlighter;

public:
	ChessGame();
	~ChessGame();

	void initializeScreen();

	void draw();

	void input();

	void run();
};

#endif