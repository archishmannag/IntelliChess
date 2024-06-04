#ifndef GAME_HISTORY_HPP
#define GAME_HISTORY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

class board;
class move_log;

class history_row
{
private:
	sf::Text white_move_, black_move_;
	sf::RectangleShape bottom_divider_rect_;

public:
	history_row(sf::Font &font);
	void set_position(sf::Vector2f position);
	void set_white_move(std::string move);
	void set_black_move(std::string move);
	sf::Vector2f get_position() const;
	std::string get_white_move();
	std::string get_black_move();
	void draw(sf::RenderWindow &window);
};

class game_history_block
{
private:
	sf::Vector2f mouse_offset_;
	sf::RectangleShape game_history_area_rect_, scroll_bar_rect_, divider_rect_;
	std::vector<history_row> history_rows_;
	sf::Font font;
	std::array<sf::Text, 2> player_names_;
	sf::View view;
	float scroll_percentage_top_, scroll_percentage_bottom_;
	bool scroll_bar_clicked_;

	void update(sf::RenderWindow &window);
	void update_scroll_percentage(sf::Vector2f window_size);

public:
	game_history_block();
	sf::View get_view() const;
	void mouse_wheel_scrolled(sf::Event::MouseWheelScrollEvent &event, sf::Vector2f window_size);
	void scroll_bar_scrolled(sf::Event::MouseButtonEvent &event, bool button_clicked_or_released);
	void scroll(sf::RenderWindow &window);
	void redo(board *b, move_log &ml);
	void draw(sf::RenderWindow &window);
};

#endif