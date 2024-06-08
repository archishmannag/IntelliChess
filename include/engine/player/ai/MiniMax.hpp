#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <memory>
#include <cstdint>

#include <engine/player/ai/MoveStrategy.hpp>

class mini_max final : public move_strategy
{
private:
	unsigned const search_depth_;

	int min(std::shared_ptr<board> b, unsigned int d);
	int max(std::shared_ptr<board> b, unsigned int d);

public:
	mini_max(unsigned int sd);
	std::shared_ptr<move> execute(std::shared_ptr<board> b) override;
};

#endif