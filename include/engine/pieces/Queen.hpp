/**
 * @file Queen.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the queen class
 * @version 1.1.0
 *
 */

#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Piece.hpp"

/**
 * @brief The queen class, used for move generation and legality checking of queen pieces
 *
 */
class queen final : public piece
{
public:
    /**
     * @brief Construct a new queen
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param fm The piece's first move flag
     */
    queen(const int pp, const alliance pa, const bool fm = true);

    std::vector<std::shared_ptr<move> > calculate_legal_moves(std::shared_ptr<board> b) override;
    std::shared_ptr<piece> move_piece(const move *const m) const override;

private:
    static bool is_first_column_error(const int cp, const int co);
    static bool is_eighth_column_error(const int cp, const int co);

private:
    static const int candidate_move_vector_coordinates[]; ///< The candidate move vector coordinates
};

#endif // QUEEN_HPP