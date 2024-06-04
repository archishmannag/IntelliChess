#ifndef STANDARD_BOARD_EVALUATOR_HPP
#define STANDARD_BOARD_EVALUATOR_HPP

#include <engine/player/ai/BoardEvaluator.hpp>

class board;
class player;

class standard_board_evaluator final : public board_evaluator
{
private:
	int player_score(const player *p, int d);
	static int piece_value(const player *p);
	static int mobility_value(const player *p);
	static int check_value(const player *p);
	static int checkmate_value(const player *p, int d);
	static int has_castled(const player *p);
	static int depth_bonus(int d);

public:
	int evaluate(board *b, int d) override;
};

#endif