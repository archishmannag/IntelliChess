#include <stdexcept>

#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/player/Player.hpp>

/*Move*/

Move::Move(Board *board, int destinationCoordinate) : board(board), movedPiece(nullptr), destinationCoordinate(destinationCoordinate), isFirstMove(false){};

Move::Move(Board *board, Piece *movedPiece, int destinationCoordinate) : board(board), movedPiece(movedPiece), destinationCoordinate(destinationCoordinate), isFirstMove(movedPiece->getIsFirstMove()){};

bool Move::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (typeid(*this) != typeid(other))
		return false;
	return getCurrentCoordinate() == other.getCurrentCoordinate() && getDestinationCoordinate() == other.getDestinationCoordinate() && *getMovedPiece() == *other.getMovedPiece();
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

Board *Move::getBoard() const
{
	return const_cast<Board *>(this->board);
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
	builder.setTransitionMove(this);
	return builder.build();
}

std::string Move::stringify() const
{
	throw std::logic_error("Use subclass functions!");
}

/*MajorMove*/

MajorMove::MajorMove(Board *board, Piece *movedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

bool MajorMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const MajorMove *otherMajorMove = dynamic_cast<const MajorMove *>(&other))
		return Move::operator==(other);
	return false;
}

std::string MajorMove::stringify() const
{
	return movedPiece->stringify() + BoardUtils::getPositionAtCoordinate(this->destinationCoordinate);
}

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

/*PawnPromotion*/

PawnPromotion::PawnPromotion(Move *inputMove, Piece *promotedPiece) : Move(inputMove->getBoard(), inputMove->getMovedPiece(), inputMove->getDestinationCoordinate()), inputMove(inputMove), promotedPawn(dynamic_cast<Pawn *>(inputMove->getMovedPiece())), promotedPiece(promotedPiece) {}

bool PawnPromotion::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const PawnPromotion *otherPawnPromotion = dynamic_cast<const PawnPromotion *>(&other))
		return Move::operator==(other) && *getPromotedPiece() == *otherPawnPromotion->getPromotedPiece();
	return false;
}

Board *PawnPromotion::execute() const
{
	Board *pawnMovedBoard = this->inputMove->execute();
	BoardBuilder builder;
	for (const auto piece : pawnMovedBoard->getCurrentPlayer()->getActivePieces())
		if (!this->promotedPawn->operator==(*piece))
			builder.setPiece(piece);
	for (const auto piece : pawnMovedBoard->getCurrentPlayer()->getOpponent()->getActivePieces())
		builder.setPiece(piece);
	builder.setPiece(this->promotedPiece->movePiece(this));
	builder.setMoveMaker(pawnMovedBoard->getCurrentPlayer()->getPlayerAlliance());
	builder.setTransitionMove(this);
	return builder.build();
}

bool PawnPromotion::isAttack() const
{
	return this->inputMove->isAttack();
}

Piece *PawnPromotion::getAttackedPiece() const
{
	return this->inputMove->getAttackedPiece();
}

Piece *PawnPromotion::getPromotedPiece() const
{
	return this->promotedPiece;
}

std::string PawnPromotion::stringify() const
{
	return inputMove->stringify() + '=' + promotedPiece->stringify();
}

/*MajorAttackMove*/

MajorAttackMove::MajorAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : AttackMove(board, movedPiece, attackedPiece, destinationCoordinate){};

bool MajorAttackMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const MajorAttackMove *otherMajorAttackMove = dynamic_cast<const MajorAttackMove *>(&other))
		return AttackMove::operator==(other);
	return false;
}

std::string MajorAttackMove::stringify() const
{
	return movedPiece->stringify() + "x" + BoardUtils::getPositionAtCoordinate(this->destinationCoordinate);
}

/*PawnMove*/

PawnMove::PawnMove(Board *board, Piece *movedPiece, int destinationCoordinate) : Move(board, movedPiece, destinationCoordinate){};

bool PawnMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const PawnMove *otherPawnMove = dynamic_cast<const PawnMove *>(&other))
		return Move::operator==(other);
	return false;
}

std::string PawnMove::stringify() const
{
	return BoardUtils::getPositionAtCoordinate(this->destinationCoordinate);
}

/*PawnAttackMove*/

PawnAttackMove::PawnAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : AttackMove(board, movedPiece, attackedPiece, destinationCoordinate){};

bool PawnAttackMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const PawnAttackMove *otherPawnAttackMove = dynamic_cast<const PawnAttackMove *>(&other))
		return AttackMove::operator==(other);
	return false;
}

std::string PawnAttackMove::stringify() const
{
	return BoardUtils::getPositionAtCoordinate(this->movedPiece->getPiecePosition()).substr(0, 1) + "x" +
		   BoardUtils::getPositionAtCoordinate(this->destinationCoordinate);
}

