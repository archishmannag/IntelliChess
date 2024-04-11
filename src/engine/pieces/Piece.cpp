#include "../../../include/engine/pieces/Piece.hpp"

Piece::Piece(const int piecePosition, const Alliance pieceAlliance) : piecePosition(piecePosition), pieceAlliance(pieceAlliance){};

Alliance Piece::getPieceAlliance()
{
	return this->pieceAlliance;
}