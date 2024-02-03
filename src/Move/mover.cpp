#include "../../include/mover.h"

Mover::Mover(Board &board, bool &isWhiteTurn) : board(board), isWhiteTurn(isWhiteTurn)
{
	highlighter = new MoveHighlighter(board);
	moves = 0;
	moveStack.clear();
	currentMove = new move_t;
}

Mover::~Mover()
{
	moveStack.clear();
	delete currentMove;
}

int Mover::move(int rank, int file)
{
	tile_t currentTile = board.getBoard()[board.getRank()][board.getFile()];
	// Select which piece to move.
	if (currentMove->tile1.state == 0)
	{
		if ((currentTile.state & otherFlags::isOccupied) && (!(!(currentTile.state & pieceFlags::isWhitePiece)) == isWhiteTurn))
		{
			currentMove->tile1 = currentTile;
			highlighter->highlight(currentTile.rank, currentTile.file);
		}
		else
		{
			currentMove->tile1.state = 0;
			highlighter->noHighlight();
		}
		return 0;
	}
	// If select same tile twice, nothing happens.
	else if (currentMove->tile1.rank == currentTile.rank && currentMove->tile1.file == currentTile.file)
	{
		return 0;
	}
	// If select different tile, check and move piece.
	else
	{
		if (currentTile.state & pieceFlags::isWhitePiece == isWhiteTurn)
		{
			currentMove->tile1 = currentTile;
			highlighter->highlight(currentTile.rank, currentTile.file);
			return 0;
		}
		else if (currentTile.state & otherFlags::isHighlighted)
		{
			currentMove->tile2 = currentTile;
			highlighter->noHighlight();
			moveStack.push_back(*currentMove);
			moves++;
			isWhiteTurn = !isWhiteTurn;
			board.getBoardReference()[currentTile.rank][currentTile.file].state |= otherFlags::hasMoved;
			board.getBoardReference()[currentMove->tile2.rank][currentMove->tile2.file] = currentMove->tile1;
			board.getBoardReference()[currentMove->tile1.rank][currentMove->tile1.file].state &= ~(otherFlags::isOccupied | 0b111111);
			delete currentMove;
			currentMove = new move_t;
			if (currentTile.state & otherFlags::canCapture)
			{
				switch (currentTile.state & 0b111111)
				{
				case pieceFlags::pawn:
					return 1;
				case pieceFlags::rook:
					return 5;
				case pieceFlags::knight:
					return 3;
				case pieceFlags::bishop:
					return 3;
				case pieceFlags::queen:
					return 9;
				default:
					if (currentTile.state & otherFlags::canEnPassant)
						return 1;
					else
						return 0;
				}
			}
			else
				return 0;
		}
		else
		{
			currentMove->tile1.state = 0;
			highlighter->noHighlight();
			return 0;
		}
	}
}

int Mover::undo()
{
	if (moves > 0)
	{
		move_t lastMove = moveStack.back();
		moveStack.pop_back();
		moves--;
		isWhiteTurn = !isWhiteTurn;
		board.getBoardReference()[lastMove.tile1.rank][lastMove.tile1.file] = lastMove.tile1;
		board.getBoardReference()[lastMove.tile2.rank][lastMove.tile2.file] = lastMove.tile2;
		if (lastMove.tile2.state & otherFlags::canCapture)
		{
			switch (lastMove.tile2.state & 0b111111)
			{
			case pieceFlags::pawn:
				return -1;
			case pieceFlags::rook:
				return -5;
			case pieceFlags::knight:
				return -3;
			case pieceFlags::bishop:
				return -3;
			case pieceFlags::queen:
				return -9;
			default:
				if (lastMove.tile2.state & otherFlags::canEnPassant)
					return -1;
				else
					return 0;
			}
		}
		else
			return 0;
	}
	else
		return 0;
}