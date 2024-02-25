#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <cstdlib>

#include "board.h"
#include "player.h"
#include "clock.h"
#include "mover.h"
#include "screen.h"

class Game
{
private:
	Board *board;
	Clock *clock;
	Player *whitePlayer, *blackPlayer;
	Mover *mover;
	Screen *screen;
	bool isWhiteTurn, isGameOver, undoMove;
	int scoreUpdateReturned;

public:
	Game();
	~Game();

	void initialize();

	void run();

	void input();

	void update();

	void end();
};

#endif