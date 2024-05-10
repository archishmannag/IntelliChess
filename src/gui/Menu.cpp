#include <iostream>
#include "../../include/gui/Menu.hpp"

MenuBar::MenuBar(sf::RenderWindow &window)
{
	this->menuBar.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 25));
	this->menuBar.setFillColor(sf::Color(200, 200, 200, 200));
	this->menuBar.setPosition(0, 0);

	this->font.loadFromFile("../resources/fonts/arial.ttf");

	this->fileText.setFont(this->font);
	this->fileText.setString("File");
	this->fileText.setCharacterSize(20);
	this->fileText.setFillColor(sf::Color::Black);
	this->fileText.setPosition(10, 0);

	this->optionText.setFont(this->font);
	this->optionText.setString("Option");
	this->optionText.setCharacterSize(20);
	this->optionText.setFillColor(sf::Color::Black);
	this->optionText.setPosition(80, 0);

	this->preferenceText.setFont(this->font);
	this->preferenceText.setString("Preference");
	this->preferenceText.setCharacterSize(20);
	this->preferenceText.setFillColor(sf::Color::Black);
	this->preferenceText.setPosition(180, 0);
}

// MenuBar::~MenuBar()
// {
// }

void MenuBar::updateMenuBar(sf::Event event, sf::Vector2i mousePosition)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (this->fileText.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && fileMenuOpen){
				std::cout << "File menu closed" << std::endl;
				fileMenuOpen = false;
			}
			else if (!this->fileText.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && fileMenuOpen)
				fileMenuOpen = false;
			else if (this->fileText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				std::cout << "File menu opened" << std::endl;
				fileMenuOpen = true;
			}
			if (this->optionText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				std::cout << "Option menu clicked" << std::endl;
				optionMenuOpen = true;
			}
		}
	}
}

void MenuBar::update(sf::RenderWindow& window){
	this->menuBar.setSize(sf::Vector2f(window.getSize().x, 25));
}

void MenuBar::draw(sf::RenderWindow &window)
{
	update(window);
	window.draw(this->menuBar);
	window.draw(this->fileText);
	window.draw(this->optionText);
	window.draw(this->preferenceText);
}