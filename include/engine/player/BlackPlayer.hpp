/**
 * @file BlackPlayer.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief
 * @version 1.1.0
 *
 */
#ifndef BLACK_PLAYER_HPP
#define BLACK_PLAYER_HPP

#include "Player.hpp"

/**
 * @brief Derived from player class, it represents the black player
 *
 * @details It determines the castles and the active pieces of the black player. This is an immutable class.
 *
 */
class black_player final : public player
{
public:
    /**
     * @brief Construct a new black player
     *
     * @param b The board
     * @param wslm The white player's standard legal moves
     * @param bslm The black player's standard legal moves
     */
    black_player(std::shared_ptr<board> b, std::vector<std::shared_ptr<move> > wslm, std::vector<std::shared_ptr<move> > bslm);
    std::vector<std::shared_ptr<piece> > get_active_pieces() const override;
    alliance get_player_alliance() const override;
    std::weak_ptr<player> get_opponent() const override;
    std::string stringify() const override;

private:
    /**
     * @param ol The opponent's legal moves
     * @return Castle moves (if any)
     */
    std::vector<std::shared_ptr<move> > calculate_king_castles(const std::vector<std::shared_ptr<move> > &ol) const override;
};

#endif // BLACK_PLAYER_HPP