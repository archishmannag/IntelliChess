#include <gui/GuiUtils.hpp>

/* move_log */

std::vector<std::shared_ptr<move>> move_log::get_moves() const
{
	return moves;
}

int move_log::get_moves_count() const
{
	return moves.size();
}

void move_log::add_move(std::shared_ptr<move> m)
{
	moves.push_back(m);
}

std::shared_ptr<move> move_log::remove_move(int index)
{
	std::shared_ptr<move> m = moves[index];
	moves.erase(moves.begin() + index);
	return m;
}

void move_log::remove_move(std::shared_ptr<move> m)
{
	moves.erase(std::remove(moves.begin(), moves.end(), m), moves.end());
}

void move_log::clear_moves()
{
	moves.clear();
}