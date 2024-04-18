#include "../../../include/engine/pieces/King.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int King::CANDIDATE_MOVE_COORDINATES[] = {-9, -8, -7, -1, 1, 7, 8, 9};

King::King(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance)
{
	this->pieceType = PieceType::KING;
};

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
				legalMoves.push_back(new MajorMove(board, *this, candidateDestinationCoordinate));
			else
			{
				const Piece pieceAtDestination = *candidateDestinationTile->getPiece();
				if (this->pieceAlliance != pieceAtDestination.getPieceAlliance())
					legalMoves.push_back(new AttackMove(board, *this, pieceAtDestination, candidateDestinationCoordinate));
			}
		}
	}
	return legalMoves;
}

bool King::isFirstColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::FIRST_COLUMN[currentPosition] && (candidateOffset == -9 || candidateOffset == -1 || candidateOffset == 7);
}

bool King::isEighthColumnExclusion(const int currentPosition, const int candidateOffset)
{
	return BoardUtils::EIGHTH_COLUMN[currentPosition] && (candidateOffset == -7 || candidateOffset == 1 || candidateOffset == 9);
}