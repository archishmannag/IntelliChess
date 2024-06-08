#include <gui/GameSetup.hpp>
#include <engine/player/Player.hpp>
#include <engine/Alliance.hpp>
#include <iostream>

std::string to_string(player_type p)
{
	switch (p)
	{
	case player_type::human:
		return "Human";
	case player_type::computer:
		return "Computer";
	default:
		return "Unknown";
	}
}

game_setup::game_setup(std::function<void()> notify_parent) : notify_parent_(notify_parent)
{
	if (!font_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	game_setup_rect_.setSize(sf::Vector2f(180, 300));
	game_setup_rect_.setFillColor(sf::Color(200, 200, 200));
	game_setup_rect_.setPosition(740, 120);

	white_text_.setFont(font_);
	white_text_.setString("White");
	white_text_.setCharacterSize(18);
	white_text_.setFillColor(sf::Color::Black);
	white_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 5));

	black_text_.setFont(font_);
	black_text_.setString("Black");
	black_text_.setCharacterSize(18);
	black_text_.setFillColor(sf::Color::Black);
	black_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 95));

	depth_text_.setFont(font_);
	depth_text_.setString("Search Depth");
	depth_text_.setCharacterSize(18);
	depth_text_.setFillColor(sf::Color::Black);
	depth_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 185));

	white_human_.setRadius(10);
	white_human_.setFillColor(sf::Color(200, 200, 200, 100));
	white_human_.setOutlineColor(sf::Color::Black);
	white_human_.setOutlineThickness(1.f);
	white_human_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 35));

	white_computer_.setRadius(10);
	white_computer_.setFillColor(sf::Color::White);
	white_computer_.setOutlineColor(sf::Color::Black);
	white_computer_.setOutlineThickness(1.f);
	white_computer_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 65));

	black_human_.setRadius(10);
	black_human_.setFillColor(sf::Color(200, 200, 200, 200));
	black_human_.setOutlineColor(sf::Color::Black);
	black_human_.setOutlineThickness(1.f);
	black_human_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 125));

	black_computer_.setRadius(10);
	black_computer_.setFillColor(sf::Color::White);
	black_computer_.setOutlineColor(sf::Color::Black);
	black_computer_.setOutlineThickness(1.f);
	black_computer_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 155));

	white_human_text_.setFont(font_);
	white_human_text_.setString("Human");
	white_human_text_.setCharacterSize(18);
	white_human_text_.setFillColor(sf::Color::Black);
	white_human_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(30, 35));

	white_computer_text_.setFont(font_);
	white_computer_text_.setString("Computer");
	white_computer_text_.setCharacterSize(18);
	white_computer_text_.setFillColor(sf::Color::Black);
	white_computer_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(30, 65));

	black_human_text_.setFont(font_);
	black_human_text_.setString("Human");
	black_human_text_.setCharacterSize(18);
	black_human_text_.setFillColor(sf::Color::Black);
	black_human_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(30, 125));

	black_computer_text_.setFont(font_);
	black_computer_text_.setString("Computer");
	black_computer_text_.setCharacterSize(18);
	black_computer_text_.setFillColor(sf::Color::Black);
	black_computer_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(30, 155));

	depth_field_rect_.setSize(sf::Vector2f(150, 20));
	depth_field_rect_.setFillColor(sf::Color::White);
	depth_field_rect_.setOutlineColor(sf::Color::Black);
	depth_field_rect_.setOutlineThickness(1.f);
	depth_field_rect_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 215));

	depth_entered_text_.setFont(font_);
	depth_entered_text_.setString("6");
	depth_entered_text_.setCharacterSize(18);
	depth_entered_text_.setFillColor(sf::Color::Black);
	depth_entered_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(5, 215));

	depth_increment_.setPrimitiveType(sf::Triangles);
	depth_increment_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(157.5f, 224), sf::Color(255, 255, 255, 255)));
	depth_increment_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(177.5f, 224), sf::Color(255, 255, 255, 255)));
	depth_increment_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(167.5f, 215), sf::Color(255, 255, 255, 255)));

	depth_decrement_.setPrimitiveType(sf::Triangles);
	depth_decrement_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(157.5f, 226), sf::Color(255, 255, 255, 255)));
	depth_decrement_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(177.5f, 226), sf::Color(255, 255, 255, 255)));
	depth_decrement_.append(sf::Vertex(game_setup_rect_.getPosition() + sf::Vector2f(167.5f, 235), sf::Color(255, 255, 255, 255)));

	setup_text_.setFont(font_);
	setup_text_.setString("Setup");
	setup_text_.setCharacterSize(18);
	setup_text_.setFillColor(sf::Color::Black);
	setup_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(15, 270));

	cancel_text_.setFont(font_);
	cancel_text_.setString("Cancel");
	cancel_text_.setCharacterSize(18);
	cancel_text_.setFillColor(sf::Color::Black);
	cancel_text_.setPosition(game_setup_rect_.getPosition() + sf::Vector2f(90, 270));
}

