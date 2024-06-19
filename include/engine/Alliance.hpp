#ifndef ALLIANCE_HPP
#define ALLIANCE_HPP

#include <PreCompiledHeaders.hpp>

class player;
class board;
class piece;

enum class alliance
{
	white,
	black
};

namespace alliance_utils
{
	int get_direction(alliance a);
	int get_opposite_direction(alliance a);
	bool is_white(alliance a);
	bool is_black(alliance a);
	bool is_pawn_promotion_square(alliance a, int p);
	std::shared_ptr<player> choose_player(alliance a, board *b);
	int get_location_bonus(const piece *p);

	std::string stringify(alliance a);
} // namespace alliance_utils

#endif // ALLIANCE_HPP