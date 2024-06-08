#include <iterator>
#include <algorithm>

#include <engine/player/ai/PawnStructureAnalyzer.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/player/Player.hpp>

int pawn_structure_analyzer::pawn_structure_score(const player *p)
{
	std::array<int, 8> pawns_on_column = calculate_pawns_on_column(calculate_player_pawns(p));
	return calculate_pawn_column_stack(pawns_on_column) + calculate_isolated_pawn_penalty(pawns_on_column);
}

int pawn_structure_analyzer::net_isolated_pawn_penalty(const player *p)
{
	return calculate_isolated_pawn_penalty(calculate_pawns_on_column(calculate_player_pawns(p)));
}

int pawn_structure_analyzer::net_doubled_pawn_penalty(const player *p)
{
	return calculate_pawn_column_stack(calculate_pawns_on_column(calculate_player_pawns(p)));
}

std::vector<std::shared_ptr<piece>> pawn_structure_analyzer::calculate_player_pawns(const player *p)
{
	std::vector<std::shared_ptr<piece>> pawns,
		pieces = p->get_active_pieces();
	std::copy_if(pieces.begin(), pieces.end(), std::back_inserter(pawns), [](std::shared_ptr<piece> Piece)
				 { return Piece->get_piece_type() == piece_type::pawn; });
	return pawns;
}

int pawn_structure_analyzer::calculate_pawn_column_stack(std::array<int, 8> pawns_on_column)
{
	int pawn_stack_penalty = 0;
	for (const int pawn_stack : pawns_on_column)
		if (pawn_stack > 1)
			pawn_stack_penalty += pawn_stack;
	return pawn_stack_penalty * doubled_pawn_penalty;
}

int pawn_structure_analyzer::calculate_isolated_pawn_penalty(std::array<int, 8> pawns_on_column)
{
	int isolated_pawn_number = 0;
	if (pawns_on_column[0] > 0 && pawns_on_column[1] == 0)
		isolated_pawn_number += pawns_on_column[0];
	if (pawns_on_column[7] > 0 && pawns_on_column[6] == 0)
		isolated_pawn_number += pawns_on_column[7];
	for (std::size_t i = 1; i < pawns_on_column.size() - 1; i++)
		if (pawns_on_column[i - 1] == 0 && pawns_on_column[i + 1] == 0)
			isolated_pawn_number += pawns_on_column[i];
	return isolated_pawn_number * isolated_pawn_penalty;
}

std::array<int, 8> pawn_structure_analyzer::calculate_pawns_on_column(std::vector<std::shared_ptr<piece>> pawns)
{
	std::array<int, 8> pawns_om_column{};
	for (std::shared_ptr<piece> p : pawns)
		pawns_om_column[p->get_piece_position() % 8]++;
	return pawns_om_column;
}