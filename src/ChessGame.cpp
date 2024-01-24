#include "ChessGame.h"

ChessGame::ChessGame()
{
	// Start the terminal size watcher function.
	watcher = new TerminalSizeWatcher();
	highlighter = new MoveHighlighter(&board);
	initializeScreen();
	run();
}

ChessGame::~ChessGame()
{
	// Delete the terminal size watcher object.
	delete watcher;
	// Delete the moving window.
	if (movingWindow != NULL)
	{
		wborder(movingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(movingWindow);
		delwin(movingWindow);
	}
	// Delete the ncurses screen.
	endwin();
}

void ChessGame::initializeScreen()
{
	// Initialize ncurses
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	noecho();
	timeout(-1);
	keypad(stdscr, TRUE);

	// Initialize board colours
	start_color();
	init_color(1, 933, 822, 823); // White
	init_color(2, 462, 588, 337); // Black
	init_color(3, 969, 700, 650); // Yellow (highlighted opponent piece)
	init_pair(1, 1, COLOR_BLACK);
	init_pair(2, 2, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);

	// Initialise board array
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			// if (i == 1 || i == 6)
			// {
			// 	board[i][j].piece_color |= piece::pawn;
			// 	board[i][j].piece_color |= i == 1 ? 0 : pieceFlags::isWhitePiece;
			// } else
			if (i == 0 || i == 7)
			{
				board[i][j].piece_color |=
					j == 0 || j == 7 ? piece::rook : j == 1 || j == 6 ? piece::knight
												 : j == 2 || j == 5	  ? piece::bishop
												 : j == 3			  ? piece::queen
																	  : piece::king;
				board[i][j].piece_color |= i == 0 ? 0 : pieceFlags::isWhitePiece;
			}
		}
	board[3][3].piece_color |= piece::pawn | pieceFlags::isWhitePiece;
	board[3][2].piece_color |= piece::pawn;
	board[3][4].piece_color |= piece::pawn;
	board[4][5].piece_color |= piece::pawn;
	board[4][6].piece_color |= piece::pawn | pieceFlags::isWhitePiece;
	board[4][4].piece_color |= piece::pawn | pieceFlags::isWhitePiece;
}

