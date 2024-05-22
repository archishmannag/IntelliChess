#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Queen.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/pieces/Knight.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>

const int Pawn::CANDIDATE_MOVE_COORDINATES[] = {8, 16, 7, 9};

Pawn::Pawn(const int piecePosition, const Alliance pieceAlliance) : Piece(piecePosition, pieceAlliance, PieceType::PAWN, true)
{
}

Pawn::Pawn(const int piecePosition, const Alliance pieceAlliance, const bool isFirstMove) : Piece(piecePosition, pieceAlliance, PieceType::PAWN, isFirstMove)
{
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

		if (currentCandidateOffset == 8 && !board.getTile(candidateDestinationCoordinate)->isTileOccupied())
		{
			if (AllianceUtils::isPawnPromotionSquare(this->pieceAlliance, candidateDestinationCoordinate))
			{
				legalMoves.push_back(new PawnPromotion(new PawnMove(&board, this, candidateDestinationCoordinate), new Queen(candidateDestinationCoordinate, this->pieceAlliance)));
				legalMoves.push_back(new PawnPromotion(new PawnMove(&board, this, candidateDestinationCoordinate), new Rook(candidateDestinationCoordinate, this->pieceAlliance)));
				legalMoves.push_back(new PawnPromotion(new PawnMove(&board, this, candidateDestinationCoordinate), new Knight(candidateDestinationCoordinate, this->pieceAlliance)));
				legalMoves.push_back(new PawnPromotion(new PawnMove(&board, this, candidateDestinationCoordinate), new Bishop(candidateDestinationCoordinate, this->pieceAlliance)));
			}
			else
				legalMoves.push_back(new PawnMove(&board, this, candidateDestinationCoordinate));
		}
		else if (currentCandidateOffset == 16 && this->getIsFirstMove() && ((BoardUtils::SECOND_ROW[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance)) || (BoardUtils::SEVENTH_ROW[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance))))
		{
			behindCandidateDestinationCoordinate = this->piecePosition + (AllianceUtils::getDirection(this->pieceAlliance) * 8);
			if (!board.getTile(behindCandidateDestinationCoordinate)->isTileOccupied() && !board.getTile(candidateDestinationCoordinate)->isTileOccupied())
			{
				legalMoves.push_back(new PawnJump(&board, this, candidateDestinationCoordinate));
			}
		}
		else if (currentCandidateOffset == 7 && !((BoardUtils::EIGHTH_COLUMN[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance)) || (BoardUtils::FIRST_COLUMN[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance))))
		{
			if (board.getTile(candidateDestinationCoordinate)->isTileOccupied())
			{
				Piece *pieceOnCandidate = board.getTile(candidateDestinationCoordinate)->getPiece();
				if (this->pieceAlliance != pieceOnCandidate->getPieceAlliance())
				{
					if (AllianceUtils::isPawnPromotionSquare(this->pieceAlliance, candidateDestinationCoordinate))
					{
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Queen(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Rook(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Knight(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Bishop(candidateDestinationCoordinate, this->pieceAlliance)));
					}
					else
						legalMoves.push_back(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate));
				}
			}
			else if (board.getEnPassantPawn() != nullptr && board.getEnPassantPawn()->getPiecePosition() == this->piecePosition + AllianceUtils::getOppositeDirection(this->pieceAlliance))
			{
				auto pieceOnCandidate = board.getEnPassantPawn();
				if (this->pieceAlliance != pieceOnCandidate->getPieceAlliance())
					legalMoves.push_back(new PawnEnPassantAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate));
			}
		}
		else if (currentCandidateOffset == 9 && !((BoardUtils::EIGHTH_COLUMN[this->piecePosition] && AllianceUtils::isBlack(this->pieceAlliance)) || (BoardUtils::FIRST_COLUMN[this->piecePosition] && AllianceUtils::isWhite(this->pieceAlliance))))
		{
			if (board.getTile(candidateDestinationCoordinate)->isTileOccupied())
			{
				Piece *pieceOnCandidate = board.getTile(candidateDestinationCoordinate)->getPiece();
				if (this->pieceAlliance != pieceOnCandidate->getPieceAlliance())
				{
					if (AllianceUtils::isPawnPromotionSquare(this->pieceAlliance, candidateDestinationCoordinate))
					{
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Queen(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Rook(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Knight(candidateDestinationCoordinate, this->pieceAlliance)));
						legalMoves.push_back(new PawnPromotion(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate), new Bishop(candidateDestinationCoordinate, this->pieceAlliance)));
					}
					else
						legalMoves.push_back(new PawnAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate));
				}
			}
			else if (board.getEnPassantPawn() != nullptr && board.getEnPassantPawn()->getPiecePosition() == this->piecePosition - AllianceUtils::getOppositeDirection(this->pieceAlliance))
			{
				auto pieceOnCandidate = board.getEnPassantPawn();
				if (this->pieceAlliance != pieceOnCandidate->getPieceAlliance())
					legalMoves.push_back(new PawnEnPassantAttackMove(&board, this, pieceOnCandidate, candidateDestinationCoordinate));
			}
		}
	}
	return legalMoves;
}

Pawn *Pawn::movePiece(const Move *move) const
{
	return new Pawn(move->getDestinationCoordinate(), move->getMovedPiece()->getPieceAlliance());
}