#ifndef PAWN_STRUCTURE_ANALYZER_HPP
#define PAWN_STRUCTURE_ANALYZER_HPP

#include <PreCompiledHeaders.hpp>

class piece;
class player;

class pawn_structure_analyzer
{
private:
	static const int isolated_pawn_penalty = -10;
	static const int doubled_pawn_penalty = -10;

	static std::vector<std::shared_ptr<piece>> calculate_player_pawns(const player *p);
	static int calculate_pawn_column_stack(std::array<int, 8> pawns_on_column);
	static int calculate_isolated_pawn_penalty(std::array<int, 8> pawns_on_column);
	static std::array<int, 8> calculate_pawns_on_column(std::vector<std::shared_ptr<piece>> pawns);

public:
	static int net_isolated_pawn_penalty(const player *p);
	static int net_doubled_pawn_penalty(const player *p);
	static int pawn_structure_score(const player *p);
};

#endif