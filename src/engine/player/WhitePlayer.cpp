#include "../../../include/engine/player/WhitePlayer.hpp"
#include "../../../include/engine/board/Board.hpp"

WhitePlayer::WhitePlayer(Board *board, std::vector<Move *> whiteStandardLegalMoves, std::vector<Move *> blackStandardLegalMoves) : Player(board, whiteStandardLegalMoves, blackStandardLegalMoves) {}

std::vector<Piece *> WhitePlayer::getActivePieces()
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