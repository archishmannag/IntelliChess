#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Board;
class MenuBar;

class TileBlock
{
private:
	sf::RectangleShape tileRect;
	int tileId;

public:
	TileBlock(int tileId);
	int getTileId() const;
	sf::RectangleShape getTileRect() const;
	void setTileRectScale(float x, float y);
	void setTileRectPosition(float x, float y);
	void setTileRectFillColor(sf::Color color);
};

class GameBoard
{
private:
	// Window and event
	sf::RenderWindow *window;
	sf::Event event;

	// Window scale
	sf::Vector2f windowScale;

	// Mouse position and event
	sf::Vector2i mousePosition;

	// Main board, textures and sprites
	std::vector<TileBlock> tileBlocks;
	sf::Texture blackPawnTexture, whitePawnTexture, blackKnightTexture, whiteKnightTexture, blackBishopTexture, whiteBishopTexture, blackKingTexture, whiteKingTexture, blackRookTexture, whiteRookTexture, blackQueenTexture, whiteQueenTexture;
	sf::Sprite blackPawnSprite, whitePawnSprite, blackKnightSprite, whiteKnightSprite, blackBishopSprite, whiteBishopSprite, blackKingSprite, whiteKingSprite, blackRookSprite, whiteRookSprite, blackQueenSprite, whiteQueenSprite;

	// Menu bar
	MenuBar *menuBar;

	Board *board;

	void init();
	void processEvents();
	void updateMousePosition();
	void renderTileBlocks();
	void updateTileBlocks();

public:
	GameBoard();
	~GameBoard();
	bool isRunning() const;
	void update();
	void render();
};

#endif