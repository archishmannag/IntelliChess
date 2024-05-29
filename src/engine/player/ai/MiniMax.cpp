#include <chrono>
#include <iostream>

#include <engine/player/ai/MiniMax.hpp>
#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/board/Board.hpp>
#include <engine/player/Player.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>

MiniMax::MiniMax(unsigned int searchDepth) : searchDepth(searchDepth)
{
	boardEvaluator = std::make_unique<StandardBoardEvaluator>();
}

Move *MiniMax::execute(Board *board)
{
	const auto startTime = std::chrono::high_resolution_clock::now();
	Move *bestMove = nullptr;
	int highestSeenValue = INT32_MIN,
		lowestSeenValue = INT32_MAX,
		currentValue;

	std::cout << board->getCurrentPlayer()->stringify() << " THINKING with depth = " << searchDepth << std::endl;
	std::vector<Move *> moves = board->getCurrentPlayer()->getLegalMoves();
	int numMoves = moves.size();
	for (const auto move : moves)
	{
		MoveTransition transition = board->getCurrentPlayer()->makeMove(move);
		if (transition.getMoveStatus() == MoveStatus::DONE)
		{
			currentValue = board->getCurrentPlayer()->getPlayerAlliance() == Alliance::WHITE
							   ? min(transition.getTransitionBoard(), searchDepth - 1)
							   : max(transition.getTransitionBoard(), searchDepth - 1);

			if (board->getCurrentPlayer()->getPlayerAlliance() == Alliance::WHITE && highestSeenValue <= currentValue)
			{
				highestSeenValue = currentValue;
				bestMove = move;
			}
			else if (board->getCurrentPlayer()->getPlayerAlliance() == Alliance::BLACK && currentValue <= lowestSeenValue)
			{
				lowestSeenValue = currentValue;
				bestMove = move;
			}
		}
	}

	const auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime);

	return bestMove;
}

int MiniMax::min(Board *board, unsigned int depth)
{
	if (depth == 0)
		return boardEvaluator->evaluate(board, depth);

	int lowestSeenValue = INT32_MAX;
	for (const auto move : board->getCurrentPlayer()->getLegalMoves())
	{
		MoveTransition transition = board->getCurrentPlayer()->makeMove(move);
		if (transition.getMoveStatus() == MoveStatus::DONE)
		{
			int currentValue = max(transition.getTransitionBoard(), depth - 1);
			if (currentValue <= lowestSeenValue)
				lowestSeenValue = currentValue;
		}
	}
	return lowestSeenValue;
}

int MiniMax::max(Board *board, unsigned int depth)
{
	if (depth == 0)
		return boardEvaluator->evaluate(board, depth);

	int highestSeenValue = INT32_MIN;
	for (const auto move : board->getCurrentPlayer()->getLegalMoves())
	{
		MoveTransition transition = board->getCurrentPlayer()->makeMove(move);
		if (transition.getMoveStatus() == MoveStatus::DONE)
		{
			int currentValue = min(transition.getTransitionBoard(), depth - 1);
			if (highestSeenValue <= currentValue)
				highestSeenValue = currentValue;
		}
	}
	return highestSeenValue;
}