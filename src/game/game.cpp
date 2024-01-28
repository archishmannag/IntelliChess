/*
	The main class for the game. This will consist of the board, pieces, players, clocks for the players and various function calls. The TUI will directly use this class' object to draw the board and pieces and to get input from the user.
*/

#include "../../include/game.h"

class Game
{
private:
	Board board;
	WhitePlayer whitePlayer;
	BlackPlayer blackPlayer;
	Clock whiteClock, blackClock;
	bool isWhiteTurn;
	bool isGameOver;
};