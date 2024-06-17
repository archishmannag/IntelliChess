#include <gui/Dialogs.hpp>
#include <gui/GuiUtils.hpp>

dialog::dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position)
{
	if (!font_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/arial.ttf"))
		throw std::runtime_error("Failed to load font!");

	heading_text_.setFont(font_);
	heading_text_.setString(heading_text);
	heading_text_.setCharacterSize(18);
	heading_text_.setFillColor(sf::Color::White);
	heading_text_.setPosition(sf::Vector2f(200 - heading_text.size() / 2 * heading_text_.getCharacterSize() / 2, 3.5f) + position);

	dialog_text_.setFont(font_);
	dialog_text_.setString(dialog_text);
	dialog_text_.setCharacterSize(18);
	dialog_text_.setFillColor(sf::Color::Black);
	dialog_text_.setPosition(sf::Vector2f(8, 35) + position);
	for (std::size_t i = 0; i < dialog_text.size(); i++)
		if (i % 40 == 0 && i)
			dialog_text_.setString(dialog_text_.getString().toAnsiString().insert(i, "\n"));

	heading_box_.setSize(sf::Vector2f(400, 30));
	heading_box_.setFillColor(sf::Color::Black);
	heading_box_.setPosition(sf::Vector2f(0, 0) + position);

	dialog_box_.setSize(sf::Vector2f(400, 120));
	dialog_box_.setFillColor(sf::Color(238, 238, 238));
	dialog_box_.setPosition(sf::Vector2f(0, 30) + position);
}

void dialog::set_active(bool active)
{
	is_active_ = active;
}

bool dialog::is_active() const
{
	return is_active_;
}

void dialog::set_heading_text(std::string text)
{
	heading_text_.setString(text);
	update_text_positions();
}

void dialog::set_dialog_text(std::string text)
{
	dialog_text_.setString(text);
	update_text_positions();
}

void dialog::update_text_positions()
{
	heading_text_.setPosition(sf::Vector2f(200 - heading_text_.getString().getSize() / 2 * heading_text_.getCharacterSize() / 2, 3.5f) + heading_box_.getPosition());
	dialog_text_.setPosition(sf::Vector2f(8, 35) + heading_box_.getPosition());
	for (std::size_t i = 0; i < dialog_text_.getString().getSize(); i++)
		if (i % 40 == 0 && i)
			dialog_text_.setString(dialog_text_.getString().toAnsiString().insert(i, "\n"));
}

message_dialog::message_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void()> ok_callback)
	: dialog(heading_text, dialog_text, position),
	  ok_callback_(ok_callback)
{
	ok_button_.setSize(sf::Vector2f(100, 30));
	ok_button_.setFillColor(sf::Color(208, 224, 239));
	ok_button_.setPosition(sf::Vector2f(150, 90) + position);

	ok_text_.setFont(font_);
	ok_text_.setString("OK");
	ok_text_.setCharacterSize(16);
	ok_text_.setFillColor(sf::Color::Black);
	ok_text_.setPosition(sf::Vector2f(188, 95) + position);
}

void message_dialog::draw(sf::RenderWindow &window)
{
	window.draw(heading_box_);
	window.draw(heading_text_);
	window.draw(dialog_box_);
	window.draw(dialog_text_);
	window.draw(ok_button_);
	window.draw(ok_text_);
}

void message_dialog::event_handler(sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (ok_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				// Close the dialog
				set_active(false);
				ok_callback_();
			}
		}
	}
}

