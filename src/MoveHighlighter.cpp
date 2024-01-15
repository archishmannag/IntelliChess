#include "MoveHighlighter.h"

MoveHighlighter::MoveHighlighter(std::vector<std::vector<square>> *b)
{
	this->board = b;
}
MoveHighlighter::~MoveHighlighter()
{
	delete board;
}

void MoveHighlighter::getCurrentPosition(int &f, int &r)
{
	f = this->f;
	r = this->r;
}

/*
	This function toggles the highlighted cells based on the available moves. It takes the current cell as the input and computes the moves, then highlights them. If the cell is already highlighted, it removes the highlight.

	f = Current file
	r = Current rank
*/
void MoveHighlighter::toggleHighlight(int f, int r)
{
	/*
		How this works:
		*	We have the knowledge of the cell which was selected. We find out which piece was present there.
		*	Then we go on highlighting the cells which are possible moves until the edge of board or another piece is found.
	*/
	if (!(this->f == f && this->r == r))
		noHighlight();
	this->f = f, this->r = r;
	switch ((*board)[r][f].piece_color & 0b0111111)
	{
	case piece::pawn:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		pawnMoves();
		break;
	case piece::rook:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		rookMoves();
		break;
	case piece::knight:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		knightMoves();
		break;
	case piece::bishop:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		bishopMoves();
		break;
	case piece::queen:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		rookMoves();
		bishopMoves();
		break;
	case piece::king:
		(*board)[r][f].piece_color ^= pieceFlags::isHighlighted;
		kingMoves();
		break;
	}
}

void MoveHighlighter::pawnMoves()
{
	if ((*board)[r][f].piece_color & pieceFlags::isWhitePiece)
	{
		if (r == 6)
		{
			if (!((*board)[r - 1][f].piece_color & 0b111111))
			{
				(*board)[r - 1][f].piece_color ^= pieceFlags::isHighlighted;
				if (!((*board)[r - 2][f].piece_color & 0b111111))
					(*board)[r - 2][f].piece_color ^= pieceFlags::isHighlighted;
			}
		}
		else if (r == 3)
		{
			if (!((*board)[r - 1][f].piece_color & 0b111111))
				(*board)[r - 1][f].piece_color ^= pieceFlags::isHighlighted;
			if (f > 0 && (((*board)[r][f - 1].piece_color & pieceFlags::isWhitePiece) == 0) && ((*board)[r][f - 1].piece_color & piece::pawn))
				(*board)[r - 1][f - 1].piece_color ^= pieceFlags::enPassant | pieceFlags::isHighlighted;
			if (f < 7 && (((*board)[r][f + 1].piece_color & pieceFlags::isWhitePiece) == 0) && ((*board)[r][f + 1].piece_color & piece::pawn))
				(*board)[r - 1][f + 1].piece_color ^= pieceFlags::enPassant | pieceFlags::isHighlighted;
		}
		else
		{
			if (!((*board)[r - 1][f].piece_color & 0b111111))
				(*board)[r - 1][f].piece_color ^= pieceFlags::isHighlighted;
		}
		if (f > 0 && ((*board)[r - 1][f - 1].piece_color & pieceFlags::isWhitePiece == 0) && (*board)[r - 1][f - 1].piece_color & 0b111111)
			(*board)[r - 1][f - 1].piece_color ^= pieceFlags::isHighlighted;
		if (f < 7 && ((*board)[r - 1][f + 1].piece_color & pieceFlags::isWhitePiece == 0) && (*board)[r - 1][f + 1].piece_color & 0b111111)
			(*board)[r - 1][f + 1].piece_color ^= pieceFlags::isHighlighted;
	}
	else
	{
		if (r == 1)
		{
			if (!((*board)[r + 1][f].piece_color & 0b111111))
			{
				(*board)[r + 1][f].piece_color ^= pieceFlags::isHighlighted;
				if (!((*board)[r + 1][f].piece_color & 0b111111))
					(*board)[r + 2][f].piece_color ^= pieceFlags::isHighlighted;
			}
		}
		else if (r == 4)
		{
			if (!((*board)[r + 1][f].piece_color & 0b111111))
				(*board)[r + 1][f].piece_color ^= pieceFlags::isHighlighted;
			if (f > 0 && (((*board)[r][f - 1].piece_color & pieceFlags::isWhitePiece) != 0) && ((*board)[r][f - 1].piece_color & piece::pawn))
				(*board)[r + 1][f - 1].piece_color ^= pieceFlags::enPassant | pieceFlags::isHighlighted;
			if (f < 7 && (((*board)[r][f + 1].piece_color & pieceFlags::isWhitePiece) != 0) && ((*board)[r][f + 1].piece_color & piece::pawn))
				(*board)[r + 1][f + 1].piece_color ^= pieceFlags::enPassant | pieceFlags::isHighlighted;
		}
		else
		{
			if (!((*board)[r + 1][f].piece_color & 0b111111))
				(*board)[r + 1][f].piece_color ^= pieceFlags::isHighlighted;
		}
		if (f > 0 && ((*board)[r + 1][f - 1].piece_color & pieceFlags::isWhitePiece != 0) && (*board)[r + 1][f - 1].piece_color & 0b111111)
			(*board)[r + 1][f - 1].piece_color ^= pieceFlags::isHighlighted;
		if (f < 7 && ((*board)[r + 1][f + 1].piece_color & pieceFlags::isWhitePiece != 0) && (*board)[r + 1][f + 1].piece_color & 0b111111)
			(*board)[r + 1][f + 1].piece_color ^= pieceFlags::isHighlighted;
	}
}

