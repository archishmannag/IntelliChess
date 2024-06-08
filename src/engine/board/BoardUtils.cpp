#include <engine/board/BoardUtils.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/board/Tile.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
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

	std::array<std::string, 64> initialize_algebraic_notation()
	{
		std::array<std::string, 64> algebraic_notation = {
			"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
			"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
			"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
			"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
			"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
			"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
			"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
			"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"};
		return algebraic_notation;
	}

	std::array<std::string, 64> algebraic_notation = initialize_algebraic_notation();

	std::unordered_map<std::string, int> initialize_position_to_coordinate_map()
	{
		std::unordered_map<std::string, int> position_to_coordinate;
		for (int i = 0; i < 64; i++)
			position_to_coordinate[algebraic_notation[i]] = i;
		return position_to_coordinate;
	}

	std::unordered_map<std::string, int> position_to_coordinate = initialize_position_to_coordinate_map();
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

bool board_utils::king_threat(std::shared_ptr<move> m)
{
	std::shared_ptr<board> b = m->get_board();
	move_transition transition = b->get_current_player()->make_move(m);
	return transition.get_transition_board()->get_current_player()->is_in_check();
}

bool board_utils::is_king_pawn_trap(const board *b, const king *k, const int ft)
{
	std::shared_ptr<piece> p = b->get_tile(ft)->get_piece();
	return p &&
		   p->get_piece_type() == piece_type::pawn &&
		   p->get_piece_alliance() != k->get_piece_alliance();
}

int board_utils::mvv_lva(const move *m)
{
	std::shared_ptr<piece> moving_piece = m->get_moved_piece();

	// For reference
	king k(64, alliance::white);

	if (m->is_attack())
	{
		std::shared_ptr<piece> attacked_piece = m->get_attacked_piece();
		return (attacked_piece->get_piece_value() - moving_piece->get_piece_value() + k.get_piece_value()) * 100;
	}
	return k.get_piece_value() - moving_piece->get_piece_value();
}

bool board_utils::game_over(const board *b)
{
	return b->get_current_player()->is_is_checkmate() || b->get_current_player()->is_in_stalemate();
}

// std::vector<std::shared_ptr<move>> board_utils::last_n_moves(const board *b, const int n)
// {
// 	std::vector<std::shared_ptr<move>> move_history;
// 	std::shared_ptr<move> current_move = b->get_transition_move();
// 	int i = 0;
// 	while (!(*current_move == *move::get_null_move()) && i < n)
// 	{
// 		move_history.push_back(current_move);
// 		current_move = current_move->get_board()->get_transition_move();
// 		i++;
// 	}
// 	return move_history;
// }