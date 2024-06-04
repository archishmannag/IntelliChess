#include <engine/Alliance.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>

int alliance_utils::get_direction(const alliance a)
{
	return a == alliance::white ? -1 : 1;
}

int alliance_utils::get_opposite_direction(const alliance a)
{
	return a == alliance::white ? 1 : -1;
}

bool alliance_utils::is_white(const alliance a)
{
	return a == alliance::white;
}

bool alliance_utils::is_black(const alliance a)
{
	return a == alliance::black;
}

bool alliance_utils::is_pawn_promotion_square(const alliance a, const int p)
{
	return (is_black(a) && board_utils::eighth_row[p]) || (is_white(a) && board_utils::first_row[p]);
}

std::shared_ptr<player> alliance_utils::choose_player(alliance a, board *b)
{
	return a == alliance::white ? b->get_white_player() : b->get_black_player();
}

std::string alliance_utils::stringify(const alliance a)
{
	return a == alliance::white ? "White" : "Black";
}