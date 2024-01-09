#include <ncurses.h>
#include <vector>
#include <string>
#include <wchar.h>
#include <iostream>
#include "TerminalSizeWatcher.cpp"

class ChessGame
{
private:
	int file, rank, height, width, x, y;
	WINDOW *movingWindow;
	typedef enum
	{
		pawn = 1,
		rook = 2,
		knight = 4,
		bishop = 8,
		queen = 16,
		king = 32
	} piece;
	typedef struct
	{
		uint8_t piece_color;
	} square;
	square board[8][8];
	TerminalSizeWatcher *watcher;

public:
	ChessGame()
	{
		watcher = new TerminalSizeWatcher(x, y);
		initializeScreen();
		run();
	}
	~ChessGame()
	{
		endwin();
	}
	void initializeScreen()
	{
		// Initialize ncurses
		initscr();
		cbreak();
		noecho();
		timeout(0);
		keypad(stdscr, TRUE);

		// Initialize moving window for selecting and moving pieces
		movingWindow = newwin(height, width, 4 * height, 4 * width);

		// Initialise board array
		for (rank = 0; rank < 8; rank++)
			for (file = 0; file < 8; file++)
			{
				board[rank][file].piece_color = (rank + file) % 2 ? 0 : 1 << 7;

				if (rank == 1 || rank == 6)
				{
					board[rank][file].piece_color |= pawn;
					board[rank][file].piece_color |= rank == 1 ? 0 : 1 << 6;
				}
				else if (rank == 0 || rank == 7)
				{
					board[rank][file].piece_color |=
						file == 0 || file == 7 ? piece::rook : file == 1 || file == 6 ? piece::knight
														   : file == 2 || file == 5	  ? piece::bishop
														   : file == 3				  ? piece::queen
																					  : piece::king;
					board[rank][file].piece_color |= rank == 0 ? 0 : 1 << 6;
				}
			}

		refresh();
	}

	/*
		The draw function draws the board on the screen. It calculates the terminal size and draws the board accordingly.
	*/
	void draw()
	{
		// Check terminal size
		watcher->checkTerminalSize();

		if (x < 80 || y < 24)
		{
			mvprintw(y / 2, x / 2 - 10, "Terminal size must be at least 80x24");
			mvprintw(y / 2 + 1, x / 2 - 10, "Current size: %dx%d", x, y);
			refresh();
			return;
		}
		else if (x > 2 * y)
		{
			height = y / 8;
			width = 2 * height;
		}
		else
		{
			width = x / 8;
			height = width / 2;
		}

		// Initialize board colour
		start_color();
		init_color(1, 933, 822, 823);
		init_color(2, 462, 588, 337);
		init_pair(1, 1, COLOR_BLACK);
		init_pair(2, 2, COLOR_BLACK);

		// Draw board
		for (rank = 0; rank < 8; rank++)
			for (file = 0; file < 8; file++)
			{
				board[rank][file].piece_color & 1 << 7 ? attron(COLOR_PAIR(1)) : attron(COLOR_PAIR(2));
				for (int i = 0; i < height; i++)
				{
					mvaddch(rank * height + i, file * width, ACS_CKBOARD);
					for (int j = 1; j < width; j++)
						addch(ACS_CKBOARD);
				}
				board[rank][file].piece_color & 1 << 7 ? attroff(COLOR_PAIR(1)) : attroff(COLOR_PAIR(2));
			}
		refresh();
	}

	void input()
	{
		int ch;
		ch = getch();
		if (ch == 'q')
		{
			this->~ChessGame();
			exit(0);
		}
		else if (ch == KEY_UP)
		{
		}
		else if (ch == KEY_DOWN)
		{
		}
		else if (ch == KEY_LEFT)
		{
		}
		else if (ch == KEY_RIGHT)
		{
		}
		else if (ch == ' ')
		{
		}
	}

	void run()
	{
		while (true)
		{
			draw();
			input();
			// process();
		}
		getch();
	}
};