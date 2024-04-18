#include <stdexcept>
#include "../../../include/engine/board/Move.hpp"

Move::Move(const Board board, const Piece movedPiece, const int destinationCoordinate) : board(board), movedPiece(movedPiece), destinationCoordinate(destinationCoordinate){};

int Move::getDestinationCoordinate() const
{
	return this->destinationCoordinate;
}

Board *Move::execute() const
{
	throw std::logic_error("Use derived class methods.");
}

MajorMove::MajorMove(const Board board, const Piece movedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

AttackMove::AttackMove(const Board board, const Piece movedPiece, const Piece attackedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate), attackedPiece(attackedPiece){};