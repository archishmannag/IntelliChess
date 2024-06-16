#ifndef PGN_UTILS_HPP
#define PGN_UTILS_HPP

#include <PreCompiledHeaders.hpp>

class move;
class board;

namespace pgn_utils
{
	void save_game_to_pgn(const std::string &file_path, const std::vector<std::shared_ptr<move>> &moves, const board &b);
} // namespace pgn_utils

#endif