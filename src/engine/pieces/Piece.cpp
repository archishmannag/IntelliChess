#include <stdexcept>

#include "../../../include/engine/pieces/Piece.hpp"

Piece::Piece(const int piecePosition, const Alliance pieceAlliance) : piecePosition(piecePosition), pieceAlliance(pieceAlliance), isFirstMove(false){};

std::vector<Move *> Piece::calculateLegalMoves(Board &board)
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