#ifndef BOARD_EVALUATOR_HPP
#define BOARD_EVALUATOR_HPP

class Board;

class BoardEvaluator
{
public:
	virtual int evaluate(Board *board, int depth) = 0;
};

#endif