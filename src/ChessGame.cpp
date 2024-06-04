#include <iostream>

#include <gui/GameBoard.hpp>

int main(int argc, char *argv[])
{
	try
	{
		game_board gameBoard;
		while (gameBoard.is_running())
		{
			gameBoard.render();
			gameBoard.update();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}