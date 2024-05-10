#include <SFML/Graphics.hpp>
#include <iostream>

#include "../../include/gui/GameBoard.hpp"
#include "../../include/gui/Menu.hpp"
#include "../../include/engine/board/Board.hpp"
#include "../../include/engine/board/Tile.hpp"
#include "../../include/engine/pieces/Piece.hpp"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 700
#define TILE_HEIGHT 70
#define TILE_WIDTH 70

/* TileBlock */

TileBlock::TileBlock(int tileId)
{
	this->tileId = tileId;
	// Initial size and positions
	this->tileRect.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
	this->tileRect.setFillColor((tileId / 8 + tileId) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
	this->tileRect.setPosition(200 + (tileId % 8) * TILE_WIDTH, 100 + (tileId / 8) * TILE_HEIGHT);
}

int TileBlock::getTileId() const
{
	return this->tileId;
}

sf::RectangleShape TileBlock::getTileRect() const
{
	return this->tileRect;
}

void TileBlock::setTileRectScale(float x, float y)
{
	this->tileRect.setScale(x, y);
}

void TileBlock::setTileRectPosition(float x, float y)
{
	this->tileRect.setPosition(x, y);
}

void TileBlock::setTileRectFillColor(sf::Color color)
{
	this->tileRect.setFillColor(color);
}

/* GameBoard */

GameBoard::GameBoard()
{
	init();
}

GameBoard::~GameBoard()
{
	this->tileBlocks.clear();
	delete this->menuBar;
	delete this->window;
}

void GameBoard::init()
{
	this->board = Board::createStandardBoard();

	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess");
	this->window->setFramerateLimit(60);

	this->menuBar = new MenuBar(*this->window);

	for (int i = 0; i < 64; i++)
	{
		this->tileBlocks.push_back(TileBlock(i));
	}

	if (
		!this->blackPawnTexture.loadFromFile("../resources/pieces/blackPawn.png") ||
		!this->whitePawnTexture.loadFromFile("../resources/pieces/whitePawn.png") ||
		!this->blackKingTexture.loadFromFile("../resources/pieces/blackKing.png") ||
		!this->whiteKingTexture.loadFromFile("../resources/pieces/whiteKing.png") ||
		!this->blackBishopTexture.loadFromFile("../resources/pieces/blackBishop.png") ||
		!this->whiteBishopTexture.loadFromFile("../resources/pieces/whiteBishop.png") ||
		!this->blackKnightTexture.loadFromFile("../resources/pieces/blackKnight.png") ||
		!this->whiteKnightTexture.loadFromFile("../resources/pieces/whiteKnight.png") ||
		!this->blackRookTexture.loadFromFile("../resources/pieces/blackRook.png") ||
		!this->whiteRookTexture.loadFromFile("../resources/pieces/whiteRook.png") ||
		!this->blackQueenTexture.loadFromFile("../resources/pieces/blackQueen.png") ||
		!this->whiteQueenTexture.loadFromFile("../resources/pieces/whiteQueen.png"))
	{
		std::cerr << "Error loading textures" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->blackPawnTexture.setSmooth(true);
	this->whitePawnTexture.setSmooth(true);
	this->blackKingTexture.setSmooth(true);
	this->whiteKingTexture.setSmooth(true);
	this->blackBishopTexture.setSmooth(true);
	this->whiteBishopTexture.setSmooth(true);
	this->blackKnightTexture.setSmooth(true);
	this->whiteKnightTexture.setSmooth(true);
	this->blackRookTexture.setSmooth(true);
	this->whiteRookTexture.setSmooth(true);
	this->blackQueenTexture.setSmooth(true);
	this->whiteQueenTexture.setSmooth(true);

	this->blackPawnSprite.setTexture(this->blackPawnTexture);
	this->whitePawnSprite.setTexture(this->whitePawnTexture);
	this->blackKingSprite.setTexture(this->blackKingTexture);
	this->whiteKingSprite.setTexture(this->whiteKingTexture);
	this->blackBishopSprite.setTexture(this->blackBishopTexture);
	this->whiteBishopSprite.setTexture(this->whiteBishopTexture);
	this->blackKnightSprite.setTexture(this->blackKnightTexture);
	this->whiteKnightSprite.setTexture(this->whiteKnightTexture);
	this->blackRookSprite.setTexture(this->blackRookTexture);
	this->whiteRookSprite.setTexture(this->whiteRookTexture);
	this->blackQueenSprite.setTexture(this->blackQueenTexture);
	this->whiteQueenSprite.setTexture(this->whiteQueenTexture);

	// Initial scales of the sprites, this will get updated everytime the window is resized
	this->blackPawnSprite.setScale(TILE_WIDTH / blackPawnSprite.getLocalBounds().width, TILE_HEIGHT / blackPawnSprite.getLocalBounds().height);
	this->whitePawnSprite.setScale(TILE_WIDTH / whitePawnSprite.getLocalBounds().width, TILE_HEIGHT / whitePawnSprite.getLocalBounds().height);
	this->blackKingSprite.setScale(TILE_WIDTH / blackKingSprite.getLocalBounds().width, TILE_HEIGHT / blackKingSprite.getLocalBounds().height);
	this->whiteKingSprite.setScale(TILE_WIDTH / whiteKingSprite.getLocalBounds().width, TILE_HEIGHT / whiteKingSprite.getLocalBounds().height);
	this->blackBishopSprite.setScale(TILE_WIDTH / blackBishopSprite.getLocalBounds().width, TILE_HEIGHT / blackBishopSprite.getLocalBounds().height);
	this->whiteBishopSprite.setScale(TILE_WIDTH / whiteBishopSprite.getLocalBounds().width, TILE_HEIGHT / whiteBishopSprite.getLocalBounds().height);
	this->blackKnightSprite.setScale(TILE_WIDTH / blackKnightSprite.getLocalBounds().width, TILE_HEIGHT / blackKnightSprite.getLocalBounds().height);
	this->whiteKnightSprite.setScale(TILE_WIDTH / whiteKnightSprite.getLocalBounds().width, TILE_HEIGHT / whiteKnightSprite.getLocalBounds().height);
	this->blackRookSprite.setScale(TILE_WIDTH / blackRookSprite.getLocalBounds().width, TILE_HEIGHT / blackRookSprite.getLocalBounds().height);
	this->whiteRookSprite.setScale(TILE_WIDTH / whiteRookSprite.getLocalBounds().width, TILE_HEIGHT / whiteRookSprite.getLocalBounds().height);
	this->blackQueenSprite.setScale(TILE_WIDTH / blackQueenSprite.getLocalBounds().width, TILE_HEIGHT / blackQueenSprite.getLocalBounds().height);
	this->whiteQueenSprite.setScale(TILE_WIDTH / whiteQueenSprite.getLocalBounds().width, TILE_HEIGHT / whiteQueenSprite.getLocalBounds().height);
}

bool GameBoard::isRunning() const
{
	return this->window->isOpen();
}

void GameBoard::processEvents()
{

	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (this->event.type == sf::Event::Resized)
		{
			// Set the view to the visible area
			sf::FloatRect visibleArea(0, 0, this->event.size.width, this->event.size.height);
			this->window->setView(sf::View(visibleArea));

			// Update the scale values
			this->windowScale = sf::Vector2f(static_cast<float>(this->event.size.width) / WINDOW_WIDTH, static_cast<float>(this->event.size.height) / WINDOW_HEIGHT);

			float min = std::min(this->windowScale.x, this->windowScale.y);

			// Update the scale of the sprites
			this->blackPawnSprite.setScale(TILE_WIDTH / blackPawnSprite.getLocalBounds().width * min, TILE_HEIGHT / blackPawnSprite.getLocalBounds().height * min);
			this->whitePawnSprite.setScale(TILE_WIDTH / whitePawnSprite.getLocalBounds().width * min, TILE_HEIGHT / whitePawnSprite.getLocalBounds().height * min);
			this->blackKingSprite.setScale(TILE_WIDTH / blackKingSprite.getLocalBounds().width * min, TILE_HEIGHT / blackKingSprite.getLocalBounds().height * min);
			this->whiteKingSprite.setScale(TILE_WIDTH / whiteKingSprite.getLocalBounds().width * min, TILE_HEIGHT / whiteKingSprite.getLocalBounds().height * min);
			this->blackBishopSprite.setScale(TILE_WIDTH / blackBishopSprite.getLocalBounds().width * min, TILE_HEIGHT / blackBishopSprite.getLocalBounds().height * min);
			this->whiteBishopSprite.setScale(TILE_WIDTH / whiteBishopSprite.getLocalBounds().width * min, TILE_HEIGHT / whiteBishopSprite.getLocalBounds().height * min);
			this->blackKnightSprite.setScale(TILE_WIDTH / blackKnightSprite.getLocalBounds().width * min, TILE_HEIGHT / blackKnightSprite.getLocalBounds().height * min);
			this->whiteKnightSprite.setScale(TILE_WIDTH / whiteKnightSprite.getLocalBounds().width * min, TILE_HEIGHT / whiteKnightSprite.getLocalBounds().height * min);
			this->blackRookSprite.setScale(TILE_WIDTH / blackRookSprite.getLocalBounds().width * min, TILE_HEIGHT / blackRookSprite.getLocalBounds().height * min);
			this->whiteRookSprite.setScale(TILE_WIDTH / whiteRookSprite.getLocalBounds().width * min, TILE_HEIGHT / whiteRookSprite.getLocalBounds().height * min);
			this->blackQueenSprite.setScale(TILE_WIDTH / blackQueenSprite.getLocalBounds().width * min, TILE_HEIGHT / blackQueenSprite.getLocalBounds().height * min);
			this->whiteQueenSprite.setScale(TILE_WIDTH / whiteQueenSprite.getLocalBounds().width * min, TILE_HEIGHT / whiteQueenSprite.getLocalBounds().height * min);
		}
		if (this->event.type == sf::Event::MouseButtonPressed)
		{
			menuBar->updateMenuBar(this->event, this->mousePosition);
		}
	}
}

void GameBoard::updateMousePosition()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
}

