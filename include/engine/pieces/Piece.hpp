#ifndef PIIECE_H
#define PIECE_H

#include <list>

#include "../alliance.hpp"

class Piece
{
protected:
	const int piecePosition;
	const Alliance pieceAlliance;

public:
	Piece(const int piecePosition, const Alliance pieceAlliance) : piecePosition(piecePosition), pieceAlliance(pieceAlliance){};
};

#endif