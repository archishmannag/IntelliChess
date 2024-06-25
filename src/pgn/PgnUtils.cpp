/**
 * @file PgnUtils.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of the PGN utilities
 * @version 1.0.0
 *
 */

#include "pgn/PgnUtils.hpp"
#include "pgn/FenUtils.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/Move.hpp"
#include "engine/player/Player.hpp"
#include "engine/Alliance.hpp"

/**
 * @brief Helper functions to calculate the PGN strings
 *
 */
namespace
{
    std::string calculate_event_string()
    {
        return "[Event \"IntelliChess\"]";
    }

    std::string calculate_date_string()
    {
        std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Convert to tm struct to extract the individual components (day, month, year, etc.)
        std::tm *time_struct = std::localtime(&current_time);

        // Stream the required components in the required format
        std::ostringstream oss;
        oss << "[Date \"" << std::put_time(time_struct, "%Y.%m.%d") << "\"]";
        return oss.str();
    }

    std::string calculate_ply_string(std::size_t size)
    {
        return "[PlyCount \"" + std::to_string(size) + "\"]";
    }

    std::string calculate_result_string(const board &b)
    {
        std::string result = "[Result \"";
        if (b.get_current_player()->is_is_checkmate())
        {
            if (b.get_current_player()->get_player_alliance() == alliance::white)
                result += "1-0";
            else
                result += "0-1";
        }
        else if (b.get_current_player()->is_in_stalemate())
            result += "1/2-1/2";
        else
            result += "*";
        result += "\"]";
        return result;
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
        << "[FEN \"" << fen_utils::board_to_fen(b) << "\"]" << "\n\n";

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