void GameBoard::updateTileBlocks()
{
	float min = std::min(this->windowScale.x, this->windowScale.y);
	for (auto &tileBlock : this->tileBlocks)
	{
		tileBlock.setTileRectScale(min, min);

		tileBlock.setTileRectPosition(static_cast<float>(this->window->getSize().x - 8 * TILE_WIDTH * min) / 2 + (tileBlock.getTileId() % 8) * TILE_WIDTH * min, 25 + 75 * min + (tileBlock.getTileId() / 8) * TILE_HEIGHT * min);

		if (tileBlock.getTileRect().getGlobalBounds().contains(this->mousePosition.x, this->mousePosition.y))
		{
			tileBlock.setTileRectFillColor(sf::Color(0, 255, 255, 100));
		}
		else
		{
			tileBlock.setTileRectFillColor((tileBlock.getTileId() / 8 + tileBlock.getTileId()) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
		}
	}
}

void GameBoard::update()
{
	processEvents();
	updateMousePosition();
	updateTileBlocks();
}

void GameBoard::renderTileBlocks()
{
	for (auto &tileBlock : this->tileBlocks)
	{
		this->window->draw(tileBlock.getTileRect());
		if (this->board->getTile(tileBlock.getTileId())->isTileOccupied())
		{
			// Draw piece
			Piece *piece = this->board->getTile(tileBlock.getTileId())->getPiece();
			switch (piece->getPieceType())
			{
			case PieceType::PAWN:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whitePawnSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whitePawnSprite);
				}
				else
				{
					this->blackPawnSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackPawnSprite);
				}
				break;
			case PieceType::KNIGHT:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whiteKnightSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whiteKnightSprite);
				}
				else
				{
					this->blackKnightSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackKnightSprite);
				}
				break;
			case PieceType::BISHOP:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whiteBishopSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whiteBishopSprite);
				}
				else
				{
					this->blackBishopSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackBishopSprite);
				}
				break;
			case PieceType::ROOK:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whiteRookSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whiteRookSprite);
				}
				else
				{
					this->blackRookSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackRookSprite);
				}
				break;
			case PieceType::QUEEN:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whiteQueenSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whiteQueenSprite);
				}
				else
				{
					this->blackQueenSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackQueenSprite);
				}
				break;
			case PieceType::KING:
				if (piece->getPieceAlliance() == Alliance::WHITE)
				{
					this->whiteKingSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->whiteKingSprite);
				}
				else
				{
					this->blackKingSprite.setPosition(tileBlock.getTileRect().getPosition().x, tileBlock.getTileRect().getPosition().y);
					this->window->draw(this->blackKingSprite);
				}
				break;
			default:
				break;
			}
		}
	}
}

void GameBoard::render()
{
	this->window->clear();

	renderTileBlocks();

	// Draw the menu bar
	this->menuBar->draw(*this->window);

	this->window->display();
}