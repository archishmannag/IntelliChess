#include "../../include/screen.h"

Screen::Screen(Board &board, Clock &clock, bool &isWhiteTurn) : board(board), clock(clock), isWhiteTurn(isWhiteTurn)
{
	watcher = new TerminalSizeWatcher();
	initializeScreen();
	isRunning = true;
	screenThread = std::thread(&Screen::displayScreen, this);
}

Screen::~Screen()
{
	isRunning = false;
	delete watcher;
	if (movingWindow != NULL)
	{
		wborder(movingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(movingWindow);
		delwin(movingWindow);
	}
	endwin();
	screenThread.join();
}

void Screen::initializeScreen()
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
	init_color(2, 462, 588, 337); // Green
	init_pair(1, 1, COLOR_BLACK);
	init_pair(2, 2, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
}

void Screen::displayScreen()
{
	while (isRunning)
	{
		draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void Screen::draw()
{
	// Delete current selected window
	if (movingWindow != NULL)
	{
		wborder(movingWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(movingWindow);
		delwin(movingWindow);
	}

	// Get terminal size
	watcher->getDimensions(&x, &y);

	if (!((height == (y - 2) / 8 && width == 2 * height) || (width == (x - 10) / 8 && height == width / 2)))
		clear();
	if (x < 80 || y < 24)
	{
		mvprintw(y / 2, x / 2 - 10, "Terminal size must be at least 80x24");
		mvprintw(y / 2 + 1, x / 2 - 10, "Current size: %dx%d", x, y);
		refresh();
		return;
	}
	else if ((x - 10) > 2 * (y - 2))
	{
		height = (y - 2) / 8;
		width = 2 * height;
	}
	else
	{
		width = (x - 10) / 8;
		height = width / 2;
	}

	// Draw board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// Continue if moving window is here
			if (i == board.getRank() && j == board.getFile())
				continue;

			// Draw tile
			attrOn(i, j);

			for (int a = 0; a < height / 2; a++)
			{
				mvaddch(i * height + a, j * width, ACS_CKBOARD);
				for (int b = 1; b < width; b++)
					addch(ACS_CKBOARD);
			}

			mvaddch(i * height + height / 2, j * width, ACS_CKBOARD);
			for (int b = 1; b < (width - 1) / 2; b++)
				addch(ACS_CKBOARD);

			attrOff(i, j);

			if (board.getBoard()[i][j].state & otherFlags::isOccupied)
			{
				if (board.getBoard()[i][j].state & pieceFlags::isWhitePiece)
				{
					switch (board.getBoard()[i][j].state & 0b111111)
					{
					case pieceFlags::pawn:
						printw("♟");
						break;
					case pieceFlags::rook:
						printw("♜");
						break;
					case pieceFlags::knight:
						printw("♞");
						break;
					case pieceFlags::bishop:
						printw("♝");
						break;
					case pieceFlags::queen:
						printw("♛");
						break;
					case pieceFlags::king:
						printw("♚");
						break;
					}
				}
				else
				{
					switch (board.getBoard()[i][j].state & 0b111111)
					{
					case pieceFlags::pawn:
						printw("♙");
						break;
					case pieceFlags::rook:
						printw("♖");
						break;
					case pieceFlags::knight:
						printw("♘");
						break;
					case pieceFlags::bishop:
						printw("♗");
						break;
					case pieceFlags::queen:
						printw("♕");
						break;
					case pieceFlags::king:
						printw("♔");
						break;
					}
				}
			}
			else
			{
				attrOn(i, j);
				addch(ACS_CKBOARD);
				addch(ACS_CKBOARD);
			}

			attrOn(i, j);

			mvaddch(i * height + height / 2, j * width + width / 2 + 1, ACS_CKBOARD);
			for (int b = width / 2 + 2; b < width; b++)
				addch(ACS_CKBOARD);

			for (int a = 0; a < (height - 1) / 2; a++)
			{
				mvaddch(i * height + height / 2 + 1 + a, j * width, ACS_CKBOARD);
				for (int b = 1; b < width; b++)
					addch(ACS_CKBOARD);
			}

			attrOff(i, j);
		}
	}

	// Draw moving window
	movingWindow = newwin(height, width, board.getRank() * height, board.getFile() * width);
	wbkgd(movingWindow, COLOR_PAIR(3) | A_BOLD);
	wborder(movingWindow, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

	wattrOn(movingWindow, board.getRank(), board.getFile());

	for (int a = 0; a < (height - 2) / 2; a++)
	{
		mvwaddch(movingWindow, a + 1, 1, ACS_CKBOARD);
		for (int b = 1; b < (width - 2); b++)
			waddch(movingWindow, ACS_CKBOARD);
	}

	mvwaddch(movingWindow, (height - 2) / 2 + 1, 1, ACS_CKBOARD);
	for (int b = 1; b < (width - 2) / 2 - 1; b++)
		waddch(movingWindow, ACS_CKBOARD);

	wattrOff(movingWindow, board.getRank(), board.getFile());

	if (board.getBoard()[board.getRank()][board.getFile()].state & otherFlags::isOccupied)
	{
		if (board.getBoard()[board.getRank()][board.getFile()].state & pieceFlags::isWhitePiece)
		{
			switch (board.getBoard()[board.getRank()][board.getFile()].state & 0b111111)
			{
			case pieceFlags::pawn:
				wprintw(movingWindow, "♟");
				break;
			case pieceFlags::rook:
				wprintw(movingWindow, "♜");
				break;
			case pieceFlags::knight:
				wprintw(movingWindow, "♞");
				break;
			case pieceFlags::bishop:
				wprintw(movingWindow, "♝");
				break;
			case pieceFlags::queen:
				wprintw(movingWindow, "♛");
				break;
			case pieceFlags::king:
				wprintw(movingWindow, "♚");
				break;
			}
		}
		else
		{
			switch (board.getBoard()[board.getRank()][board.getFile()].state & 0b111111)
			{
			case pieceFlags::pawn:
				wprintw(movingWindow, "♙");
				break;
			case pieceFlags::rook:
				wprintw(movingWindow, "♖");
				break;
			case pieceFlags::knight:
				wprintw(movingWindow, "♘");
				break;
			case pieceFlags::bishop:
				wprintw(movingWindow, "♗");
				break;
			case pieceFlags::queen:
				wprintw(movingWindow, "♕");
				break;
			case pieceFlags::king:
				wprintw(movingWindow, "♔");
				break;
			}
		}
	}
	else
	{
		wattrOn(movingWindow, board.getRank(), board.getFile());
		waddch(movingWindow, ACS_CKBOARD);
		waddch(movingWindow, ACS_CKBOARD);
	}

	wattrOn(movingWindow, board.getRank(), board.getFile());

	mvwaddch(movingWindow, (height - 2) / 2 + 1, (width - 2) / 2 + 1, ACS_CKBOARD);
	for (int b = (width - 2) / 2 + 1; b < (width - 2); b++)
		waddch(movingWindow, ACS_CKBOARD);

	for (int a = 0; a < (height - 2) / 2; a++)
	{
		mvwaddch(movingWindow, (height - 2) / 2 + 2 + a, 1, ACS_CKBOARD);
		for (int b = 1; b < width - 2; b++)
			waddch(movingWindow, ACS_CKBOARD);
	}

	wattrOff(movingWindow, board.getRank(), board.getFile());

	// Draw clock
	if ((x - 10) > 2 * (y - 2))
	{
		mvprintw(y / 4, x - 7, "White");
		mvprintw(y / 4 + 1, x - 9, "%02d:%02d:%01d", clock.getWhiteMinute(), clock.getWhiteSecond(), clock.getWhiteMilliSecond() / 100);
		mvprintw((3 * y) / 4, x - 7, "Black");
		mvprintw((3 * y) / 4 + 1, x - 9, "%02d:%02d:%01d", clock.getBlackMinute(), clock.getBlackSecond(), clock.getBlackMilliSecond() / 100);
	}
	else
	{
		mvprintw(y - 2, x / 4 - 2, "White");
		mvprintw(y - 2, (3 * x) / 4 - 2, "Black");
		mvprintw(y - 1, x / 4 - 4, "%02d:%02d:%01d", clock.getWhiteMinute(), clock.getWhiteSecond(), clock.getWhiteMilliSecond() / 100);
		mvprintw(y - 1, (3 * x) / 4 - 4, "%02d:%02d:%01d", clock.getBlackMinute(), clock.getBlackSecond(), clock.getBlackMilliSecond() / 100);
	}

	refresh();
	wrefresh(movingWindow);
}

void Screen::wattrOn(WINDOW *window, int r, int f)
{
	std::vector<std::vector<tile_t>> b = board.getBoard();
	if (b[r][f].state & otherFlags::isInCheck)
	{
		wattron(window, COLOR_PAIR(5));
	}
	else if ((b[r][f].state & otherFlags::canEnPassant) || (b[r][f].state & otherFlags::isOccupied) && (!(!(b[r][f].state & pieceFlags::isWhitePiece)) == isWhiteTurn) && (b[r][f].state & otherFlags::isHighlighted))
	{
		wattron(window, COLOR_PAIR(4));
	}
	else if (b[r][f].state & otherFlags::isHighlighted)
	{
		wattron(window, COLOR_PAIR(3));
	}
	else if ((r + f) % 2)
		wattron(window, COLOR_PAIR(2));
	else
		wattron(window, COLOR_PAIR(1));
}

void Screen::wattrOff(WINDOW *window, int r, int f)
{
	std::vector<std::vector<tile_t>> b = board.getBoard();
	if (b[r][f].state & otherFlags::isInCheck)
	{
		wattroff(window, COLOR_PAIR(5));
	}
	else if ((b[r][f].state & otherFlags::canEnPassant) || (b[r][f].state & otherFlags::isOccupied) && (!((b[r][f].state ^ b[board.getRank()][board.getFile()].state) & pieceFlags::isWhitePiece)) && (b[r][f].state & otherFlags::isHighlighted))
	{
		wattroff(window, COLOR_PAIR(4));
	}
	else if (b[r][f].state & otherFlags::isHighlighted)
	{
		wattroff(window, COLOR_PAIR(3));
	}
	else if ((r + f) % 2)
		wattroff(window, COLOR_PAIR(2));
	else
		wattroff(window, COLOR_PAIR(1));
}