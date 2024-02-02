#include "../../include/MoveHighlighter.h"

MoveHighlighter::MoveHighlighter(Board &board) : board(board), boardReference(board.getBoardReference()) {}
MoveHighlighter::~MoveHighlighter() {}

void MoveHighlighter::highlight(int r, int f)
{
	noHighlight();
	noEnPassant();

	switch (boardReference[r][f].state & 0b0000000000111111)
	{
	case pieceFlags::pawn:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		pawnMoves(r, f);
		break;
	case pieceFlags::rook:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		rookMoves(r, f);
		break;
	case pieceFlags::knight:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		knightMoves(r, f);
		break;
	case pieceFlags::bishop:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		bishopMoves(r, f);
		break;
	case pieceFlags::queen:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		rookMoves(r, f);
		bishopMoves(r, f);
		break;
	case pieceFlags::king:
		boardReference[r][f].state ^= otherFlags::isHighlighted;
		kingMoves(r, f);
		break;
	}
}

void MoveHighlighter::noHighlight()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardReference[i][j].state &= ~otherFlags::isHighlighted;
}

void MoveHighlighter::noEnPassant()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardReference[i][j].state &= ~otherFlags::canEnPassant;
}

void MoveHighlighter::pawnMoves(int r, int f)
{
	if (boardReference[r][f].state & pieceFlags::isWhitePiece)
	{
		if (boardReference[r][f].state & otherFlags::hasMoved)
		{
			if (r - 1 >= 0 && (boardReference[r - 1][f].state & 0b0111111) == 0)
				boardReference[r - 1][f].state ^= otherFlags::isHighlighted;
			if (r - 1 >= 0 && f + 1 < 8 && (boardReference[r - 1][f + 1].state & 0b0111111) != 0 && (boardReference[r - 1][f + 1].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
				boardReference[r - 1][f + 1].state ^= otherFlags::isHighlighted;
			if (r - 1 >= 0 && f - 1 >= 0 && (boardReference[r - 1][f - 1].state & 0b0111111) != 0 && (boardReference[r - 1][f - 1].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
				boardReference[r - 1][f - 1].state ^= otherFlags::isHighlighted;
		}
		else
		{
			if (r - 1 >= 0 && (boardReference[r - 1][f].state & 0b0111111) == 0)
			{
				boardReference[r - 1][f].state ^= otherFlags::isHighlighted;
				if (r - 2 >= 0 && (boardReference[r - 2][f].state & 0b0111111) == 0)
					boardReference[r - 2][f].state ^= otherFlags::isHighlighted;
			}
			if (r - 1 >= 0 && f + 1 < 8 && (boardReference[r - 1][f + 1].state & 0b0111111) != 0 && (boardReference[r - 1][f + 1].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
				boardReference[r - 1][f + 1].state ^= otherFlags::isHighlighted;
			if (r - 1 >= 0 && f - 1 >= 0 && (boardReference[r - 1][f - 1].state & 0b0111111) != 0 && (boardReference[r - 1][f - 1].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
				boardReference[r - 1][f - 1].state ^= otherFlags::isHighlighted;
		}
	}
}

void MoveHighlighter::rookMoves(int r, int f)
{
	for (int i = r + 1; i < 8; i++)
	{
		if ((boardReference[i][f].state & 0b0111111) == 0)
		{
			boardReference[i][f].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][f].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][f].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1; i >= 0; i--)
	{
		if ((boardReference[i][f].state & 0b0111111) == 0)
		{
			boardReference[i][f].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][f].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][f].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = f + 1; i < 8; i++)
	{
		if ((boardReference[r][i].state & 0b0111111) == 0)
		{
			boardReference[r][i].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[r][i].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[r][i].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = f - 1; i >= 0; i--)
	{
		if ((boardReference[r][i].state & 0b0111111) == 0)
		{
			boardReference[r][i].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[r][i].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[r][i].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
}

void MoveHighlighter::knightMoves(int r, int f)
{
	int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
	int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
	for (int k = 0; k < 8; k++)
	{
		int nx = r + dx[k];
		int ny = f + dy[k];
		if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			if ((boardReference[nx][ny].state & 0b0111111) == 0 ||
				((boardReference[nx][ny].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece)))
			{
				boardReference[nx][ny].state ^= otherFlags::isHighlighted;
			}
		}
	}
}

void MoveHighlighter::bishopMoves(int r, int f)
{
	for (int i = r + 1, j = f + 1; i < 8 && j < 8; i++, j++)
	{
		if ((boardReference[i][j].state & 0b0111111) == 0)
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][j].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1, j = f - 1; i >= 0 && j >= 0; i--, j--)
	{
		if ((boardReference[i][j].state & 0b0111111) == 0)
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][j].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r + 1, j = f - 1; i < 8 && j >= 0; i++, j--)
	{
		if ((boardReference[i][j].state & 0b0111111) == 0)
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][j].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
	for (int i = r - 1, j = f + 1; i >= 0 && j < 8; i--, j++)
	{
		if ((boardReference[i][j].state & 0b0111111) == 0)
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			continue;
		}
		else if ((boardReference[i][j].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece))
		{
			boardReference[i][j].state ^= otherFlags::isHighlighted;
			break;
		}
		else
			break;
	}
}

void MoveHighlighter::kingMoves(int r, int f)
{
	int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
	int dy[] = {1, 0, -1, 1, -1, 1, 0, -1};
	for (int k = 0; k < 8; k++)
	{
		int nx = r + dx[k];
		int ny = f + dy[k];
		if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			if ((boardReference[nx][ny].state & 0b0111111) == 0 ||
				((boardReference[nx][ny].state & pieceFlags::isWhitePiece) != (boardReference[r][f].state & pieceFlags::isWhitePiece)))
			{
				boardReference[nx][ny].state ^= otherFlags::isHighlighted;
			}
		}
	}
	// Castling
	if (boardReference[0][4].state & otherFlags::canCastle && boardReference[0][7].state & otherFlags::canCastle)
	{
		if (boardReference[0][5].state & 0b111111 == 0 && boardReference[0][6].state & 0b111111 == 0)
		{
			boardReference[0][6].state ^= otherFlags::isHighlighted;
		}
	}
	if (boardReference[0][4].state & otherFlags::canCastle && boardReference[0][0].state & otherFlags::canCastle)
	{
		if (boardReference[0][1].state & 0b111111 == 0 && boardReference[0][2].state & 0b111111 == 0 && boardReference[0][3].state & 0b111111 == 0)
		{
			boardReference[0][2].state ^= otherFlags::isHighlighted;
		}
	}
	if (boardReference[7][4].state & otherFlags::canCastle && boardReference[7][7].state & otherFlags::canCastle)
	{
		if (boardReference[7][5].state & 0b111111 == 0 && boardReference[7][6].state & 0b111111 == 0)
		{
			boardReference[7][6].state ^= otherFlags::isHighlighted;
		}
	}
	if (boardReference[7][4].state & otherFlags::canCastle && boardReference[7][0].state & otherFlags::canCastle)
	{
		if (boardReference[7][1].state & 0b111111 == 0 && boardReference[7][2].state & 0b111111 == 0 && boardReference[7][3].state & 0b111111 == 0)
		{
			boardReference[7][2].state ^= otherFlags::isHighlighted;
		}
	}
}