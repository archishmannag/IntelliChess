#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

typedef struct callback_functions
{
	std::function<void()> load_FEN;
	std::function<void()> load_PGN;
	std::function<void()> save_game;
	std::function<void()> exit;
	std::function<void()> new_game;
	std::function<void()> undo_move;
	std::function<void()> evaluate_board;
	std::function<void()> escape_analysis_score;
	std::function<void()> current_state;
	std::function<void()> setup_game;
} callback_functions_t;

class menu_bar
{
private:
	sf::RectangleShape menu_bar_rect;
	sf::Font font;

	// Main menu text
	sf::Text file_text, option_text;

	// File menu text and rectangle
	bool file_menu_open = false;
	sf::RectangleShape file_menu_rect;
	sf::Text load_FEN_text, load_PGN_text, save_game_text, exit_text;

	// Option menu text and rectangle
	bool option_menu_open = false;
	sf::RectangleShape option_menu_rect;
	sf::Text new_game_text, undo_move_text, evaluate_board_text, escape_analysis_score_text, current_state_text, setup_game_text;

	callback_functions_t callback_functions;

	void update(sf::RenderWindow &window);

public:
	menu_bar(sf::RenderWindow &window, callback_functions_t callback_functions);
	void update_menu_bar(sf::Event event, sf::Vector2i mousePosition);
	void draw(sf::RenderWindow &window);
};

#endif