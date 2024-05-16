#include "../../../include/engine/board/MoveTransition.hpp"

MoveTransition::MoveTransition(const Board *transitionBoard, const Move *move, const MoveStatus moveStatus) : transitionBoard(transitionBoard), move(move), moveStatus(moveStatus) {}

MoveStatus MoveTransition::getMoveStatus() const
{
	return this->moveStatus;
}