#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <memory>
#include <cstdint>

#include <engine/player/ai/MoveStrategy.hpp>
#include <engine/player/ai/BoardEvaluator.hpp>

class mini_max : public move_strategy
{
private:
	std::unique_ptr<board_evaluator> board_evaluator_;
	unsigned const search_depth_;

	int min(std::shared_ptr<board> b, unsigned int d);
	int max(std::shared_ptr<board> b, unsigned int d);

public:
	mini_max(unsigned int sd);
	std::shared_ptr<move> execute(std::shared_ptr<board> b) override;
};

#endif