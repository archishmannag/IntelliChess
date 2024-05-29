#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/board/Board.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/Piece.hpp>

// The following values are used to calculate the score of a player
#define CHECK_BONUS 50
#define CHECK_MATE_BONUS 10000
#define DEPTH_BONUS 100
#define CASTLE_BONUS 60

int StandardBoardEvaluator::evaluate(Board *board, int depth)
{
	return scorePlayer(board, board->getWhitePlayer(), depth) - scorePlayer(board, board->getBlackPlayer(), depth);
}

int StandardBoardEvaluator::scorePlayer(Board *board, const Player *player, int depth)
{
	return pieceValue(player) +
		   mobilityValue(player) +
		   checkValue(player) +
		   checkMateValue(player, depth) +
		   castled(player);
}

int StandardBoardEvaluator::pieceValue(const Player *player)
{
	int pieceValueScore = 0;
	for (const auto piece : player->getActivePieces())
		pieceValueScore += piece->getPieceValue();
	return pieceValueScore;
}

int StandardBoardEvaluator::mobilityValue(const Player *player)
{
	return player->getLegalMoves().size();
}

int StandardBoardEvaluator::checkValue(const Player *player)
{
	return player->isInCheck() ? CHECK_BONUS : 0;
}

int StandardBoardEvaluator::checkMateValue(const Player *player, int depth)
{
	return player->isInCheckMate() ? CHECK_MATE_BONUS * depthBonus(depth) : 0;
}

int StandardBoardEvaluator::depthBonus(int depth)
{
	return depth == 0 ? 1 : DEPTH_BONUS * depth;
}

int StandardBoardEvaluator::castled(const Player *player)
{
	return player->isCastled() ? CASTLE_BONUS : 0;
}