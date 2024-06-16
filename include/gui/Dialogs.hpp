#ifndef DIALOGS_HPP
#define DIALOGS_HPP

#include <PreCompiledHeaders.hpp>
#include <SFML/Graphics.hpp>

class dialog
{
public:
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void event_handler(sf::Event &event) = 0;
	void set_active(bool active);
	bool is_active() const;
	void set_heading_text(std::string text);
	void set_dialog_text(std::string text);

protected:
	sf::RectangleShape dialog_box_,
		heading_box_;
	sf::Text heading_text_,
		dialog_text_;
	sf::Font font_;
	bool is_active_ = false;

protected:
	dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position);
	void update_text_positions();
};

class message_dialog final : public dialog
{
public:
	message_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void()> ok_callback = []() {});
	void draw(sf::RenderWindow &window) override;
	void event_handler(sf::Event &event) override;

private:
	sf::RectangleShape ok_button_;
	sf::Text ok_text_;
	std::function<void()> ok_callback_;
};

class input_dialog final : public dialog
{
public:
	input_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void(std::string)> ok_callback, std::function<void()> cancel_callback = []() {});
	void draw(sf::RenderWindow &window) override;
	void event_handler(sf::Event &event) override;
	void set_input_text(std::string text);

private:
	int cursor_position_ = 0;
	sf::RectangleShape ok_button_,
		cancel_button_,
		input_box_;
	sf::Text ok_text_,
		cancel_text_,
		input_text_;
	sf::Font input_text_font_;
	sf::View input_text_view_;
	sf::Clipboard clipboard_;
	std::function<void(std::string)> ok_callback_;
	std::function<void()> cancel_callback_;

private:
	void update_input_text_view();
	void update_input_text_view(sf::Vector2u window_dimensions);
};

#endif