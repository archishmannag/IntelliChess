#include "../../../include/engine/pieces/King.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/Tile.hpp"
#include "../../../include/engine/board/Board.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int King::CANDIDATE_MOVE_COORDINATES[] = {-9, -8, -7, -1, 1, 7, 8, 9};

King::King(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance, PieceType::KING, true)
{
}

King::King(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove) : Piece(piecePosition, pieceAlliance, PieceType::KING, isFirstMove)
{
}

std::vector<Move *> King::calculateLegalMoves(Board &board)
{
	std::vector<Move *> legalMoves;
	int candidateDestinationCoordinate;
	for (const int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES)
	{
		candidateDestinationCoordinate = this->piecePosition + currentCandidateOffset;
		if (BoardUtils::isValidTileCoordinate(candidateDestinationCoordinate))
		{
			if (isFirstColumnExclusion(this->piecePosition, currentCandidateOffset) || isEighthColumnExclusion(this->piecePosition, currentCandidateOffset))
				continue;
			const Tile *candidateDestinationTile = board.getTile(candidateDestinationCoordinate);
			if (!candidateDestinationTile->isTileOccupied())
				legalMoves.push_back(new MajorMove(&board, this, candidateDestinationCoordinate));
			else
			{
				Piece *pieceAtDestination = candidateDestinationTile->getPiece();
				if (this->pieceAlliance != pieceAtDestination->getPieceAlliance())
					legalMoves.push_back(new MajorAttackMove(&board, this, pieceAtDestination, candidateDestinationCoordinate));
			}
		}
	}
	return legalMoves;
}

King *King::movePiece(const Move *move) const
{
	return new King(move->getDestinationCoordinate(), move->getMovedPiece()->getPieceAlliance());
}

bool King::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == -1 || candidateOffset == 7);
}

bool King::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 1 || candidateOffset == 9);
}