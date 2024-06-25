/**
 * @file King.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the king class
 * @version 1.0.0
 *
 */
#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

/**
 * @brief The king class, used for move generation and legality checking of king pieces
 *
 */
class king final : public piece
{
public:
    /**
     * @brief Construct a new king
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param fm The piece's first move flag
     * @param c The piece's castled flag
     * @param ksc The piece's king side castle flag
     * @param qsc The piece's queen side castle flag
     */
    king(const int pp, const alliance pa, const bool fm = true, const bool c = false, const bool ksc = true, const bool qsc = true);

    /**
     * @brief Calculate the legal moves for the king
     *
     * @param b The board on which the moves are to be calculated
     * @return Vector of shared pointers to the legal moves
     */
    std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b) override;
    std::shared_ptr<piece> move_piece(const move *const m) const override;
    void set_king_side_castle_capability(const bool ksc);
    void set_queen_side_castle_capability(const bool qsc);
    bool is_castled() const;
    bool is_king_side_castle_capable() const;
    bool is_queen_side_castle_capable() const;

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
    bool castled_,                  ///< The castled flag
        king_side_castle_capable_,  ///< The king side castle flag
        queen_side_castle_capable_; ///< The queen side castle flag

    static const int candidate_move_coordinates[]; ///< The candidate move coordinates
};

#endif // KING_HPP