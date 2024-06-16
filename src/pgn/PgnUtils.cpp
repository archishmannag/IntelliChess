#include <pgn/PgnUtils.hpp>
#include <pgn/FenUtils.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/Move.hpp>
#include <engine/player/Player.hpp>
#include <engine/Alliance.hpp>

namespace
{
	std::string calculate_event_string()
	{
		return "[Event \"IntelliChess\"]";
	}

	std::string calculate_date_string()
	{
		std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm *time = std::localtime(&current_time);
		std::ostringstream oss;
		oss << "[Date \"" << std::put_time(time, "%Y.%m.%d") << "\"]";
		return oss.str();
	}

	std::string calculate_ply_string(std::size_t size)
	{
		return "[PlyCount \"" + std::to_string(size) + "\"]";
	}

	std::string calculate_result_string(const board &b)
	{
		if (b.get_current_player()->is_is_checkmate())
		{
			if (b.get_current_player()->get_player_alliance() == alliance::white)
				return "1-0";
			else
				return "0-1";
		}
		else if (b.get_current_player()->is_in_stalemate())
			return "1/2-1/2";
		else
			return "*";
	}
} // namespace

void pgn_utils::save_game_to_pgn(const std::string &file_path, const std::vector<std::shared_ptr<move>> &moves, const board &b)
{
	std::stringstream pgn;
	pgn
		<< calculate_event_string() << '\n'
		<< calculate_date_string() << '\n'
		<< calculate_ply_string(moves.size()) << '\n'
		<< calculate_result_string(b) << '\n'
		<< "[FEN \"" << fen_utils::board_to_fen(b) << "\"]" << '\n';

	for (std::size_t i = 0; i < moves.size(); i++)
	{
		if (i % 2 == 0)
			pgn << i / 2 + 1 << ". "
				<< moves[i]->stringify() << " ";
		else
			pgn << moves[i]->stringify() << " ";
	}

	std::ofstream file(file_path);
	file << pgn.str();
}