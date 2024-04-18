#include "../../../include/engine/pieces/Queen.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int Queen::CANDIDATE_MOVE_VECTOR_COORDINATES[] = {-9, -8, -7, -1, 1, 7, 8, 9};

Queen::Queen(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance, PieceType::QUEEN)
{
}

std::vector<Move *> Queen::calculateLegalMoves(Board &board)
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
					legalMoves.push_back(new MajorMove(board, *this, candidateDestinationCoordinate));
				else
				{
					Piece pieceAtDestination = *(candidateDestinationTile->getPiece());
					Alliance pieceAlliance = pieceAtDestination.getPieceAlliance();
					if (this->pieceAlliance != pieceAlliance)
						legalMoves.push_back(new AttackMove(board, *this, pieceAtDestination, candidateDestinationCoordinate));
					break;
				}
			}
		}
	}
	return legalMoves;
}

bool Queen::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -1 || candidateOffset == -9 || candidateOffset == 7);
}

bool Queen::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == 1 || candidateOffset == -7 || candidateOffset == 9);
}