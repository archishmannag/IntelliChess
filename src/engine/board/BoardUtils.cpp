#include <engine/board/BoardUtils.hpp>
#include <engine/board/Board.hpp>
#include <engine/player/Player.hpp>

namespace
{
	std::array<bool, 64> init_column(int c)
	{
		std::array<bool, 64> column;
		for (int i = 0; i < 64; i++)
		{
			if (i == c)
			{
				column[i] = true;
				c += 8;
			}
			else
				column[i] = false;
		}
		return column;
	}

	std::array<bool, 64> init_row(int r)
	{
		std::array<bool, 64> row;
		int rowStart = r * 8;
		for (int i = 0; i < 64; i++)
		{
			if (i >= rowStart && i < rowStart + 8)
				row[i] = true;
			else
				row[i] = false;
		}
		return row;
	}
}

std::array<bool, 64> board_utils::first_column = init_column(0);
std::array<bool, 64> board_utils::second_column = init_column(1);
std::array<bool, 64> board_utils::third_column = init_column(2);
std::array<bool, 64> board_utils::fourth_column = init_column(3);
std::array<bool, 64> board_utils::fifth_column = init_column(4);
std::array<bool, 64> board_utils::sixth_column = init_column(5);
std::array<bool, 64> board_utils::seventh_column = init_column(6);
std::array<bool, 64> board_utils::eighth_column = init_column(7);

std::array<bool, 64> board_utils::first_row = init_row(0);
std::array<bool, 64> board_utils::second_row = init_row(1);
std::array<bool, 64> board_utils::third_row = init_row(2);
std::array<bool, 64> board_utils::fourth_row = init_row(3);
std::array<bool, 64> board_utils::fifth_row = init_row(4);
std::array<bool, 64> board_utils::sixth_row = init_row(5);
std::array<bool, 64> board_utils::seventh_row = init_row(6);
std::array<bool, 64> board_utils::eighth_row = init_row(7);

std::array<std::string, 64> board_utils::algebraic_notation = board_utils::initialize_algebraic_notation();
std::map<std::string, int> board_utils::position_to_coordinate = board_utils::initialize_position_to_coordinate_map();

bool board_utils::is_valid_tile_coordinate(int c)
{
	return c >= 0 && c < 64;
};

int board_utils::get_coordinate_at_position(std::string p)
{
	return position_to_coordinate.find(p)->second;
}

std::string board_utils::get_position_at_coordinate(int c)
{
	return algebraic_notation[c];
}

std::array<std::string, 64> board_utils::initialize_algebraic_notation()
{
	std::array<std::string, 64> algebraic_notation;
	int position = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			algebraic_notation[position++] = std::string(1, 'a' + j) + std::to_string(8 - i);
		}
	return algebraic_notation;
}

std::map<std::string, int> board_utils::initialize_position_to_coordinate_map()
{
	std::map<std::string, int> position_to_coordinate;
	for (int i = 0; i < 64; i++)
		position_to_coordinate[algebraic_notation[i]] = i;
	return position_to_coordinate;
}

std::string board_utils::calculate_check_and_checkmate(board *b)
{
	if (b->get_current_player()->is_is_checkmate())
	{
		return "#";
	}
	else if (b->get_current_player()->is_in_check())
	{
		return "+";
	}
	return "";
}