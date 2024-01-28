#ifndef MOVEHIGHLIGHTER_H
#define MOVEHIGHLIGHTER_H

#include <vector>
#include <cstdint>

typedef enum
{
	pawn = 1,
	rook = 2,
	knight = 4,
	bishop = 8,
	queen = 16,
	king = 32
} piece;

typedef enum
{
	isWhitePiece = 64,
	isHighlighted = 128,
	enPassant = 256
} pieceFlags;

typedef struct
{
	uint16_t piece_color;
} square;

class MoveHighlighter
{
private:
	int f, r;
	std::vector<std::vector<square>> *board;

	void pawnMoves();
	void rookMoves();
	void knightMoves();
	void bishopMoves();
	void kingMoves();
	void noHighlight();

public:
	MoveHighlighter(std::vector<std::vector<square>> *b);
	~MoveHighlighter();
	void toggleHighlight(int f, int r);
	void getCurrentPosition(int &f, int &r);
};

#endif