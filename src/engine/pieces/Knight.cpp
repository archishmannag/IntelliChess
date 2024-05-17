#include "../../../include/engine/pieces/Knight.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/Tile.hpp"
#include "../../../include/engine/board/Board.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

Knight::Knight(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance, PieceType::KNIGHT, true)
{
}

Knight::Knight(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove) : Piece(piecePosition, pieceAlliance, PieceType::KNIGHT, isFirstMove)
{
}

const int Knight::CANDIDATE_MOVE_COORDINATES[] = {-17, -15, -10, -6, 6, 10, 15, 17};

std::vector<Move *> Knight::calculateLegalMoves(Board &board)
{
	int candidateDestinationCoordinate;
	std::vector<Move *> legalMoves;

	for (const int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES)
	{
		candidateDestinationCoordinate = this->piecePosition + currentCandidateOffset;
		if (BoardUtils::isValidTileCoordinate(candidateDestinationCoordinate))
		{
			if (isFirstColumnExclusion(this->piecePosition, currentCandidateOffset) || isSecondColumnExclusion(this->piecePosition, currentCandidateOffset) || isSeventhColumnExclusion(this->piecePosition, currentCandidateOffset) || isEighthColumnExclusion(this->piecePosition, currentCandidateOffset))
				continue;

			const Tile *candidateDestinationTile = board.getTile(candidateDestinationCoordinate);

			if (!candidateDestinationTile->isTileOccupied())
				legalMoves.push_back(new MajorMove(&board, this, candidateDestinationCoordinate));
			else
			{
				Piece *pieceAtDestination = candidateDestinationTile->getPiece();
				Alliance pieceAlliance = pieceAtDestination->getPieceAlliance();

				if (this->pieceAlliance != pieceAlliance)
					legalMoves.push_back(new MajorAttackMove(&board, this, pieceAtDestination, candidateDestinationCoordinate));
			}
		}
	}
	return legalMoves;
}

Knight *Knight::movePiece(const Move *move) const
{
	return new Knight(move->getDestinationCoordinate(), move->getMovedPiece()->getPieceAlliance());
}

bool Knight::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -17 || candidateOffset == -10 || candidateOffset == 6 || candidateOffset == 15);
}

bool Knight::isSecondColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::SECOND_COLUMN[currentPosition] && (candidateOffset == -10 || candidateOffset == 6);
}

bool Knight::isSeventhColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::SEVENTH_COLUMN[currentPosition] && (candidateOffset == 10 || candidateOffset == -6);
}

bool Knight::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == 17 || candidateOffset == 10 || candidateOffset == -6 || candidateOffset == -15);
}