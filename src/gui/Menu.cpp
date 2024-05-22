#include <iostream>
#include <gui/Menu.hpp>

menu_bar::menu_bar(sf::RenderWindow &window, callback_functions_t callback_functions) : callback_functions(callback_functions)
{
	menu_bar_rect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 25));
	menu_bar_rect.setFillColor(sf::Color(200, 200, 200, 200));
	menu_bar_rect.setPosition(0, 0);

	if (!font.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	file_text.setFont(font);
	file_text.setString("File");
	file_text.setCharacterSize(18);
	file_text.setFillColor(sf::Color::Black);
	file_text.setPosition(10, 1);

	// File submenu
	{
		file_menu_rect.setSize(sf::Vector2f(105, 101));
		file_menu_rect.setFillColor(sf::Color(200, 200, 200));
		file_menu_rect.setPosition(0, 25);

		load_FEN_text.setFont(font);
		load_FEN_text.setString("Load FEN");
		load_FEN_text.setCharacterSize(18);
		load_FEN_text.setFillColor(sf::Color::Black);
		load_FEN_text.setPosition(5, 26);

		load_PGN_text.setFont(font);
		load_PGN_text.setString("Load PGN");
		load_PGN_text.setCharacterSize(18);
		load_PGN_text.setFillColor(sf::Color::Black);
		load_PGN_text.setPosition(5, 51);

		save_game_text.setFont(font);
		save_game_text.setString("Save Game");
		save_game_text.setCharacterSize(18);
		save_game_text.setFillColor(sf::Color::Black);
		save_game_text.setPosition(5, 76);

		exit_text.setFont(font);
		exit_text.setString("Exit");
		exit_text.setCharacterSize(18);
		exit_text.setFillColor(sf::Color::Black);
		exit_text.setPosition(5, 101);
	}

	option_text.setFont(font);
	option_text.setString("Option");
	option_text.setCharacterSize(18);
	option_text.setFillColor(sf::Color::Black);
	option_text.setPosition(80, 1);

	// Option submenu
	{
		option_menu_rect.setSize(sf::Vector2f(190, 151));
		option_menu_rect.setFillColor(sf::Color(200, 200, 200));
		option_menu_rect.setPosition(70, 25);

		new_game_text.setFont(font);
		new_game_text.setString("New Game");
		new_game_text.setCharacterSize(18);
		new_game_text.setFillColor(sf::Color::Black);
		new_game_text.setPosition(75, 26);

		undo_move_text.setFont(font);
		undo_move_text.setString("Undo Move");
		undo_move_text.setCharacterSize(18);
		undo_move_text.setFillColor(sf::Color::Black);
		undo_move_text.setPosition(75, 51);

		evaluate_board_text.setFont(font);
		evaluate_board_text.setString("Evaluate Board");
		evaluate_board_text.setCharacterSize(18);
		evaluate_board_text.setFillColor(sf::Color::Black);
		evaluate_board_text.setPosition(75, 76);

		escape_analysis_score_text.setFont(font);
		escape_analysis_score_text.setString("Escape Analysis Score");
		escape_analysis_score_text.setCharacterSize(18);
		escape_analysis_score_text.setFillColor(sf::Color::Black);
		escape_analysis_score_text.setPosition(75, 101);

		current_state_text.setFont(font);
		current_state_text.setString("Current State");
		current_state_text.setCharacterSize(18);
		current_state_text.setFillColor(sf::Color::Black);
		current_state_text.setPosition(75, 126);

		setup_game_text.setFont(font);
		setup_game_text.setString("Setup Game");
		setup_game_text.setCharacterSize(18);
		setup_game_text.setFillColor(sf::Color::Black);
		setup_game_text.setPosition(75, 151);
	}
}

void menu_bar::update_menu_bar(sf::Event event, sf::Vector2i mousePosition)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (file_menu_open)
		{
			file_menu_open = false;
			if (load_FEN_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.load_FEN();
			else if (load_PGN_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.load_PGN();
			else if (save_game_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.save_game();
			else if (exit_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.exit();
		}
		else if (option_menu_open)
		{
			option_menu_open = false;
			if (new_game_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.new_game();
			else if (undo_move_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.undo_move();
			else if (evaluate_board_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.evaluate_board();
			else if (escape_analysis_score_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.escape_analysis_score();
			else if (current_state_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.current_state();
			else if (setup_game_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				callback_functions.setup_game();
		}
		else if (file_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			file_menu_open = !file_menu_open;
			option_menu_open = false;
		}
		else if (option_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			option_menu_open = !option_menu_open;
			file_menu_open = false;
		}
		else
		{
			file_menu_open = false;
			option_menu_open = false;
		}
	}
}

void menu_bar::update(sf::RenderWindow &window)
{
	menu_bar_rect.setSize(sf::Vector2f(window.getSize().x, 25));
}

void menu_bar::draw(sf::RenderWindow &window)
{
	update(window);
	window.draw(menu_bar_rect);
	window.draw(file_text);
	window.draw(option_text);
	if (file_menu_open)
	{
		window.draw(file_menu_rect);
		window.draw(load_FEN_text);
		window.draw(load_PGN_text);
		window.draw(save_game_text);
		window.draw(exit_text);
	}
	if (option_menu_open)
	{
		window.draw(option_menu_rect);
		window.draw(new_game_text);
		window.draw(undo_move_text);
		window.draw(evaluate_board_text);
		window.draw(escape_analysis_score_text);
		window.draw(current_state_text);
		window.draw(setup_game_text);
	}
}