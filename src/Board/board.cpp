#include "../../include/board.h"

Board::Board()
{
	// Initialize the board
	board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		board[i].resize(8);
	}

	// Initialize the tiles
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			board[i][j].state = 0;
			board[i][j].rank = i;
			board[i][j].file = j;
		}
}

Board::~Board()
{
	// Delete the board
	board.clear();
}

void Board::initialize()
{
	// Initialise board array
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == 1 || i == 6)
				board[i][j].state |= pieceFlags::pawn;
			if (i == 0 || i == 7)
			{
				if (j == 0 || j == 7)
					board[i][j].state |= pieceFlags::rook | otherFlags::canCastle;
				if (j == 1 || j == 6)
					board[i][j].state |= pieceFlags::knight;
				if (j == 2 || j == 5)
					board[i][j].state |= pieceFlags::bishop;
				if (j == 3)
					board[i][j].state |= pieceFlags::queen;
				if (j == 4)
					board[i][j].state |= pieceFlags::king | otherFlags::canCastle;
			}
			if (i == 6 || i == 7)
				board[i][j].state |= pieceFlags::isWhitePiece;
		}
}

std::vector<std::vector<tile_t>> Board::getBoard()
{
	return board;
}

std::vector<std::vector<tile_t>> &Board::getBoardReference()
{
	return board;
}

int Board::getRank()
{
	return rank;
}

int Board::getFile()
{
	return file;
}

void Board::setRank(int rank)
{
	this->rank = rank;
}

void Board::setFile(int file)
{
	this->file = file;
}