input_dialog::input_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void(std::string)> ok_callback, std::function<void()> cancel_callback)
	: dialog(heading_text, dialog_text, position),
	  ok_callback_(ok_callback),
	  cancel_callback_(cancel_callback)
{
	if (!input_text_font_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/fonts/CCNFM.ttf"))
		throw std::runtime_error("Failed to load font!");

	ok_button_.setSize(sf::Vector2f(100, 30));
	ok_button_.setFillColor(sf::Color(208, 224, 239));
	ok_button_.setPosition(sf::Vector2f(80, 110) + position);

	ok_text_.setFont(font_);
	ok_text_.setString("OK");
	ok_text_.setCharacterSize(16);
	ok_text_.setFillColor(sf::Color::Black);
	ok_text_.setPosition(sf::Vector2f(118, 115) + position);

	cancel_button_.setSize(sf::Vector2f(100, 30));
	cancel_button_.setFillColor(sf::Color(208, 224, 239));
	cancel_button_.setPosition(sf::Vector2f(220, 110) + position);

	cancel_text_.setFont(font_);
	cancel_text_.setString("Cancel");
	cancel_text_.setCharacterSize(16);
	cancel_text_.setFillColor(sf::Color::Black);
	cancel_text_.setPosition(sf::Vector2f(246, 115) + position);

	input_box_.setSize(sf::Vector2f(340, 40));
	input_box_.setFillColor(sf::Color::White);
	input_box_.setPosition(sf::Vector2f(30, 60) + position);

	input_text_.setFont(input_text_font_);
	input_text_.setString("_");
	input_text_.setCharacterSize(16);
	input_text_.setFillColor(sf::Color::Black);
	input_text_.setPosition(sf::Vector2f(35, 70) + position);

	input_text_view_.reset(sf::FloatRect(input_box_.getPosition(), input_box_.getSize()));
	input_text_view_.setViewport(sf::FloatRect(sf::Vector2f(input_box_.getPosition().x / window_width, input_box_.getPosition().y / window_height), sf::Vector2f(input_box_.getSize().x / window_width, input_box_.getSize().y / window_height)));
}

void input_dialog::draw(sf::RenderWindow &window)
{
	window.draw(heading_box_);
	window.draw(heading_text_);
	window.draw(dialog_box_);
	window.draw(dialog_text_);
	window.draw(ok_button_);
	window.draw(ok_text_);
	window.draw(cancel_button_);
	window.draw(cancel_text_);
	window.draw(input_box_);
	// Draw the input text in a separate view to allow for text input to exceed the input box width
	{
		update_input_text_view(window.getSize());
		auto current_view = window.getView();
		window.setView(input_text_view_);
		window.draw(input_text_);
		window.setView(current_view);
	}
}

void input_dialog::event_handler(sf::Event &event)
{
	std::string input_string, input_string_left, input_string_right;

	input_string_left = input_text_.getString().substring(0, cursor_position_);
	if (cursor_position_ < static_cast<int>(input_text_.getString().getSize()) - 1)
		input_string_right = input_text_.getString().substring(cursor_position_ + 1);
	input_string = input_string_left + input_string_right;

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (ok_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				// Close the dialog and return the input text
				set_active(false);
				ok_callback_(input_text_.getString().toAnsiString().erase(cursor_position_, 1));
			}
			else if (cancel_button_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				// Close the dialog
				set_active(false);
				cancel_callback_();
			}
		}
	}
	else if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == 8 /* BackSpace */)
		{
			if (input_string_left.size() > 0)
			{
				input_string_left.erase(input_string_left.size() - 1);
				cursor_position_--;
			}
		}
		else if (event.text.unicode == 127 /* Delete */)
		{
			if (input_string_right.size() > 0)
				input_string_right.erase(0, 1);
		}
		else if (event.text.unicode >= 32 /* ' ' */ && event.text.unicode <= 126 /* '~' */)
		{
			input_string_left += static_cast<char>(event.text.unicode);
			cursor_position_++;
		}
		input_string = input_string_left + input_string_right;
		input_string.insert(cursor_position_, "_");
		input_text_.setString(input_string);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			if (cursor_position_ > 0)
				cursor_position_--;
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			if (cursor_position_ < static_cast<int>(input_text_.getString().getSize()) - 1)
				cursor_position_++;
		}
		else if (event.key.control && event.key.code == sf::Keyboard::V /* Ctrl+V */)
		{
			std::string clipboard_string = clipboard_.getString();
			if (clipboard_string.size() > 0)
			{
				input_string_left += clipboard_string;
				cursor_position_ += static_cast<int>(clipboard_string.size());
			}
		}
		input_string = input_string_left + input_string_right;
		input_string.insert(cursor_position_, "_");
		input_text_.setString(input_string);
	}
	update_input_text_view();
}

void input_dialog::set_input_text(std::string text)
{
	input_text_.setString(text + "_");
	cursor_position_ = static_cast<int>(text.size());
}

void input_dialog::update_input_text_view()
{
	// Update the view's centre to display the cursor.
	sf::Vector2f cursor_display_location = input_text_.findCharacterPos(cursor_position_);
	if (cursor_display_location.x < input_box_.getPosition().x + 4)
		while (cursor_display_location.x < input_box_.getPosition().x + 4)
			input_text_view_.move(-8, 0);
	else if (cursor_display_location.x > input_box_.getPosition().x + input_box_.getSize().x - 4)
		while (cursor_display_location.x > input_box_.getPosition().x + input_box_.getSize().x - 4)
			input_text_view_.move(8, 0);
}

void input_dialog::update_input_text_view(sf::Vector2u window_dimensions)
{
	// Update the view's viewport to display the text corectly.
	input_text_view_.setViewport(sf::FloatRect(sf::Vector2f(input_box_.getPosition().x / window_dimensions.x, input_box_.getPosition().y / window_dimensions.y), sf::Vector2f(input_box_.getSize().x / window_dimensions.x, input_box_.getSize().y / window_dimensions.y)));
}