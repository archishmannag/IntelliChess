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
	switch (this->pieceType)
	{
	case PieceType::PAWN:
		return "P";
		break;
	case PieceType::KNIGHT:
		return "N";
		break;
	case PieceType::BISHOP:
		return "B";
		break;
	case PieceType::ROOK:
		return "R";
		break;
	case PieceType::QUEEN:
		return "Q";
		break;
	case PieceType::KING:
		return "K";
		break;
	}
}