void game_setup::update(sf::Event event, sf::Vector2i mouse_position)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (white_human_.getGlobalBounds().contains(mouse_position.x, mouse_position.y) || white_human_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			is_white_player_AI_ = false;
			white_human_.setFillColor(sf::Color(200, 200, 200, 100));
			white_computer_.setFillColor(sf::Color::White);
		}
		else if (white_computer_.getGlobalBounds().contains(mouse_position.x, mouse_position.y) || white_computer_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			is_white_player_AI_ = true;
			white_human_.setFillColor(sf::Color::White);
			white_computer_.setFillColor(sf::Color(200, 200, 200, 100));
		}
		else if (black_human_.getGlobalBounds().contains(mouse_position.x, mouse_position.y) || black_human_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			is_black_player_AI_ = false;
			black_human_.setFillColor(sf::Color(200, 200, 200, 100));
			black_computer_.setFillColor(sf::Color::White);
		}
		else if (black_computer_.getGlobalBounds().contains(mouse_position.x, mouse_position.y) || black_computer_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			is_black_player_AI_ = true;
			black_human_.setFillColor(sf::Color::White);
			black_computer_.setFillColor(sf::Color(200, 200, 200, 100));
		}
		else if (depth_increment_.getBounds().contains(mouse_position.x, mouse_position.y))
		{
			int val = std::stoi(depth_entered_text_.getString().toAnsiString());
			depth_entered_text_.setString(std::to_string(val < INT32_MAX ? val + 1 : val));
		}
		else if (depth_decrement_.getBounds().contains(mouse_position.x, mouse_position.y))
		{
			int val = std::stoi(depth_entered_text_.getString().toAnsiString());
			depth_entered_text_.setString(std::to_string(val > 0 ? val - 1 : val));
		}
		else if (setup_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			white_player_ = is_white_player_AI_ ? player_type::computer : player_type::human;
			black_player_ = is_black_player_AI_ ? player_type::computer : player_type::human;
			depth_ = std::stoi(depth_entered_text_.getString().toAnsiString());
			notify_parent_();
		}
		else if (cancel_text_.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			white_player_ = player_type::human;
			black_player_ = player_type::human;
			depth_ = 6;
			notify_parent_();
		}
	}
	else if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode >= '0' && event.text.unicode <= '9')
		{
			std::string str = depth_entered_text_.getString().toAnsiString();
			if (std::stol(str + static_cast<char>(event.text.unicode)) <= INT32_MAX)
				depth_entered_text_.setString(str + static_cast<char>(event.text.unicode));
		}
		else if (event.text.unicode == '\b')
		{
			std::string str = depth_entered_text_.getString().toAnsiString();
			if (str.size() > 0)
				depth_entered_text_.setString(str.substr(0, str.size() - 1));
		}
	}
}

void game_setup::draw(sf::RenderWindow &window)
{
	window.draw(game_setup_rect_);
	window.draw(white_text_);
	window.draw(black_text_);
	window.draw(depth_text_);
	window.draw(white_human_);
	window.draw(white_computer_);
	window.draw(black_human_);
	window.draw(black_computer_);
	window.draw(white_human_text_);
	window.draw(white_computer_text_);
	window.draw(black_human_text_);
	window.draw(black_computer_text_);
	window.draw(depth_field_rect_);
	window.draw(depth_entered_text_);
	window.draw(depth_increment_);
	window.draw(depth_decrement_);

	window.draw(setup_text_);
	window.draw(cancel_text_);
}

bool game_setup::is_AI_player(player *p) const
{
	if (p->get_player_alliance() == alliance::white)
		return get_white_player_type() == player_type::computer;
	else
		return get_black_player_type() == player_type::computer;
}

player_type game_setup::get_white_player_type() const
{
	return white_player_;
}

player_type game_setup::get_black_player_type() const
{
	return black_player_;
}

unsigned int game_setup::get_search_depth() const
{
	return depth_;
}