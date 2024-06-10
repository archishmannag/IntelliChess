#ifndef WHITEPLAYER_HPP
#define WHITEPLAYER_HPP

#include "Player.hpp"

class white_player : public player
{
public:
	white_player(std::shared_ptr<board> b, std::vector<std::shared_ptr<move>> wslm, std::vector<std::shared_ptr<move>> bslm);
	std::vector<std::shared_ptr<piece>> get_active_pieces() const override;
	alliance get_player_alliance() const override;
	std::weak_ptr<player> get_opponent() const override;
	std::vector<std::shared_ptr<move>> calculate_king_castles(const std::vector<std::shared_ptr<move>> &ol) const override;
	std::string stringify() const override;
};

#endif