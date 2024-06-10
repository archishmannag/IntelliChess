#ifndef GAME_SETUP_HPP
#define GAME_SETUP_HPP

#include <PreCompiledHeaders.hpp>

#include <SFML/Graphics.hpp>

enum class player_type
{
	human,
	computer
};

std::string to_string(player_type player);

class player;
class game_board;

class game_setup
{
private:
	player_type white_player_ = player_type::human,
				black_player_ = player_type::human;
	unsigned int depth_;

	sf::RectangleShape game_setup_rect_;
	sf::Font font_;

	sf::CircleShape white_human_, white_computer_, black_human_, black_computer_;
	sf::Text white_text_, black_text_, depth_text_,
		white_human_text_, white_computer_text_, black_human_text_, black_computer_text_, depth_entered_text_,
		setup_text_, cancel_text_;
	sf::RectangleShape depth_field_rect_;
	sf::VertexArray depth_increment_, depth_decrement_;

	bool is_white_player_AI_ = false, is_black_player_AI_ = false;
	std::function<void()> notify_parent_;

public:
	game_setup(std::function<void()> notify_parent);
	void update(sf::Event event, sf::Vector2i mouse_position);
	void draw(sf::RenderWindow &window);

	bool is_AI_player(player *p) const;
	player_type get_white_player_type() const;
	player_type get_black_player_type() const;
	unsigned int get_search_depth() const;
};

#endif