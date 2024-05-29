#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <memory>
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 700
#define TILE_HEIGHT 70
#define TILE_WIDTH 70

class Board;
class Tile;
class Piece;
class menu_bar;
class TakenPiecesBlock;
class GameHistoryBlock;
class game_setup;
class Move;
enum class player_type;

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

class MoveLog
{
private:
	std::vector<Move *> moves;

public:
	~MoveLog();
	std::vector<Move *> getMoves() const;
	int getMovesCount() const;
	void addMove(Move *move);
	Move *removeMove(int index);
	void removeMove(Move *move);
	void clearMoves();
};

class GameBoard
{
private:
	// Window and event
	sf::RenderWindow *window;
	sf::Event event;
	sf::RectangleShape bg;
	sf::View currentMainView;

	// Window scale
	sf::Vector2f windowScale;

	// Mouse position and event
	sf::Vector2i mousePosition;

	// Main board, textures and sprites
	sf::RectangleShape boardRect;
	std::vector<TileBlock> tileBlocks;
	sf::Texture blackPawnTexture, whitePawnTexture, blackKnightTexture, whiteKnightTexture, blackBishopTexture, whiteBishopTexture, blackKingTexture, whiteKingTexture, blackRookTexture, whiteRookTexture, blackQueenTexture, whiteQueenTexture;
	sf::Sprite blackPawnSprite, whitePawnSprite, blackKnightSprite, whiteKnightSprite, blackBishopSprite, whiteBishopSprite, blackKingSprite, whiteKingSprite, blackRookSprite, whiteRookSprite, blackQueenSprite, whiteQueenSprite;

	// Menu bar
	std::unique_ptr<menu_bar> menuBar;

	// Taken pieces
	std::unique_ptr<TakenPiecesBlock> takenPiecesBlock;

	// Game history
	std::unique_ptr<GameHistoryBlock> gameHistoryBlock;

	// Game setup
	std::unique_ptr<game_setup> gameSetup;
	bool is_game_setup_open = false;
	bool is_move_made = false;

	// Move log
	MoveLog moveLog;
	Board *board;
	Tile *sourceTile, *destinationTile;
	Piece *movedPiece;

	// Pawn Promotion
	sf::RectangleShape pawnPromotionRect;
	bool pawnPromotion = false;

	friend bool isPawnPromotable(GameBoard &gameBoard);

	void init();
	void processEvents();
	void updateMousePosition();
	void scaleBoard();
	void renderTileBlocks();
	void renderPawnPromotionOptionPane();
	void updateTileBlocks();
	std::vector<int> legalMoveDestinations();
	void moveHandler(sf::Vector2i mousePosition);
	void observe();

	class ai_move_generator
	{
	public:
		ai_move_generator(GameBoard *parent);
		void run();
		void done(Move *best_move);
		Move *get_best_move();

	private:
		GameBoard *parent;
	};

	std::unique_ptr<ai_move_generator> ai;

public:
	GameBoard();
	~GameBoard();
	bool isRunning() const;
	void update();
	void render();
};

bool isPawnPromotable(GameBoard &gameBoard);

#endif