void ChessGame::draw()
{
	// Getting the current position of the highlighter
	int f, r;
	highlighter->getCurrentPosition(f, r);

	// Delete current selected cell moving window.
	if (movingWindow != NULL)
	{
		wborder(movingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(movingWindow);
		delwin(movingWindow);
		movingWindow = NULL;
	}
	clear();
	// Check terminal size
	watcher->getDimensions(&x, &y);

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

	// Draw board
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			// ontinue for here, the another window will be drawn to show highlighted cell
			if (i == rank && j == file)
				continue;

			// Turn on colours
			if (board[i][j].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
					attron(COLOR_PAIR(4));
				else
					attron(COLOR_PAIR(3));
			}
			else if ((i + j) % 2)
				attron(COLOR_PAIR(2));
			else
				attron(COLOR_PAIR(1));

			for (int a = 0; a < height / 2; a++)
			{
				mvaddch(i * height + a, j * width, ACS_CKBOARD);
				for (int b = 1; b < width; b++)
					addch(ACS_CKBOARD);
			}
			mvaddch(i * height + height / 2, j * width, ACS_CKBOARD);
			for (int b = 1; b < (width - 1) / 2; b++)
				addch(ACS_CKBOARD);

			if (board[i][j].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
					attroff(COLOR_PAIR(4));
				else
					attroff(COLOR_PAIR(3));
			}
			else if ((i + j) % 2)
				attroff(COLOR_PAIR(2));
			else
				attroff(COLOR_PAIR(1));

			if (board[i][j].piece_color & pieceFlags::isWhitePiece)
			{
				switch (board[i][j].piece_color & 0b111111)
				{
				case piece::pawn:
					printw("♙");
					break;
				case piece::rook:
					printw("♖");
					break;
				case piece::knight:
					printw("♘");
					break;
				case piece::bishop:
					printw("♗");
					break;
				case piece::queen:
					printw("♕");
					break;
				case piece::king:
					printw("♔");
					break;
				default:
					if (board[i][j].piece_color & pieceFlags::isHighlighted)
					{
						if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
							attron(COLOR_PAIR(4));
						else
							attron(COLOR_PAIR(3));
					}
					else if ((i + j) % 2)
						attron(COLOR_PAIR(2));
					else
						attron(COLOR_PAIR(1));
					addch(ACS_CKBOARD);
					addch(ACS_CKBOARD);
				}
			}
			else
			{
				switch (board[i][j].piece_color & 0b111111)
				{
				case piece::pawn:
					printw("♟");
					break;
				case piece::rook:
					printw("♜");
					break;
				case piece::knight:
					printw("♞");
					break;
				case piece::bishop:
					printw("♝");
					break;
				case piece::queen:
					printw("♛");
					break;
				case piece::king:
					printw("♚");
					break;
				default:
					if (board[i][j].piece_color & pieceFlags::isHighlighted)
					{
						if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
							attron(COLOR_PAIR(4));
						else
							attron(COLOR_PAIR(3));
					}
					else if ((i + j) % 2)
						attron(COLOR_PAIR(2));
					else
						attron(COLOR_PAIR(1));
					addch(ACS_CKBOARD);
					addch(ACS_CKBOARD);
				}
			}

			if (board[i][j].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
					attron(COLOR_PAIR(4));
				else
					attron(COLOR_PAIR(3));
			}
			else if ((i + j) % 2)
				attron(COLOR_PAIR(2));
			else
				attron(COLOR_PAIR(1));

			mvaddch(i * height + height / 2, j * width + (width + 3) / 2, ACS_CKBOARD);
			for (int b = 1; b < (width - 1) / 2; b++)
				addch(ACS_CKBOARD);

			for (int a = 0; a < (height - 1) / 2; a++)
			{
				mvaddch(i * height + height / 2 + 1 + a, j * width, ACS_CKBOARD);
				for (int b = 1; b < width; b++)
					addch(ACS_CKBOARD);
			}

			if (board[i][j].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[i][j].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[i][j].piece_color & 0b111111)) || board[i][j].piece_color & pieceFlags::enPassant)
					attroff(COLOR_PAIR(4));
				else
					attroff(COLOR_PAIR(3));
			}
			else if ((i + j) % 2)
				attroff(COLOR_PAIR(2));
			else
				attroff(COLOR_PAIR(1));
		}

	// Draw selected cell moving window borders
	movingWindow = newwin(height, width, rank * height, file * width);
	wbkgd(movingWindow, COLOR_PAIR(3) | A_BOLD);
	wborder(movingWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	// Draw selected cell moving window
	if (board[rank][file].piece_color & pieceFlags::isHighlighted)
	{
		if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
			wattron(movingWindow, COLOR_PAIR(4));
		else
			wattron(movingWindow, COLOR_PAIR(3));
	}
	else if ((rank + file) % 2)
		wattron(movingWindow, COLOR_PAIR(2));
	else
		wattron(movingWindow, COLOR_PAIR(1));

	for (int a = 0; a < (height - 2) / 2; a++)
	{
		mvwaddch(movingWindow, a + 1, 1, ACS_CKBOARD);
		for (int b = 1; b < width - 2; b++)
			waddch(movingWindow, ACS_CKBOARD);
	}
	mvwaddch(movingWindow, (height - 2) / 2 + 1, 1, ACS_CKBOARD);
	for (int b = 1; b < (width - 2) / 2 - 1; b++)
		waddch(movingWindow, ACS_CKBOARD);

	if (board[rank][file].piece_color & pieceFlags::isHighlighted)
	{
		if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
			wattroff(movingWindow, COLOR_PAIR(4));
		else
			wattroff(movingWindow, COLOR_PAIR(3));
	}
	else if ((rank + file) % 2)
		wattroff(movingWindow, COLOR_PAIR(2));
	else
		wattroff(movingWindow, COLOR_PAIR(1));

	if (board[rank][file].piece_color & pieceFlags::isWhitePiece)
	{
		switch (board[rank][file].piece_color & 0b111111)
		{
		case piece::pawn:
			wprintw(movingWindow, "♙");
			break;
		case piece::rook:
			wprintw(movingWindow, "♖");
			break;
		case piece::knight:
			wprintw(movingWindow, "♘");
			break;
		case piece::bishop:
			wprintw(movingWindow, "♗");
			break;
		case piece::queen:
			wprintw(movingWindow, "♕");
			break;
		case piece::king:
			wprintw(movingWindow, "♔");
			break;
		default:
			if (board[rank][file].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
					wattron(movingWindow, COLOR_PAIR(4));
				else
					wattron(movingWindow, COLOR_PAIR(3));
			}
			else if ((rank + file) % 2)
				wattron(movingWindow, COLOR_PAIR(2));
			else
				wattron(movingWindow, COLOR_PAIR(1));
			waddch(movingWindow, ACS_CKBOARD);
			waddch(movingWindow, ACS_CKBOARD);
		}
	}
	else
	{
		switch (board[rank][file].piece_color & 0b111111)
		{
		case piece::pawn:
			wprintw(movingWindow, "♟");
			break;
		case piece::rook:
			wprintw(movingWindow, "♜");
			break;
		case piece::knight:
			wprintw(movingWindow, "♞");
			break;
		case piece::bishop:
			wprintw(movingWindow, "♝");
			break;
		case piece::queen:
			wprintw(movingWindow, "♛");
			break;
		case piece::king:
			wprintw(movingWindow, "♚");
			break;
		default:
			if (board[rank][file].piece_color & pieceFlags::isHighlighted)
			{
				if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
					wattron(movingWindow, COLOR_PAIR(4));
				else
					wattron(movingWindow, COLOR_PAIR(3));
			}
			else if ((rank + file) % 2)
				wattron(movingWindow, COLOR_PAIR(2));
			else
				wattron(movingWindow, COLOR_PAIR(1));
			waddch(movingWindow, ACS_CKBOARD);
			waddch(movingWindow, ACS_CKBOARD);
		}
	}

	if (board[rank][file].piece_color & pieceFlags::isHighlighted)
	{
		if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
			wattron(movingWindow, COLOR_PAIR(4));
		else
			wattron(movingWindow, COLOR_PAIR(3));
	}
	else if ((rank + file) % 2)
		wattron(movingWindow, COLOR_PAIR(2));
	else
		wattron(movingWindow, COLOR_PAIR(1));

	mvwaddch(movingWindow, (height - 2) / 2 + 1, 2 + (width - 2) / 2, ACS_CKBOARD);
	for (int b = 1; b < (width - 2) / 2 - 1; b++)
		waddch(movingWindow, ACS_CKBOARD);

	for (int a = 0; a < (height - 2) / 2 - 1; a++)
	{
		mvwaddch(movingWindow, (height - 2) / 2 + 2 + a, 1, ACS_CKBOARD);
		for (int b = 1; b < width - 2; b++)
			waddch(movingWindow, ACS_CKBOARD);
	}

	if (board[rank][file].piece_color & pieceFlags::isHighlighted)
	{
		if ((((board[rank][file].piece_color ^ board[r][f].piece_color) & pieceFlags::isWhitePiece) && (board[rank][file].piece_color & 0b111111)) || board[rank][file].piece_color & pieceFlags::enPassant)
			wattroff(movingWindow, COLOR_PAIR(4));
		else
			wattroff(movingWindow, COLOR_PAIR(3));
	}
	else if ((rank + file) % 2)
		wattroff(movingWindow, COLOR_PAIR(2));
	else
		wattroff(movingWindow, COLOR_PAIR(1));

	refresh();
	wrefresh(movingWindow);
}

void ChessGame::input()
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
		if (rank > 0)
			rank--;
	}
	else if (ch == KEY_DOWN)
	{
		if (rank < 7)
			rank++;
	}
	else if (ch == KEY_LEFT)
	{
		if (file > 0)
			file--;
	}
	else if (ch == KEY_RIGHT)
	{
		if (file < 7)
			file++;
	}
	else if (ch == ' ')
	{
		highlighter->toggleHighlight(file, rank);
	}
}

void ChessGame::run()
{
	while (true)
	{
		draw();
		input();
		// process();
	}
}
