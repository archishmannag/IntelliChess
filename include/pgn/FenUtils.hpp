#ifndef FEN_UTILS_HPP
#define FEN_UTILS_HPP

#include <PreCompiledHeaders.hpp>

class board;

namespace fen_utils
{
	std::shared_ptr<board> fen_to_board(const std::string &fen);
	std::string board_to_fen(const board &b);
} // namespace fen_utils

#endif