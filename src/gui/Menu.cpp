#include <gui/Menu.hpp>

menu_bar::menu_bar(sf::RenderWindow &window, callback_functions_t callback_functions)
	: callback_functions_(callback_functions)
{
	menu_bar_rect_.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 25));
	menu_bar_rect_.setFillColor(sf::Color(200, 200, 200, 200));
	menu_bar_rect_.setPosition(0, 0);

	if (!font_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	file_text_.setFont(font_);
	file_text_.setString("File");
	file_text_.setCharacterSize(18);
	file_text_.setFillColor(sf::Color::Black);
	file_text_.setPosition(10, 1);

	// File submenu
	{
		file_menu_rect_.setSize(sf::Vector2f(105, 101));
		file_menu_rect_.setFillColor(sf::Color(200, 200, 200));
		file_menu_rect_.setPosition(0, 25);

		load_FEN_text_.setFont(font_);
		load_FEN_text_.setString("Load FEN");
		load_FEN_text_.setCharacterSize(18);
		load_FEN_text_.setFillColor(sf::Color::Black);
		load_FEN_text_.setPosition(5, 26);

		create_FEN_text_.setFont(font_);
		create_FEN_text_.setString("Create FEN");
		create_FEN_text_.setCharacterSize(18);
		create_FEN_text_.setFillColor(sf::Color::Black);
		create_FEN_text_.setPosition(5, 51);

		save_game_text_.setFont(font_);
		save_game_text_.setString("Save Game");
		save_game_text_.setCharacterSize(18);
		save_game_text_.setFillColor(sf::Color::Black);
		save_game_text_.setPosition(5, 76);

		exit_text_.setFont(font_);
		exit_text_.setString("Exit");
		exit_text_.setCharacterSize(18);
		exit_text_.setFillColor(sf::Color::Black);
		exit_text_.setPosition(5, 101);
	}

	option_text_.setFont(font_);
	option_text_.setString("Option");
	option_text_.setCharacterSize(18);
	option_text_.setFillColor(sf::Color::Black);
	option_text_.setPosition(80, 1);

	// Option submenu
	{
		option_menu_rect_.setSize(sf::Vector2f(190, 126));
		option_menu_rect_.setFillColor(sf::Color(200, 200, 200));
		option_menu_rect_.setPosition(70, 25);

		new_game_text_.setFont(font_);
		new_game_text_.setString("New Game");
		new_game_text_.setCharacterSize(18);
		new_game_text_.setFillColor(sf::Color::Black);
		new_game_text_.setPosition(75, 26);

		undo_move_text_.setFont(font_);
		undo_move_text_.setString("Undo Move");
		undo_move_text_.setCharacterSize(18);
		undo_move_text_.setFillColor(sf::Color::Black);
		undo_move_text_.setPosition(75, 51);

		evaluate_board_text_.setFont(font_);
		evaluate_board_text_.setString("Evaluate board");
		evaluate_board_text_.setCharacterSize(18);
		evaluate_board_text_.setFillColor(sf::Color::Black);
		evaluate_board_text_.setPosition(75, 76);

		current_state_text_.setFont(font_);
		current_state_text_.setString("Current State");
		current_state_text_.setCharacterSize(18);
		current_state_text_.setFillColor(sf::Color::Black);
		current_state_text_.setPosition(75, 101);

		setup_game_text_.setFont(font_);
		setup_game_text_.setString("Setup Game");
		setup_game_text_.setCharacterSize(18);
		setup_game_text_.setFillColor(sf::Color::Black);
		setup_game_text_.setPosition(75, 126);
	}
}

void menu_bar::update_menu_bar(sf::Event event, sf::Vector2i mouse_position)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		if (file_menu_open_)
		{
			file_menu_open_ = false;
			if (load_FEN_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.load_FEN();
			else if (create_FEN_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.create_FEN();
			else if (save_game_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.save_game();
			else if (exit_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.exit();
		}
		else if (option_menu_open_)
		{
			option_menu_open_ = false;
			if (new_game_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.new_game();
			else if (undo_move_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.undo_move();
			else if (evaluate_board_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.evaluate_board();
			else if (current_state_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.current_state();
			else if (setup_game_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
				callback_functions_.setup_game();
		}
		else if (file_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			file_menu_open_ = !file_menu_open_;
			option_menu_open_ = false;
		}
		else if (option_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			option_menu_open_ = !option_menu_open_;
			file_menu_open_ = false;
		}
		else
		{
			file_menu_open_ = false;
			option_menu_open_ = false;
		}
	}
}

void menu_bar::update(sf::RenderWindow &window)
{
	menu_bar_rect_.setSize(sf::Vector2f(window.getSize().x, 25));
}

void menu_bar::draw(sf::RenderWindow &window)
{
	update(window);
	window.draw(menu_bar_rect_);
	window.draw(file_text_);
	window.draw(option_text_);
	if (file_menu_open_)
	{
		window.draw(file_menu_rect_);
		window.draw(load_FEN_text_);
		window.draw(create_FEN_text_);
		window.draw(save_game_text_);
		window.draw(exit_text_);
	}
	if (option_menu_open_)
	{
		window.draw(option_menu_rect_);
		window.draw(new_game_text_);
		window.draw(undo_move_text_);
		window.draw(evaluate_board_text_);
		window.draw(current_state_text_);
		window.draw(setup_game_text_);
	}
}