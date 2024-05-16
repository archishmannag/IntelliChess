#ifndef MOVETRANSITION_HPP
#define MOVETRANSITION_HPP

#include "Move.hpp"

class MoveTransition
{
private:
	const Board *transitionBoard;
	const Move *move;
	const MoveStatus moveStatus;

public:
	MoveTransition(const Board *transitionBoard, const Move *move, const MoveStatus moveStatus);
	MoveStatus getMoveStatus() const;
	Board *getTransitionBoard() const;
};
#endif