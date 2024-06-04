#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/board/Board.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/Piece.hpp>

// The following values are used to calculate the score of a player
#define CHECK_BONUS 50
#define CHECK_MATE_BONUS 10000
#define DEPTH_BONUS 100
#define CASTLE_BONUS 60

int standard_board_evaluator::evaluate(board *b, int d)
{
	return player_score(b->get_white_player().get(), d) - player_score(b->get_black_player().get(), d);
}

int standard_board_evaluator::player_score(const player *p, int d)
{
	return piece_value(p) +
		   mobility_value(p) +
		   check_value(p) +
		   checkmate_value(p, d) +
		   has_castled(p);
}

int standard_board_evaluator::piece_value(const player *p)
{
	int piece_value_score = 0;
	for (auto piece : p->get_active_pieces())
		piece_value_score += piece->get_piece_value();
	return piece_value_score;
}

int standard_board_evaluator::mobility_value(const player *p)
{
	return p->get_legal_moves().size();
}

int standard_board_evaluator::check_value(const player *p)
{
	return p->is_in_check() ? CHECK_BONUS : 0;
}

int standard_board_evaluator::checkmate_value(const player *p, int d)
{
	return p->is_is_checkmate() ? CHECK_MATE_BONUS * depth_bonus(d) : 0;
}

int standard_board_evaluator::depth_bonus(int d)
{
	return d == 0 ? 1 : DEPTH_BONUS * d;
}

int standard_board_evaluator::has_castled(const player *p)
{
	return p->is_castled() ? CASTLE_BONUS : 0;
}