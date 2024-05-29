#include <gui/GameSetup.hpp>
#include <engine/player/Player.hpp>
#include <engine/Alliance.hpp>

std::string to_string(player_type player)
{
	switch (player)
	{
	case player_type::HUMAN:
		return "Human";
	case player_type::COMPUTER:
		return "Computer";
	default:
		return "Unknown";
	}
}

game_setup::game_setup(std::function<void()> notify_parent) : notify_parent(notify_parent)
{
	if (!font.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	game_setup_rect.setSize(sf::Vector2f(180, 300));
	game_setup_rect.setFillColor(sf::Color(200, 200, 200));
	game_setup_rect.setPosition(740, 120);

	white_text.setFont(font);
	white_text.setString("White");
	white_text.setCharacterSize(18);
	white_text.setFillColor(sf::Color::Black);
	white_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 5));

	black_text.setFont(font);
	black_text.setString("Black");
	black_text.setCharacterSize(18);
	black_text.setFillColor(sf::Color::Black);
	black_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 95));

	depth_text.setFont(font);
	depth_text.setString("Difficulty");
	depth_text.setCharacterSize(18);
	depth_text.setFillColor(sf::Color::Black);
	depth_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 185));

	white_human.setRadius(10);
	white_human.setFillColor(sf::Color(200, 200, 200, 100));
	white_human.setOutlineColor(sf::Color::Black);
	white_human.setOutlineThickness(1.f);
	white_human.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 35));

	white_computer.setRadius(10);
	white_computer.setFillColor(sf::Color::White);
	white_computer.setOutlineColor(sf::Color::Black);
	white_computer.setOutlineThickness(1.f);
	white_computer.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 65));

	black_human.setRadius(10);
	black_human.setFillColor(sf::Color(200, 200, 200, 200));
	black_human.setOutlineColor(sf::Color::Black);
	black_human.setOutlineThickness(1.f);
	black_human.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 125));

	black_computer.setRadius(10);
	black_computer.setFillColor(sf::Color::White);
	black_computer.setOutlineColor(sf::Color::Black);
	black_computer.setOutlineThickness(1.f);
	black_computer.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 155));

	white_human_text.setFont(font);
	white_human_text.setString("Human");
	white_human_text.setCharacterSize(18);
	white_human_text.setFillColor(sf::Color::Black);
	white_human_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(30, 35));

	white_computer_text.setFont(font);
	white_computer_text.setString("Computer");
	white_computer_text.setCharacterSize(18);
	white_computer_text.setFillColor(sf::Color::Black);
	white_computer_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(30, 65));

	black_human_text.setFont(font);
	black_human_text.setString("Human");
	black_human_text.setCharacterSize(18);
	black_human_text.setFillColor(sf::Color::Black);
	black_human_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(30, 125));

	black_computer_text.setFont(font);
	black_computer_text.setString("Computer");
	black_computer_text.setCharacterSize(18);
	black_computer_text.setFillColor(sf::Color::Black);
	black_computer_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(30, 155));

	depth_field_rect.setSize(sf::Vector2f(150, 20));
	depth_field_rect.setFillColor(sf::Color::White);
	depth_field_rect.setOutlineColor(sf::Color::Black);
	depth_field_rect.setOutlineThickness(1.f);
	depth_field_rect.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 215));

	depth_entered_text.setFont(font);
	depth_entered_text.setString("6");
	depth_entered_text.setCharacterSize(18);
	depth_entered_text.setFillColor(sf::Color::Black);
	depth_entered_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(5, 215));

	depth_increment.setPrimitiveType(sf::Triangles);
	depth_increment.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(157.5f, 224), sf::Color(255, 255, 255, 255)));
	depth_increment.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(177.5f, 224), sf::Color(255, 255, 255, 255)));
	depth_increment.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(167.5f, 215), sf::Color(255, 255, 255, 255)));

	depth_decrement.setPrimitiveType(sf::Triangles);
	depth_decrement.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(157.5f, 226), sf::Color(255, 255, 255, 255)));
	depth_decrement.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(177.5f, 226), sf::Color(255, 255, 255, 255)));
	depth_decrement.append(sf::Vertex(game_setup_rect.getPosition() + sf::Vector2f(167.5f, 235), sf::Color(255, 255, 255, 255)));

	setup_text.setFont(font);
	setup_text.setString("Setup");
	setup_text.setCharacterSize(18);
	setup_text.setFillColor(sf::Color::Black);
	setup_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(15, 270));

	cancel_text.setFont(font);
	cancel_text.setString("Cancel");
	cancel_text.setCharacterSize(18);
	cancel_text.setFillColor(sf::Color::Black);
	cancel_text.setPosition(game_setup_rect.getPosition() + sf::Vector2f(90, 270));
}

