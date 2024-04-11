#include "../../../include/engine/board/Move.hpp"

Move::Move(const Board board, const Piece movedPiece, const int destinationCoordinate) : board(board), movedPiece(movedPiece), destinationCoordinate(destinationCoordinate){};

MajorMove::MajorMove(const Board board, const Piece movedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

AttackMove::AttackMove(const Board board, const Piece movedPiece, const Piece attackedPiece, const int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate), attackedPiece(attackedPiece){};