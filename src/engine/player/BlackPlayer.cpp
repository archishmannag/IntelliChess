#include "../../../include/engine/player/BlackPlayer.hpp"
#include "../../../include/engine/board/Board.hpp"

BlackPlayer::BlackPlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves) : Player(board, blackStandardLegalMoves, whiteStandardLegalMoves) {}

std::vector<Piece *> BlackPlayer::getActivePieces()
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