void game_setup::update(sf::Event event, sf::Vector2i mousePosition)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (white_human.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || white_human_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			white_human.setFillColor(sf::Color(200, 200, 200, 100));
			white_computer.setFillColor(sf::Color::White);
		}
		else if (white_computer.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || white_computer_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			white_human.setFillColor(sf::Color::White);
			white_computer.setFillColor(sf::Color(200, 200, 200, 100));
		}
		else if (black_human.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || black_human_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			black_human.setFillColor(sf::Color(200, 200, 200, 100));
			black_computer.setFillColor(sf::Color::White);
		}
		else if (black_computer.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || black_computer_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			black_human.setFillColor(sf::Color::White);
			black_computer.setFillColor(sf::Color(200, 200, 200, 100));
		}
		else if (depth_increment.getBounds().contains(mousePosition.x, mousePosition.y))
		{
			int val = std::stoi(depth_entered_text.getString().toAnsiString());
			depth_entered_text.setString(std::to_string(val < INT32_MAX ? val + 1 : val));
		}
		else if (depth_decrement.getBounds().contains(mousePosition.x, mousePosition.y))
		{
			int val = std::stoi(depth_entered_text.getString().toAnsiString());
			depth_entered_text.setString(std::to_string(val > 0 ? val - 1 : val));
		}
		else if (setup_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			white_player = white_human.getFillColor() == sf::Color(200, 200, 200, 100) ? player_type::HUMAN : player_type::COMPUTER;
			black_player = black_human.getFillColor() == sf::Color(200, 200, 200, 100) ? player_type::HUMAN : player_type::COMPUTER;
			depth = std::stoi(depth_entered_text.getString().toAnsiString());
			notify_parent();
		}
		else if (cancel_text.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			white_player = player_type::HUMAN;
			black_player = player_type::HUMAN;
			depth = 6;
			notify_parent();
		}
	}
	else if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode >= '0' && event.text.unicode <= '9')
		{
			std::string str = depth_entered_text.getString().toAnsiString();
			if (std::stol(str + static_cast<char>(event.text.unicode)) <= INT32_MAX)
				depth_entered_text.setString(str + static_cast<char>(event.text.unicode));
		}
		else if (event.text.unicode == '\b')
		{
			std::string str = depth_entered_text.getString().toAnsiString();
			if (str.size() > 0)
				depth_entered_text.setString(str.substr(0, str.size() - 1));
		}
	}
}

void game_setup::draw(sf::RenderWindow &window)
{
	window.draw(game_setup_rect);
	window.draw(white_text);
	window.draw(black_text);
	window.draw(depth_text);
	window.draw(white_human);
	window.draw(white_computer);
	window.draw(black_human);
	window.draw(black_computer);
	window.draw(white_human_text);
	window.draw(white_computer_text);
	window.draw(black_human_text);
	window.draw(black_computer_text);
	window.draw(depth_field_rect);
	window.draw(depth_entered_text);
	window.draw(depth_increment);
	window.draw(depth_decrement);

	window.draw(setup_text);
	window.draw(cancel_text);
}

bool game_setup::is_AI_player(Player *player) const
{
	if (player->getPlayerAlliance() == Alliance::WHITE)
		return get_white_player_type() == player_type::COMPUTER;
	else
		return get_black_player_type() == player_type::COMPUTER;
}

player_type game_setup::get_white_player_type() const
{
	return white_player;
}

player_type game_setup::get_black_player_type() const
{
	return black_player;
}

unsigned int game_setup::get_search_depth() const
{
	return depth;
}