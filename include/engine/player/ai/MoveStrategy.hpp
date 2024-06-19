#ifndef MOVE_STRATEGY_HPP
#define MOVE_STRATEGY_HPP

class move;
class board;

class move_strategy
{
public:
	virtual std::shared_ptr<move> execute(std::shared_ptr<board> b) = 0;
};

#endif // MOVE_STRATEGY_HPP