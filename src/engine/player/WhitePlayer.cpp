#include <engine/player/WhitePlayer.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Tile.hpp>
#include <engine/board/Board.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Rook.hpp>

WhitePlayer::WhitePlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves) : Player(board)
{
	this->playerKing = establishKing();
	this->legalMoves = whiteStandardLegalMoves;
	std::vector<Move *> kingCastleMoves = calculateKingCastles(whiteStandardLegalMoves, blackStandardLegalMoves);
	whiteStandardLegalMoves.insert(whiteStandardLegalMoves.end(), kingCastleMoves.begin(), kingCastleMoves.end());
	this->inCheck = !calculateAttacksOnTile(this->playerKing->getPiecePosition(), blackStandardLegalMoves).empty();
}

std::vector<Piece *> WhitePlayer::getActivePieces() const
{
	return this->board->getWhitePieces();
}

Alliance WhitePlayer::getPlayerAlliance() const
{
	return Alliance::WHITE;
}

const Player *WhitePlayer::getOpponent() const
{
	return this->board->getBlackPlayer();
}

std::vector<Move *> WhitePlayer::calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const
{
	std::vector<Move *> kingCastles;
	if (this->playerKing->getIsFirstMove() && !this->isInCheck())
	{
		// White king side castle
		if (!this->board->getTile(61)->isTileOccupied() && !this->board->getTile(62)->isTileOccupied())
		{
			Tile *rookTile = this->board->getTile(63);
			if (rookTile->isTileOccupied() && rookTile->getPiece()->getIsFirstMove() && rookTile->getPiece()->getPieceType() == PieceType::ROOK)
				if (calculateAttacksOnTile(61, opponentLegals).empty() && calculateAttacksOnTile(62, opponentLegals).empty())
					kingCastles.push_back(new KingSideCastleMove(this->board, this->playerKing, 62, dynamic_cast<Rook *>(rookTile->getPiece()), rookTile->getTileCoordinate(), 61));
		}
		// White queen side castle
		if (!this->board->getTile(59)->isTileOccupied() && !this->board->getTile(58)->isTileOccupied() && !this->board->getTile(57)->isTileOccupied())
		{
			Tile *rookTile = this->board->getTile(56);
			if (rookTile->isTileOccupied() && rookTile->getPiece()->getIsFirstMove() && rookTile->getPiece()->getPieceType() == PieceType::ROOK)
				if (calculateAttacksOnTile(59, opponentLegals).empty() && calculateAttacksOnTile(58, opponentLegals).empty() && calculateAttacksOnTile(57, opponentLegals).empty())
					kingCastles.push_back(new QueenSideCastleMove(this->board, this->playerKing, 58, dynamic_cast<Rook *>(rookTile->getPiece()), rookTile->getTileCoordinate(), 59));
		}
	}
	return kingCastles;
}