#include "../../../include/engine/pieces/Bishop.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/Tile.hpp"
#include "../../../include/engine/board/Board.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int Bishop::CANDIDATE_MOVE_VECTOR_COORDINATES[] = {-9, -7, 7, 9};

Bishop::Bishop(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance, PieceType::BISHOP, true)
{
}

Bishop::Bishop(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove) : Piece(piecePosition, pieceAlliance, PieceType::BISHOP, isFirstMove)
{
}

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

Bishop *Bishop::movePiece(const Move *move) const
{
	return new Bishop(move->getDestinationCoordinate(), move->getMovedPiece()->getPieceAlliance());
}

bool Bishop::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == 7);
}

bool Bishop::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 9);
}