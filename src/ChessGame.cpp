#include <iostream>

#include "../include/engine/board/Board.hpp"
#include "../include/gui/GameBoard.hpp"

int main(int argc, char *argv[])
{
	GameBoard gameBoard;
	while (gameBoard.isRunning())
	{
		gameBoard.render();
		gameBoard.update();
	}
	return 0;
}