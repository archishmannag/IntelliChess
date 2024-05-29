#ifndef STANDARD_BOARD_EVALUATOR_HPP
#define STANDARD_BOARD_EVALUATOR_HPP

#include <engine/player/ai/BoardEvaluator.hpp>

class Board;
class Player;

class StandardBoardEvaluator final : public BoardEvaluator
{
private:
	int scorePlayer(Board *board, const Player *player, int depth);
	static int pieceValue(const Player *player);
	static int mobilityValue(const Player *player);
	static int checkValue(const Player *player);
	static int checkMateValue(const Player *player, int depth);
	static int castled(const Player *player);
	static int depthBonus(int depth);

public:
	int evaluate(Board *board, int depth) override;
};

#endif