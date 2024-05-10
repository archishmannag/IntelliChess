#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class MenuBar
{
private:
	sf::RectangleShape menuBar;
	sf::Font font;

	// Main menu text
	sf::Text fileText, optionText, preferenceText;

	// File menu text and rectangle
	bool fileMenuOpen=false;
	sf::RectangleShape fileMenu;
	sf::Text newGameText, saveGameText, loadGameText, exitText;

	// Option menu text and rectangle
	bool optionMenuOpen = false;
	sf::RectangleShape optionMenu;
	sf::Text undoText, redoText, flipBoardText;

	// Preference menu text
	// sf::Text themeText, soundText, languageText;

	void update(sf::RenderWindow& window);

public:
	MenuBar(sf::RenderWindow &window);
	// ~MenuBar();
	void updateMenuBar(sf::Event event, sf::Vector2i mousePosition);
	void draw(sf::RenderWindow &window);
};

#endif