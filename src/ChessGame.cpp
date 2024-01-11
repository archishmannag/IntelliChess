#include <ncurses.h>
#include <vector>
#include <string>
#include <wchar.h>
#include <iostream>
#include "TerminalSizeWatcher.cpp"

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
		keypad(stdscr, TRUE);

		// Initialise board array
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				board[i][j].piece_color = (i + j) % 2 ? 0 : 1 << 7;

				if (i == 1 || i == 6)
				{
					board[i][j].piece_color |= pawn;
					board[i][j].piece_color |= i == 1 ? 0 : 1 << 6;
				}
				else if (i == 0 || i == 7)
				{
					board[i][j].piece_color |=
						j == 0 || j == 7 ? piece::rook : j == 1 || j == 6 ? piece::knight
													 : j == 2 || j == 5	  ? piece::bishop
													 : j == 3			  ? piece::queen
																		  : piece::king;
					board[i][j].piece_color |= i == 0 ? 0 : 1 << 6;
				}
			}

		refresh();
	}

	void draw()
	{
		// Delete current selected cell moving window.
		if (movingWindow != NULL)
		{
			wborder(movingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
			wrefresh(movingWindow);
			delwin(movingWindow);
			movingWindow = NULL;
		}
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
		init_color(1, 933, 822, 823); // White
		init_color(2, 462, 588, 337); // Black
		init_color(3, 168, 682, 839); // Blue (selected cell)
		init_pair(1, 1, COLOR_BLACK);
		init_pair(2, 2, COLOR_BLACK);
		init_pair(3, 3, 1);
		init_pair(4, 3, 2);

		// Draw board
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if (i == rank && j == file)
					continue;
				board[i][j].piece_color & 1 << 7 ? attron(COLOR_PAIR(1)) : attron(COLOR_PAIR(2));
				for (int a = 0; a < height; a++)
				{
					mvaddch(i * height + a, j * width, ACS_CKBOARD);
					for (int b = 1; b < width; b++)
						addch(ACS_CKBOARD);
				}
				board[i][j].piece_color & 1 << 7 ? attroff(COLOR_PAIR(1)) : attroff(COLOR_PAIR(2));
			}

		// Draw selected cell moving window
		movingWindow = newwin(height, width, rank * height, file * width);
		wborder(movingWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

		refresh();
		wrefresh(movingWindow);
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
			rank--;
		}
		else if (ch == KEY_DOWN)
		{
			rank++;
		}
		else if (ch == KEY_LEFT)
		{
			file--;
		}
		else if (ch == KEY_RIGHT)
		{
			file++;
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
	}
};