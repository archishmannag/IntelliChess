/**
 * @file Pawn.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the pawn class
 * @version 1.0.0
 *
 */

#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

/**
 * @brief The pawn class, used for move generation and legality checking of pawn pieces
 *
 */
class pawn final : public piece
{
public:
    /**
     * @brief Construct a new pawn
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param fm The piece's first move flag
     */
    pawn(const int pp, const alliance pa, const bool fm = true);

    std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
    std::shared_ptr<piece> move_piece(const move *const m) const override;

private:
    static const int candidate_move_coordinates[]; ///< The candidate move coordinates
};

#endif // PAWN_HPP