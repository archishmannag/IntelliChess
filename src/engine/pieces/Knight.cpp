#include "../../../include/engine/pieces/Knight.hpp"

const int Knight::CANDIDATE_MOVE_COORDINATES[] = {-17, -15, -10, -6, 6, 10, 15, 17};

const std::list<Move> Knight::calculateLegalMoves(const Board board)
{
	int candidateDestinationCoordinate;
	std::list<Move> legalMoves;

	for (const int currentCandidate : CANDIDATE_MOVE_COORDINATES)
	{
		candidateDestinationCoordinate = this->piecePosition + currentCandidate;
		if (true)
		{
			const Tile candidateDestinationTile = board.getTile(candidateDestinationCoordinate);

			if (!candidateDestinationTile.isTileOccupied())
				legalMoves.push_back(Move());
			else
			{
				Piece pieceAtDestination = *(candidateDestinationTile.getPiece());
				Alliance pieceAlliance = pieceAtDestination.getPieceAlliance();

				if (this->pieceAlliance != pieceAlliance)
					legalMoves.push_back(Move());
			}
		}
	}
	return legalMoves;
}