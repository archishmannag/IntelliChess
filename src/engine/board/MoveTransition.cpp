#include <engine/board/Board.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>

MoveTransition::MoveTransition(const Board *transitionBoard, const Move *move, const MoveStatus moveStatus) : transitionBoard(transitionBoard), move(move), moveStatus(moveStatus) {}

MoveStatus MoveTransition::getMoveStatus() const
{
	return this->moveStatus;
}

Board *MoveTransition::getTransitionBoard() const
{
	return const_cast<Board *>(this->transitionBoard);
}