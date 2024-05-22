#ifndef MOVETRANSITION_HPP
#define MOVETRANSITION_HPP

class Move;
class Board;
enum class MoveStatus;

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