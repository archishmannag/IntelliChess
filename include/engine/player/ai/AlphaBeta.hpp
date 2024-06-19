#ifndef ALPHA_BETA_HPP
#define ALPHA_BETA_HPP

#include <PreCompiledHeaders.hpp>

#include "MoveStrategy.hpp"

class board;
class move;
class player;

class alpha_beta final : public move_strategy
{
public:
	alpha_beta(const unsigned sd);
	std::shared_ptr<move> execute(std::shared_ptr<board> b) override;

private:
	int max(std::shared_ptr<board> b, int depth, int alpha, int beta);
	int min(std::shared_ptr<board> b, int depth, int alpha, int beta);
	std::string score(std::shared_ptr<player> cp, int highest_seen_value, int lowest_seen_value);
	int quiescence(std::shared_ptr<board> b, int depth, int alpha, int beta);

private:
	int search_depth_, quiescence_count_ = 0, max_quiescence = 25000;
	long boards_evaluated_ = 0;
};

#endif // ALPHA_BETA_HPP