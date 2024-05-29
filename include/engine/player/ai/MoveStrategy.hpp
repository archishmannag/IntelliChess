#ifndef MOVE_STRATEGY_HPP
#define MOVE_STRATEGY_HPP

class Move;
class Board;

class MoveStrategy
{
public:
	virtual Move *execute(Board *board) = 0;
};

#endif