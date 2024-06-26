/**
 * @file Piece.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the piece class
 * @version 1.0.0
 *
 */

#ifndef PIECE_HPP
#define PIECE_HPP

#include "PreCompiledHeaders.hpp"

#include "engine/Alliance.hpp"

// Forward declarations
class move;
class board;

/**
 * @brief Enum class for the piece type
 *
 */
enum class piece_type
{
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king
};

/**
 * @brief Polymporphic class for the piece
 *
 * @details enable_shared_from_this is used for sharing pointers with the moves.
 *
 */
class piece : public std::enable_shared_from_this<piece>
{
public:
    /**
     * @brief Compare two pieces.
     *
     * @param other The other piece to compare
     * @return bool
     */
    bool operator==(const piece &other);

    virtual std::vector<std::shared_ptr<move>> calculate_legal_moves(std::shared_ptr<board> b);
    virtual std::shared_ptr<piece> move_piece(const move *const m) const;

    int get_piece_position() const;
    alliance get_piece_alliance() const;
    bool is_first_move() const;
    piece_type get_piece_type() const;

    /**
     * @brief Get the value of the piece for the minimax algorithm
     *
     * @return int
     */
    int get_piece_value() const;
    std::string stringify() const;

protected:
    /**
     * @brief Construct a new piece
     *
     * @param pp The piece position
     * @param pa The piece alliance
     * @param pt The piece type
     * @param fm The piece's first move flag
     */
    piece(const int pp, const alliance pa, const piece_type pt, bool fm);

protected:
    int piece_position_;            ///< The piece position
    const alliance piece_alliance_; ///< The piece alliance
    bool first_move_;               ///< The piece's first move flag
    const piece_type piece_type_;   ///< The piece type
};

#endif // PIECE_HPP