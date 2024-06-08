#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

typedef struct callback_functions
{
	std::function<void()> load_FEN, load_PGN, save_game, exit,
		new_game, undo_move, evaluate_board, current_state, setup_game;
} callback_functions_t;

class menu_bar
{
private:
	sf::RectangleShape menu_bar_rect_;
	sf::Font font_;

	// Main menu text
	sf::Text file_text_, option_text_;

	// File menu text and rectangle
	bool file_menu_open_ = false;
	sf::RectangleShape file_menu_rect_;
	sf::Text load_FEN_text_, load_PGN_text_, save_game_text_, exit_text_;

	// Option menu text and rectangle
	bool option_menu_open_ = false;
	sf::RectangleShape option_menu_rect_;
	sf::Text new_game_text_, undo_move_text_, evaluate_board_text_, current_state_text_, setup_game_text_;

	callback_functions_t callback_functions_;

	void update(sf::RenderWindow &window);

public:
	menu_bar(sf::RenderWindow &window, callback_functions_t callback_functions);
	void update_menu_bar(sf::Event event, sf::Vector2i mouse_position);
	void draw(sf::RenderWindow &window);
};

#endif