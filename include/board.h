#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdint>

#ifndef PIECE_ENUM
#define PIECE_ENUM

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
	canPromote = 512,
	canEnPassant = 1024,
	canCastle = 2048,
	hasMoved = 4096,
	isInCheck = 8192,
	isInCheckmate = 16384,
	isInStalemate = 32768
} otherFlags;

#endif

typedef struct
{
	uint16_t state;
} tile_t;

class Board
{
private:
	int file = 5, rank = 5;
	std::vector<std::vector<tile_t>> board;

public:
	Board();
	~Board();
	void initialize();
	std::vector<std::vector<tile_t>> &getBoard();
	int getRank();
	int getFile();
	void setRank(int rank);
	void setFile(int file);
};

#endif