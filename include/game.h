#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <cstdlib>

#include "board.h"
#include "player.h"
#include "clock.h"
// #include "move.h"

class Game
{
private:
	Board *board;
	Clock *clock;
	Player *whitePlayer, *blackPlayer;
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