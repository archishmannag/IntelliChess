#ifndef GAME_HISTORY_HPP
#define GAME_HISTORY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <vector>

class Board;
class MoveLog;

class HistoryRow
{
private:
	sf::Vector2f position;
	sf::Text whiteMove, blackMove;
	sf::RectangleShape bottomDividerRect;

public:
	HistoryRow(sf::Font &font);
	void setPosition(sf::Vector2f position);
	void setWhiteMove(std::string move);
	void setBlackMove(std::string move);
	sf::Vector2f getPosition() const;
	std::string getWhiteMove();
	std::string getBlackMove();
	void draw(sf::RenderWindow &window);
};

class GameHistoryBlock
{
private:
	sf::Vector2f scale, mouseOffset;
	sf::RectangleShape gameHistoryAreaRect, scrollBarRect, dividerRect;
	std::vector<HistoryRow> historyRows;
	sf::Font font;
	std::array<sf::Text, 2> playerNames;
	sf::View view;
	float scrollPercentageTop, scrollPercentageBottom;
	bool scrollBarClicked;

	void update(sf::RenderWindow &window);
	void updateScrollPercentage(sf::Vector2f windowSize);
	std::string calculateCheckAndCheckMate(Board *board);

public:
	GameHistoryBlock();
	sf::View getView() const;
	void mouseWheelScrolled(sf::Event::MouseWheelScrollEvent &event, sf::Vector2f windowSize);
	void scrollBarScrolled(sf::Event::MouseButtonEvent &event, bool buttonClickedOrReleased);
	void scroll(sf::RenderWindow &window);
	void redo(Board *board, MoveLog &moveLog);
	void draw(sf::RenderWindow &window);
};

#endif