/*PawnEnPassantAttackMove*/

PawnEnPassantAttackMove::PawnEnPassantAttackMove(Board *board, Piece *movedPiece, Piece *attackedPiece, int destinationCoordinate) : PawnAttackMove(board, movedPiece, attackedPiece, destinationCoordinate){};

Board *PawnEnPassantAttackMove::execute() const
{
	BoardBuilder builder;
	for (const auto piece : this->board->getCurrentPlayer()->getActivePieces())
		if (!(piece == this->getMovedPiece()))
			builder.setPiece(piece);
	for (const auto piece : this->board->getCurrentPlayer()->getOpponent()->getActivePieces())
		if (!(piece == this->getAttackedPiece()))
			builder.setPiece(piece);
	builder.setPiece(this->movedPiece->movePiece(this));
	builder.setMoveMaker(this->board->getCurrentPlayer()->getOpponent()->getPlayerAlliance());
	builder.setTransitionMove(this);
	return builder.build();
}

bool PawnEnPassantAttackMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const PawnEnPassantAttackMove *otherPawnEnPassantAttackMove = dynamic_cast<const PawnEnPassantAttackMove *>(&other))
		return PawnAttackMove::operator==(other);
	return false;
}

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
	builder.setTransitionMove(this);
	return builder.build();
}

std::string PawnJump::stringify() const
{
	return BoardUtils::getPositionAtCoordinate(this->destinationCoordinate);
}

/*CastleMove*/

CastleMove::CastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : Move(board, movedPiece, destinationCoordinate), castleRook(castleRook), castleRookStart(castleRookStart), castleRookDestination(castleRookDestination){};

bool CastleMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const CastleMove *otherCastleMove = dynamic_cast<const CastleMove *>(&other))
		return Move::operator==(other) && *getCastleRook() == *otherCastleMove->getCastleRook();
	return false;
}

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
	builder.setPiece(new Rook(this->castleRookDestination, this->castleRook->getPieceAlliance(), false));
	builder.setMoveMaker(this->board->getCurrentPlayer()->getOpponent()->getPlayerAlliance());
	builder.setTransitionMove(this);
	return builder.build();
}

/*KingSideCastleMove*/

KingSideCastleMove::KingSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : CastleMove(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination){};

bool KingSideCastleMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const KingSideCastleMove *otherKingSideCastleMove = dynamic_cast<const KingSideCastleMove *>(&other))
		return CastleMove::operator==(other);
	return false;
}

std::string KingSideCastleMove::stringify() const
{
	return std::string("O-O");
}

/*QueenSideCastleMove*/

QueenSideCastleMove::QueenSideCastleMove(Board *board, Piece *movedPiece, int destinationCoordinate, Rook *castleRook, int castleRookStart, int castleRookDestination) : CastleMove(board, movedPiece, destinationCoordinate, castleRook, castleRookStart, castleRookDestination){};

bool QueenSideCastleMove::operator==(const Move &other) const
{
	if (this == &other)
		return true;
	if (const QueenSideCastleMove *otherQueenSideCastleMove = dynamic_cast<const QueenSideCastleMove *>(&other))
		return CastleMove::operator==(other);
	return false;
}

std::string QueenSideCastleMove::stringify() const
{
	return std::string("O-O-O");
}

/*NullMove*/

NullMove::NullMove() : Move(nullptr, -1){};

Board *NullMove::execute() const
{
	throw std::logic_error("Cannot execute the null move!");
}

std::string NullMove::stringify() const
{
	return std::string("Null Move");
}

/*Namespace MoveFactory*/

Move *MoveFactory::createMove(Board *board, int currentCoordinate, int destinationCoordinate)
{
	Move *selectedMove = nullptr;
	for (const auto move : board->getAllLegalMoves())
		if (move->getCurrentCoordinate() == currentCoordinate && move->getDestinationCoordinate() == destinationCoordinate)
		{
			selectedMove = move;
			break;
		}
	return selectedMove;
}

Move *MoveFactory::createMove(Board *board, int currentCoordinate, int destinationCoordinate, PieceType promotedPieceType)
{
	Move *selectedMove = nullptr;
	for (const auto move : board->getAllLegalMoves())
		if (move->getCurrentCoordinate() == currentCoordinate &&
			move->getDestinationCoordinate() == destinationCoordinate &&
			typeid(*move) == typeid(PawnPromotion) &&
			dynamic_cast<PawnPromotion *>(move)->getPromotedPiece()->getPieceType() == promotedPieceType)
		{
			selectedMove = move;
			break;
		}
	return selectedMove;
}