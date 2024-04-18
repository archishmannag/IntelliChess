#include "../../../include/engine/pieces/Bishop.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int Bishop::CANDIDATE_MOVE_VECTOR_COORDINATES[] = {-9, -7, 7, 9};

Bishop::Bishop(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance)
{
	this->pieceType = PieceType::BISHOP;
};

std::vector<Move *> Bishop::calculateLegalMoves(Board &board)
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

bool Bishop::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == 7);
}

bool Bishop::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 9);
}