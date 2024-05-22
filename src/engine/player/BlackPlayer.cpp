#include <engine/player/BlackPlayer.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Rook.hpp>

BlackPlayer::BlackPlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves) : Player(board)
{
	this->playerKing = establishKing();
	this->inCheck = !calculateAttacksOnTile(this->playerKing->getPiecePosition(), whiteStandardLegalMoves).empty();
	std::vector<Move *> kingCastleMoves = calculateKingCastles(blackStandardLegalMoves, whiteStandardLegalMoves);
	blackStandardLegalMoves.insert(blackStandardLegalMoves.end(), kingCastleMoves.begin(), kingCastleMoves.end());
	this->legalMoves = blackStandardLegalMoves;
}

std::vector<Piece *> BlackPlayer::getActivePieces() const
{
	return this->board->getBlackPieces();
}

Alliance BlackPlayer::getPlayerAlliance() const
{
	return Alliance::BLACK;
}

const Player *BlackPlayer::getOpponent() const
{
	return this->board->getWhitePlayer();
}

std::vector<Move *> BlackPlayer::calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const
{
	std::vector<Move *> kingCastles;
	if (this->playerKing->getIsFirstMove() && !this->isInCheck())
	{
		// Black king side castle
		if (!this->board->getTile(5)->isTileOccupied() && !this->board->getTile(6)->isTileOccupied())
		{
			Tile *rookTile = this->board->getTile(7);
			if (rookTile->isTileOccupied() && rookTile->getPiece()->getIsFirstMove() && rookTile->getPiece()->getPieceType() == PieceType::ROOK)
				if (calculateAttacksOnTile(5, opponentLegals).empty() && calculateAttacksOnTile(6, opponentLegals).empty())
					kingCastles.push_back(new KingSideCastleMove(this->board, this->playerKing, 6, dynamic_cast<Rook *>(rookTile->getPiece()), rookTile->getTileCoordinate(), 5));
		}
		// Black queen side castle
		if (!this->board->getTile(3)->isTileOccupied() && !this->board->getTile(2)->isTileOccupied() && !this->board->getTile(1)->isTileOccupied())
		{
			Tile *rookTile = this->board->getTile(0);
			if (rookTile->isTileOccupied() && rookTile->getPiece()->getIsFirstMove() && rookTile->getPiece()->getPieceType() == PieceType::ROOK)
				if (calculateAttacksOnTile(3, opponentLegals).empty() && calculateAttacksOnTile(2, opponentLegals).empty() && calculateAttacksOnTile(1, opponentLegals).empty())
					kingCastles.push_back(new QueenSideCastleMove(this->board, this->playerKing, 2, dynamic_cast<Rook *>(rookTile->getPiece()), rookTile->getTileCoordinate(), 3));
		}
	}
	return kingCastles;
}

std::string BlackPlayer::stringify() const
{
	return std::string("Black");
}