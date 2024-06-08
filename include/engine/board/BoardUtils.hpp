#ifndef BOARDUTILS_HPP
#define BOARDUTILS_HPP

#include <array>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class board;
class king;
class move;

namespace board_utils
{
	extern std::array<bool, 64>
		first_column, second_column, third_column, fourth_column, fifth_column, sixth_column, seventh_column, eighth_column,
		first_row, second_row, third_row, fourth_row, fifth_row, sixth_row, seventh_row, eighth_row;

	bool is_valid_tile_coordinate(int c);
	int get_coordinate_at_position(std::string p);
	std::string get_position_at_coordinate(int c);

	bool king_threat(std::shared_ptr<move> m);
	bool is_king_pawn_trap(const board *b, const king *k, const int ft);
	int mvv_lva(const move *m);
	bool game_over(const board *b);

	std::string calculate_check_and_checkmate(board *b);
}

#endif