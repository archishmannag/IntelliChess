/**
 * @file Bishop.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the bishop class
 * @version 1.1.0
 *
 */

#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "Piece.hpp"

/**
 * @brief The bishop class, used for move generation and legality checking of bishop pieces
 *
 */
class bishop final : public piece
{
public:
    /**
     * @brief Construct a new bishop
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param fm The piece's first move flag
     */
    bishop(const int pp, const alliance pa, const bool fm = true);

    /**
     * @brief Calculate the legal moves for the bishop
     *
     * @param b The board on which the moves are to be calculated
     * @return Vector of shared pointers to the legal moves
     */
    std::vector<std::shared_ptr<move> > calculate_legal_moves(std::shared_ptr<board> b) override;
    std::shared_ptr<piece> move_piece(const move *const m) const override;

private:
    /**
     * @brief Calculate if the offset produces error in first column
     *
     * @param cp The current position
     * @param co The offset
     * @return bool
     */
    static bool is_first_column_error(const int cp, const int co);
    /**
     * @brief Calculate if the offset produces error in eighth column
     *
     * @param cp The current position
     * @param co The offset
     * @return bool
     */
    static bool is_eighth_column_error(const int cp, const int co);

private:
    const static int candidate_move_vector_coordinates[]; ///< The candidate move vector coordinates
};

#endif // BISHOP_HPP