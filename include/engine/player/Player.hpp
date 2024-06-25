/**
 * @file Player.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the player class
 * @version
 *
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PreCompiledHeaders.hpp"

#include "../Alliance.hpp"

// Forward declarations
class board;
class move;
class king;
class move_transition;
class piece;

/**
 * @brief A polymorphic class representing a player
 *
 */
class player
{
public: // Ctor and getters
    player(std::shared_ptr<board> b);
    bool is_move_legal(const move *m) const;
    std::shared_ptr<king> get_player_king() const;
    const std::vector<std::shared_ptr<move>> &get_legal_moves() const;
    bool is_in_check() const;
    bool is_is_checkmate() const;
    bool is_in_stalemate() const;
    bool is_castled() const;
    bool is_castle_capable() const;
    bool is_king_side_castle_capable() const;
    bool is_queen_side_castle_capable() const;
    move_transition make_move(std::shared_ptr<move> m) const;
    move_transition unmake_move(std::shared_ptr<move> m) const;

public: // Virtual methods
    virtual std::vector<std::shared_ptr<piece>> get_active_pieces() const;
    virtual alliance get_player_alliance() const;
    virtual std::weak_ptr<player> get_opponent() const;
    virtual std::vector<std::shared_ptr<move>> calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const;
    virtual std::string stringify() const;

protected:
    /**
     * @param tc The tile coordinate
     * @param ol The opponent's legal moves
     * @return std::vector<std::shared_ptr<move>>
     */
    static std::vector<std::shared_ptr<move>> calculate_attacks_on_tile(const int tc, std::vector<std::shared_ptr<move>> ol);
    std::shared_ptr<king> establish_king();
    bool has_escape_coves() const;
    bool fifty_move_rule() const;

protected:
    bool checked_;                                   ///< Is the player in check
    std::weak_ptr<board> board_;                     ///< The board
    std::shared_ptr<king> player_king_;              ///< The player's king
    std::vector<std::shared_ptr<move>> legal_moves_; ///< The player's legal moves
};

#endif // PLAYER_HPP