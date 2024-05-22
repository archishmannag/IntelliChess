#include <stdexcept>

#include <engine/pieces/Piece.hpp>

Piece::Piece(const int piecePosition, const Alliance pieceAlliance, const PieceType pieceType, bool isFirstMove) : piecePosition(piecePosition), pieceAlliance(pieceAlliance), isFirstMove(isFirstMove), pieceType(pieceType){};

bool Piece::operator==(const Piece &other)
{
	if (this == &other)
		return true;
	if (typeid(*this) != typeid(other))
		return false;
	return this->piecePosition == other.getPiecePosition() && this->pieceAlliance == other.getPieceAlliance() && this->pieceType == other.getPieceType() && this->isFirstMove == other.getIsFirstMove();
}

std::vector<Move *> Piece::calculateLegalMoves(Board &board)
{
	throw std::logic_error("This method must be overridden by a subclass.");
}

Piece *Piece::movePiece(const Move *move) const
{
	throw std::logic_error("This method must be overridden by a subclass.");
}

int Piece::getPiecePosition() const
{
	return this->piecePosition;
}

Alliance Piece::getPieceAlliance() const
{
	return this->pieceAlliance;
}

bool Piece::getIsFirstMove() const
{
	return this->isFirstMove;
}

PieceType Piece::getPieceType() const
{
	return this->pieceType;
}

int Piece::getPieceValue() const
{
	switch (this->pieceType)
	{
	case PieceType::PAWN:
		return 100;
	case PieceType::KNIGHT:
	case PieceType::BISHOP:
		return 300;
	case PieceType::ROOK:
		return 500;
	case PieceType::QUEEN:
		return 900;
	case PieceType::KING:
		return 10000;
	default:
		throw std::runtime_error("Invalid piece type");
	}
}

std::string Piece::stringify() const
{
	std::string typeString = "";
	switch (this->pieceType)
	{
	case PieceType::PAWN:
		typeString += "P";
		break;
	case PieceType::KNIGHT:
		typeString += "N";
		break;
	case PieceType::BISHOP:
		typeString += "B";
		break;
	case PieceType::ROOK:
		typeString += "R";
		break;
	case PieceType::QUEEN:
		typeString += "Q";
		break;
	case PieceType::KING:
		typeString += "K";
		break;
	}
	return typeString;
}