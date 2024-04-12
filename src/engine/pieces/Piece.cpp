#include "../../../include/engine/pieces/Piece.hpp"

Piece::Piece(const int piecePosition, const Alliance pieceAlliance) : piecePosition(piecePosition), pieceAlliance(pieceAlliance), isFirstMove(false){};

Alliance Piece::getPieceAlliance() const
{
	return this->pieceAlliance;
}

bool Piece::getIsFirstMove() const
{
	return this->isFirstMove;
}