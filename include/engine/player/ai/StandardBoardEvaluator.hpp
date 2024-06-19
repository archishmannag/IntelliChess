#ifndef STANDARD_BOARD_EVALUATOR_HPP
#define STANDARD_BOARD_EVALUATOR_HPP

#include <PreCompiledHeaders.hpp>

class board;
class player;

namespace standard_board_evaluator
{
	int evaluate(const board &b, int d);
	std::string evaluation_details(const board &b, const int d);
} // namespace standard_board_evaluator

#endif // STANDARD_BOARD_EVALUATOR_HPP