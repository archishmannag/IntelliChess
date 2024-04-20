#include <stdexcept>

#include "../../../include/engine/board/Board.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/pieces/Piece.hpp"
#include "../../../include/engine/pieces/Pawn.hpp"
#include "../../../include/engine/pieces/Rook.hpp"
#include "../../../include/engine/player/Player.hpp"

/*Move*/

Move::Move(Board *board, Piece *movedPiece, int destinationCoordinate) : board(board), movedPiece(movedPiece), destinationCoordinate(destinationCoordinate){};

const Move *Move::NULL_MOVE = new NullMove();

bool Move::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (typeid(*this) != typeid(other))
		return false;
	return getDestinationCoordinate() == other.getDestinationCoordinate() && *getMovedPiece() == *other.getMovedPiece();
}

int Move::getDestinationCoordinate() const
{
	return this->destinationCoordinate;
}

int Move::getCurrentCoordinate() const
{
	return this->movedPiece->getPiecePosition();
}

Piece *Move::getMovedPiece() const
{
	return const_cast<Piece *>(this->movedPiece);
}

bool Move::isAttack() const
{
	return false;
}

bool Move::isCastlingMove() const
{
	return false;
}

Piece *Move::getAttackedPiece() const
{
	return nullptr;
}

Board *Move::execute() const
{
	BoardBuilder builder;
	// Add all the pieces of same alliance to the new board except the moved piece
	for (const auto piece : this->board->getCurrentPlayer()->getActivePieces())
		if (!(*getMovedPiece() == *piece))
			builder.setPiece(piece);
	// Add all the pieces of opponent alliance to the new board
	for (const auto piece : this->board->getCurrentPlayer()->getOpponent()->getActivePieces())
		builder.setPiece(piece);
	// Move the moved piece to the destination coordinate
	builder.setPiece(this->movedPiece->movePiece(this));
	builder.setMoveMaker(this->board->getCurrentPlayer()->getOpponent()->getPlayerAlliance());
	return builder.build();
}

std::string Move::stringify() const
{
	throw std::logic_error("Use subclass functions!");
}

/*MajorMove*/

MajorMove::MajorMove(Board *board, Piece *movedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

/*AttackMove*/

AttackMove::AttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate), attackedPiece(attackedPiece){};

bool AttackMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const AttackMove *otherAttackMove = dynamic_cast<const AttackMove *>(&other))
		return Move::operator==(other) && *getAttackedPiece() == *otherAttackMove->getAttackedPiece();
	return false;
}

bool AttackMove::isAttack() const
{
	return true;
}

Piece *AttackMove::getAttackedPiece() const
{
	return const_cast<Piece *>(this->attackedPiece);
}

/*PawnMove*/

PawnMove::PawnMove(Board *board, Piece *movedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

/*PawnAttackMove*/

PawnAttackMove::PawnAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : AttackMove(board, movedPiece, attackedPiece, destinationCoordinate){};

/*PawnEnPassantAttackMove*/

PawnEnPassantAttackMove::PawnEnPassantAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : PawnAttackMove(board, movedPiece, attackedPiece, destinationCoordinate){};

/*PawnJump*/

PawnJump::PawnJump(Board *board, Piece *movedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

Board *PawnJump::execute() const
{
	BoardBuilder builder;
	// Add all the pieces of same alliance to the new board except the moved piece
	for (const auto piece : this->board->getCurrentPlayer()->getActivePieces())
		if (!(*getMovedPiece() == *piece))
			builder.setPiece(piece);
	// Add all the pieces of opponent alliance to the new board
	for (const auto piece : this->board->getCurrentPlayer()->getOpponent()->getActivePieces())
		builder.setPiece(piece);
	// Move the moved piece to the destination coordinate
	Pawn *movedPawn = dynamic_cast<Pawn *>(this->getMovedPiece()->movePiece(this));
	builder.setPiece(movedPawn);
	builder.setEnPassantPawn(movedPawn);
	builder.setMoveMaker(this->board->getCurrentPlayer()->getOpponent()->getPlayerAlliance());
	return builder.build();
}

/*CastleMove*/

CastleMove::CastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : Move(board, movedPiece, destinationCoordinate), castleRook(castleRook), castleRookStart(castleRookStart), castleRookDestination(castleRookDestination){};

Rook *CastleMove::getCastleRook() const
{
	return const_cast<Rook *>(this->castleRook);
}

bool CastleMove::isCastlingMove() const
{
	return true;
}

Board *CastleMove::execute() const
{
	BoardBuilder builder;
	// Add all the pieces of same alliance to the new board except the moved piece and the castle rook
	for (const auto piece : this->board->getCurrentPlayer()->getActivePieces())
		if (!(*getMovedPiece() == *piece) && !(*getCastleRook() == *piece))
			builder.setPiece(piece);
	// Add all the pieces of opponent alliance to the new board
	for (const auto piece : this->board->getCurrentPlayer()->getOpponent()->getActivePieces())
		builder.setPiece(piece);
	// Move the moved piece (King) to the destination coordinate
	builder.setPiece(this->movedPiece->movePiece(this));
	// Move the castle rook to the destination coordinate
	builder.setPiece(new Rook(this->castleRook->getPiecePosition(), this->castleRook->getPieceAlliance()));
	builder.setMoveMaker(this->board->getCurrentPlayer()->getOpponent()->getPlayerAlliance());
	return builder.build();
}

/*KingSideCastleMove*/

KingSideCastleMove::KingSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : CastleMove(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination){};

std::string KingSideCastleMove::stringify() const
{
	return std::string("O-O");
}

/*QueenSideCastleMove*/

QueenSideCastleMove::QueenSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : CastleMove(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination){};

std::string QueenSideCastleMove::stringify() const
{
	return std::string("O-O-O");
}

/*NullMove*/

NullMove::NullMove() : Move(nullptr, nullptr, -1){};

Board *NullMove::execute() const
{
	throw std::invalid_argument("Cannot execute the null move!");
}

/*Namespace MoveFactory*/

Move *MoveFactory::createMove(Board *board, int currectCoordinate, int destinationCoordinate)
{
	Move *selectedMove = nullptr;
	for (const auto move : board->getAllLegalMoves())
		if (move->getCurrentCoordinate() == currectCoordinate && move->getDestinationCoordinate() == destinationCoordinate)
		{
			selectedMove = move;
			break;
		}
	return selectedMove;
}