/**
 * @file Knight.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the knight class
 * @version 1.1.0
 *
 */

#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Piece.hpp"

/**
 * @brief The knight class, used for move generation and legality checking of knight pieces
 *
 */
class knight final : public piece
{
public:
    /**
     * @brief Construct a new knight
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param fm The piece's first move flag
     */
    knight(const int pp, const alliance pa, const bool fm = true);

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
    static bool is_second_column_error(const int cp, const int co);
    static bool is_seventh_column_error(const int cp, const int co);
    static bool is_eighth_column_error(const int cp, const int co);

private:
    static const int candidate_move_coordinates[]; ///< The candidate move coordinates
};

#endif // KNIGHT_HPP