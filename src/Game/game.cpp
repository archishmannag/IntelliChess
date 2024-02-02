#include "../../include/game.h"

Game::Game()
{
	board = new Board();
	clock = new Clock(10, 0, isWhiteTurn);
	whitePlayer = new Player(true);
	blackPlayer = new Player(false);
	mover = new Mover((*board), isWhiteTurn);
	screen = new Screen((*board), (*clock));
	isWhiteTurn = true;
	isGameOver = undoMove = false;

	whitePlayer->setOpponent(blackPlayer);
	blackPlayer->setOpponent(whitePlayer);

	initialize();

	run();
}

Game::~Game()
{
	delete board;
	delete clock;
	delete whitePlayer;
	delete blackPlayer;
}

void Game::initialize()
{
	board->initialize();
}

void Game::run()
{
	clock->startClock();
	while (!isGameOver)
	{
		input();
		update();
	}
	end();
}

void Game::input()
{
	int ch;
	ch = getch();
	if (ch == 'q')
	{
		this->~Game();
		exit(0);
	}
	else if (ch == KEY_UP)
	{
		if (board->getRank() > 0)
			board->setRank(board->getRank() - 1);
	}
	else if (ch == KEY_DOWN)
	{
		if (board->getRank() < 7)
			board->setRank(board->getRank() + 1);
	}
	else if (ch == KEY_LEFT)
	{
		if (board->getFile() > 0)
			board->setFile(board->getFile() - 1);
	}
	else if (ch == KEY_RIGHT)
	{
		if (board->getFile() < 7)
			board->setFile(board->getFile() + 1);
	}
	else if (ch == ' ')
	{
		scoreUpdateReturned = mover->move(board->getRank(), board->getFile());
	}
	else if (ch == 'u')
	{
		scoreUpdateReturned = mover->undo();
	}
}

void Game::update()
{
	// Based upon the move, update the score of the player.
	if (!isWhiteTurn)
		whitePlayer->setScore(whitePlayer->getScore() + scoreUpdateReturned);
	else
		blackPlayer->setScore(blackPlayer->getScore() + scoreUpdateReturned);
	scoreUpdateReturned = 0;
}

void Game::end()
{
}