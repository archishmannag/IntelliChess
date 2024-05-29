#include <engine/pieces/Rook.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>

const int Rook::CANDIDATE_MOVE_VECTOR_COORDINATES[] = {-8, -1, 1, 8};

Rook::Rook(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove) : Piece(piecePosition, pieceAlliance, PieceType::ROOK, isFirstMove)
{
}

std::vector<Move *> Rook::calculateLegalMoves(Board &board)
{
	std::vector<Move *> legalMoves;
	int candidateDestinationCoordinate;
	for (const int currentCandidateOffset : CANDIDATE_MOVE_VECTOR_COORDINATES)
	{
		candidateDestinationCoordinate = this->piecePosition;
		while (BoardUtils::isValidTileCoordinate(candidateDestinationCoordinate))
		{
			if (isFirstColumnExclusion(candidateDestinationCoordinate, currentCandidateOffset) || isEighthColumnExclusion(candidateDestinationCoordinate, currentCandidateOffset))
				break;
			candidateDestinationCoordinate += currentCandidateOffset;
			if (BoardUtils::isValidTileCoordinate(candidateDestinationCoordinate))
			{
				const Tile *candidateDestinationTile = board.getTile(candidateDestinationCoordinate);
				if (!candidateDestinationTile->isTileOccupied())
					legalMoves.push_back(new MajorMove(&board, this, candidateDestinationCoordinate));
				else
				{
					Piece *pieceAtDestination = candidateDestinationTile->getPiece();
					Alliance pieceAlliance = pieceAtDestination->getPieceAlliance();
					if (this->pieceAlliance != pieceAlliance)
						legalMoves.push_back(new MajorAttackMove(&board, this, pieceAtDestination, candidateDestinationCoordinate));
					break;
				}
			}
		}
	}
	return legalMoves;
}

Rook *Rook::movePiece(const Move *move) const
{
	return new Rook(move->getDestinationCoordinate(), move->getMovedPiece()->getPieceAlliance(), false);
}

bool Rook::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -1);
}

bool Rook::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == 1);
}