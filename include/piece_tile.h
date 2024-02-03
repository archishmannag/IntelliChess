#ifndef PIECE_E_TILE_S
#define PIECE_E_TILE_S

typedef enum
{
	pawn = 1,
	rook = 2,
	knight = 4,
	bishop = 8,
	queen = 16,
	king = 32,
	isWhitePiece = 64
} pieceFlags;

typedef enum
{
	isHighlighted = 128,
	isOccupied = 256,
	canCapture = 512,
	canPromote = 1024,
	canEnPassant = 2048,
	canCastle = 4096,
	hasMoved = 8192,
	isInCheck = 16384,
} otherFlags;

typedef struct
{
	int rank, file;
	uint16_t state;
} tile_t;

#endif