void MoveHighlighter::rookMoves()
{
	for (int i = r + 1; i < 8; i++)
	{
		if (((*board)[i][f].piece_color & 0b0111111) == 0)
		{
			(*board)[i][f].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][f].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][f].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1; i >= 0; i--)
	{
		if (((*board)[i][f].piece_color & 0b0111111) == 0)
		{
			(*board)[i][f].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][f].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][f].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = f + 1; i < 8; i++)
	{
		if (((*board)[r][i].piece_color & 0b0111111) == 0)
		{
			(*board)[r][i].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[r][i].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[r][i].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = f - 1; i >= 0; i--)
	{
		if (((*board)[r][i].piece_color & 0b0111111) == 0)
		{
			(*board)[r][i].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[r][i].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[r][i].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
}

void MoveHighlighter::knightMoves()
{
	int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
	int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
	for (int k = 0; k < 8; k++)
	{
		int nx = r + dx[k];
		int ny = f + dy[k];
		if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			if (((*board)[nx][ny].piece_color & 0b0111111) == 0 ||
				(((*board)[nx][ny].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece)))
			{
				(*board)[nx][ny].piece_color ^= pieceFlags::isHighlighted;
			}
		}
	}
}

void MoveHighlighter::bishopMoves()
{
	for (int i = r + 1, j = f + 1; i < 8 && j < 8; i++, j++)
	{
		if (((*board)[i][j].piece_color & 0b0111111) == 0)
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][j].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1, j = f - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (((*board)[i][j].piece_color & 0b0111111) == 0)
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][j].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r + 1, j = f - 1; i < 8 && j >= 0; i++, j--)
	{
		if (((*board)[i][j].piece_color & 0b0111111) == 0)
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][j].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1, j = f + 1; i >= 0 && j < 8; i--, j++)
	{
		if (((*board)[i][j].piece_color & 0b0111111) == 0)
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			continue;
		}
		else if (((*board)[i][j].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece))
		{
			(*board)[i][j].piece_color ^= pieceFlags::isHighlighted;
			break;
		}
		else
			break;
	}
}

void MoveHighlighter::kingMoves()
{
	int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
	int dy[] = {1, 0, -1, 1, -1, 1, 0, -1};
	for (int k = 0; k < 8; k++)
	{
		int nx = r + dx[k];
		int ny = f + dy[k];
		if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			if (((*board)[nx][ny].piece_color & 0b0111111) == 0 ||
				(((*board)[nx][ny].piece_color & pieceFlags::isWhitePiece) != ((*board)[r][f].piece_color & pieceFlags::isWhitePiece)))
			{
				(*board)[nx][ny].piece_color ^= pieceFlags::isHighlighted;
			}
		}
	}
}

void MoveHighlighter::noHighlight()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			(*board)[i][j].piece_color &= ~pieceFlags::isHighlighted;
}
/*
	//TODO: Implement normal moves
	TODO: Implement capturing moves
	TODO: Implement check
	TODO: Implement checkmate
	TODO: Implement pawn promotion
	TODO: Implement castling
	//TODO: Implement en passant
	TODO: Implement stalemate
	TODO: Implement draw
	TODO: Implement threefold repetition
*/