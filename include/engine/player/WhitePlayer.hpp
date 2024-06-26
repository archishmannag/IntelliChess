/**
 * @file WhitePlayer.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the white player class
 * @version 1.0.0
 *
 */

#ifndef WHITE_PLAYER_HPP
#define WHITE_PLAYER_HPP

#include "Player.hpp"

/**
 * @brief Derived from player class, it represents the white player
 *
 */
class white_player final : public player
{
public:
    /**
     * @brief Construct a new white player
     *
     * @param b The board
     * @param wslm The white player's standard legal moves
     * @param bslm The black player's standard legal moves
     */
    white_player(std::shared_ptr<board> b, std::vector<std::shared_ptr<move>> wslm, std::vector<std::shared_ptr<move>> bslm);
    std::vector<std::shared_ptr<piece>> get_active_pieces() const override;
    alliance get_player_alliance() const override;
    std::weak_ptr<player> get_opponent() const override;
    std::string stringify() const override;

private:
    /**
     * @param ol The opponent's legal moves
     * @return Castle moves (if any)
     */
    std::vector<std::shared_ptr<move>> calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const override;
};

#endif // WHITE_PLAYER_HPP