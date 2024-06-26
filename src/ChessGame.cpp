/**
 * @file ChessGame.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief The main file for the chess game
 * @version 1.0.0
 *
 */

#include "PreCompiledHeaders.hpp"

#include "gui/GameBoard.hpp"

int main(int argc, char *argv[])
{
    game_board gameBoard;
    while (gameBoard.is_running())
    {
        gameBoard.render();
        gameBoard.update();
    }

    return 0;
}