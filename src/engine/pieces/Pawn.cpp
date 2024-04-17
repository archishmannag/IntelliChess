#include "../../../include/engine/pieces/Pawn.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/BoardUtils.hpp"

const int Pawn::CANDIDATE_MOVE_COORDINATES[] = {8, 16, 7, 9};

Pawn::Pawn(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance)
{
	this->pieceType = PieceType::PAWN;
}

std::vector<Move *> Pawn::calculateLegalMoves(Board &board)
{
	std::vector<Move *> legalMoves;
	int candidateDestinationCoordinate, behindCandidateDestinationCoordinate;
	for (const int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES)
	{
		candidateDestinationCoordinate = this->piecePosition + (currentCandidateOffset * AllianceUtils::getDirection(this->pieceAlliance));
		if (!BoardUtils::isValidTileCoordinate(candidateDestinationCoordinate))
			continue;

		if (currentCandidateOffset == 8 && !board.getTile(candidateDestinationCoordinate).isTileOccupied())
			legalMoves.push_back(new MajorMove(board, *this, candidateDestinationCoordinate));
		else if (currentCandidateOffset == 16 && this->getIsFirstMove() && ((BoardUtils::SECOND_ROW[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance)) || (BoardUtils::SEVENTH_ROW[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance))))
		{
			behindCandidateDestinationCoordinate = this->piecePosition + (AllianceUtils::getDirection(this->pieceAlliance) * 8);
			if (!board.getTile(behindCandidateDestinationCoordinate).isTileOccupied() && !board.getTile(candidateDestinationCoordinate).isTileOccupied())
			{
				legalMoves.push_back(new MajorMove(board, *this, candidateDestinationCoordinate));
			}
		}
		else if (currentCandidateOffset == 7 && !((BoardUtils::EIGHTH_COLUMN[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance)) || (BoardUtils::FIRST_COLUMN[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance))))
		{
			if (board.getTile(candidateDestinationCoordinate).isTileOccupied())
			{
				Piece pieceOnCandidate = *board.getTile(candidateDestinationCoordinate).getPiece();
				if (this->pieceAlliance != pieceOnCandidate.getPieceAlliance())
					legalMoves.push_back(new AttackMove(board, *this, pieceOnCandidate, candidateDestinationCoordinate));
			}
		}
		else if (currentCandidateOffset == 9 && !((BoardUtils::EIGHTH_COLUMN[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance)) || (BoardUtils::FIRST_COLUMN[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance))))
		{
			if (board.getTile(candidateDestinationCoordinate).isTileOccupied())
			{
				Piece pieceOnCandidate = *board.getTile(candidateDestinationCoordinate).getPiece();
				if (this->pieceAlliance != pieceOnCandidate.getPieceAlliance())
					legalMoves.push_back(new AttackMove(board, *this, pieceOnCandidate, candidateDestinationCoordinate));
			}
		}
	}
	return legalMoves;
}
