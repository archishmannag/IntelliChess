#include <iostream>

#include "../../include/engine/board/Board.hpp"

int main(int argc, char *argv[])
{
	Board *board = Board::createStandardBoard();
	std::cout << board->stringify() << std::endl;
	return 0;
}