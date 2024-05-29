#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <memory>
#include <cstdint>

#include <engine/player/ai/MoveStrategy.hpp>
#include <engine/player/ai/BoardEvaluator.hpp>

class MiniMax : public MoveStrategy
{
private:
	std::unique_ptr<BoardEvaluator> boardEvaluator;
	unsigned const searchDepth;

	int min(Board *board, unsigned int depth);
	int max(Board *board, unsigned int depth);

public:
	MiniMax(unsigned int searchDepth);
	Move *execute(Board *board) override;
};

#endif