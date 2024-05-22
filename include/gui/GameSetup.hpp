#ifndef GAME_SETUP_HPP
#define GAME_SETUP_HPP

#include <SFML/Graphics.hpp>
#include <functional>

enum class player_type
{
	HUMAN,
	COMPUTER
};

class Player;
class GameBoard;

class game_setup
{
private:
	player_type white_player, black_player;
	int depth;

	sf::RectangleShape game_setup_rect;
	sf::Font font;

	sf::CircleShape white_human, white_computer, black_human, black_computer;
	sf::Text white_text, black_text, depth_text,
		white_human_text, white_computer_text, black_human_text, black_computer_text, depth_entered_text,
		setup_text, cancel_text;
	sf::RectangleShape depth_field_rect;
	sf::VertexArray depth_increment, depth_decrement;

	std::function<void(const player_type &, const player_type &, const int)> setup_game;
	std::function<void()> cancel_game;

public:
	game_setup(std::function<void(const player_type &, const player_type &, const int)> setup_game, std::function<void()> cancel_game);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void draw(sf::RenderWindow &window);

	bool is_AI_player(Player *player) const;
	player_type get_white_player_type() const;
	player_type get_black_player_type() const;
	int get_search_depth() const;
};

#endif