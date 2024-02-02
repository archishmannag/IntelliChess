#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>
#include <wchar.h>
#include <clocale>
#include <thread>
#include <chrono>
#include <vector>

#include "TerminalSizeWatcher.h"
#include "piece_tile.h"
#include "board.h"
#include "clock.h"

#define attrOn(r, f) wattrOn(stdscr, r, f)
#define attrOff(r, f) wattrOff(stdscr, r, f)

class Screen
{
private:
	int height, width, x, y;
	bool isRunning;
	WINDOW *movingWindow = NULL;
	TerminalSizeWatcher *watcher;
	std::thread screenThread;
	Board &board;
	Clock &clock;

	void initializeScreen();
	void displayScreen();
	void draw();
	void wattrOn(WINDOW *window, int r, int f);
	void wattrOff(WINDOW *window, int r, int f);

public:
	Screen(Board &board, Clock &clock);
	~Screen();
};

#endif