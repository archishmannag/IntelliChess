/**
 * @file PawnStructureAnalyzer.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the pawn structure analyzer class
 * @version 1.0.0
 *
 */

#ifndef PAWN_STRUCTURE_ANALYZER_HPP
#define PAWN_STRUCTURE_ANALYZER_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class piece;
class player;

/**
 * @brief A static class for analyzing the pawn structure
 *
 * @todo Convert this class to a namespace
 *
 */
class pawn_structure_analyzer
{
public:
    static int net_isolated_pawn_penalty(const player *p);
    static int net_doubled_pawn_penalty(const player *p);
    static int pawn_structure_score(const player *p);

private:
    static std::vector<std::shared_ptr<piece>> calculate_player_pawns(const player *p);
    static int calculate_pawn_column_stack_penalty(std::array<int, 8> pawns_on_column);
    static int calculate_isolated_pawn_penalty(std::array<int, 8> pawns_on_column);
    static std::array<int, 8> calculate_pawns_on_column(std::vector<std::shared_ptr<piece>> pawns);

private:
    static const int isolated_pawn_penalty = -10;
    static const int doubled_pawn_penalty = -10;
};

#endif // PAWN_STRUCTURE_ANALYZER_HPP