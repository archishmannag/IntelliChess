#ifndef BOARD_EVALUATOR_HPP
#define BOARD_EVALUATOR_HPP

class board;

class board_evaluator
{
public:
	virtual int evaluate(board *b, int d) = 0;
};

#endif