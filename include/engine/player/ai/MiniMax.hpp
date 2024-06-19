#ifndef MINI_MAX_HPP
#define MINI_MAX_HPP

#include <PreCompiledHeaders.hpp>

#include <engine/player/ai/MoveStrategy.hpp>

class mini_max final : public move_strategy
{
public:
	mini_max(unsigned int sd);
	std::shared_ptr<move> execute(std::shared_ptr<board> b) override;

private:
	int min(std::shared_ptr<board> b, unsigned int d);
	int max(std::shared_ptr<board> b, unsigned int d);

private:
	unsigned const search_depth_;
};

#endif // MINI_MAX_HPP