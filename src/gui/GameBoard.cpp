#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <gui/GameBoard.hpp>
#include <gui/Menu.hpp>
#include <gui/TakenPieces.hpp>
#include <gui/GameHistory.hpp>
#include <gui/GameSetup.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Tile.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/King.hpp>

/* TileBlock */

TileBlock::TileBlock(int tileId)
{
	this->tileId = tileId;
	// Initial size and positions
	this->tileRect.setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
	this->tileRect.setFillColor((tileId / 8 + tileId) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
	this->tileRect.setPosition(162.5f + (tileId % 8) * TILE_WIDTH, 75 + (tileId / 8) * TILE_HEIGHT);
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

/* MoveLog */

std::vector<Move *> MoveLog::getMoves() const
{
	return this->moves;
}

int MoveLog::getMovesCount() const
{
	return this->moves.size();
}

void MoveLog::addMove(Move *move)
{
	this->moves.push_back(move);
}

Move *MoveLog::removeMove(int index)
{
	Move *move = this->moves[index];
	this->moves.erase(this->moves.begin() + index);
	return move;
}

void MoveLog::removeMove(Move *move)
{
	this->moves.erase(std::remove(this->moves.begin(), this->moves.end(), move), this->moves.end());
}

void MoveLog::clearMoves()
{
	this->moves.clear();
}

/* GameBoard */

#define QUEEN_OFFSET 0
#define KNIGHT_OFFSET 8
#define ROOK_OFFSET 16
#define BISHOP_OFFSET 24

GameBoard::GameBoard()
{
	init();
}

GameBoard::~GameBoard()
{
	this->tileBlocks.clear();
	delete this->board;
	delete this->sourceTile;
	delete this->destinationTile;
	delete this->movedPiece;
	delete this->window;
}

void GameBoard::init()
{
	this->board = Board::createStandardBoard();
	this->sourceTile = nullptr;
	this->destinationTile = nullptr;
	this->movedPiece = nullptr;

	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess");
	this->window->setFramerateLimit(60);
	this->currentMainView = this->window->getDefaultView();

	this->bg.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	this->bg.setFillColor(sf::Color::White);

	this->boardRect.setSize(sf::Vector2f(10 + 8 * TILE_WIDTH, 10 + 8 * TILE_HEIGHT));
	this->boardRect.setFillColor(sf::Color(139, 71, 38));
	this->boardRect.setPosition(157.5f, 70);

	this->pawnPromotionRect.setSize(sf::Vector2f(1 * TILE_WIDTH, 4 * TILE_HEIGHT));
	this->pawnPromotionRect.setFillColor(sf::Color(139, 71, 38));

	callback_functions_t callbacks;
	callbacks.setup_game = [this]() -> void
	{ this->is_game_setup_open = true; };

	this->menuBar = std::make_unique<menu_bar>(*this->window, callbacks);

	this->takenPiecesBlock = std::make_unique<TakenPiecesBlock>();

	this->gameHistoryBlock = std::make_unique<GameHistoryBlock>();

	gameSetup = std::make_unique<game_setup>([this](player_type white_player_type, player_type black_player_type, int depth) -> void
											 { this->is_game_setup_open = false; },
											 [this]() -> void
											 {
												 this->is_game_setup_open = false;
											 });

	for (int i = 0; i < 64; i++)
	{
		this->tileBlocks.push_back(TileBlock(i));
	}

	if (
		!this->blackPawnTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackPawn.png") ||
		!this->whitePawnTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whitePawn.png") ||
		!this->blackKingTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKing.png") ||
		!this->whiteKingTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKing.png") ||
		!this->blackBishopTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackBishop.png") ||
		!this->whiteBishopTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteBishop.png") ||
		!this->blackKnightTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKnight.png") ||
		!this->whiteKnightTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKnight.png") ||
		!this->blackRookTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackRook.png") ||
		!this->whiteRookTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteRook.png") ||
		!this->blackQueenTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackQueen.png") ||
		!this->whiteQueenTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteQueen.png"))
	{
		throw std::runtime_error("Error loading textures");
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
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::Resized:
		{
			// Set the view to the visible area
			sf::FloatRect visibleArea(0, 0, this->event.size.width, this->event.size.height);
			this->currentMainView.setSize(visibleArea.width, visibleArea.height);
			this->currentMainView.setCenter(visibleArea.width / 2, visibleArea.height / 2);
			this->currentMainView.setViewport(sf::FloatRect(0, 0, 1, 1));
			this->window->setView(this->currentMainView);

			// Update the scale values
			this->windowScale = sf::Vector2f(static_cast<float>(this->event.size.width) / WINDOW_WIDTH, static_cast<float>(this->event.size.height) / WINDOW_HEIGHT);

			// Update size of the background
			this->bg.setSize(sf::Vector2f(this->event.size.width, this->event.size.height));

			this->scaleBoard();
			break;
		}
		case sf::Event::MouseButtonPressed:
			this->menuBar->update_menu_bar(this->event, this->mousePosition);
			if (is_game_setup_open)
				gameSetup->update(this->event, this->mousePosition);
			else
				moveHandler(this->mousePosition);
			gameHistoryBlock->scrollBarScrolled(this->event.mouseButton, true);
			break;
		case sf::Event::MouseButtonReleased:
			gameHistoryBlock->scrollBarScrolled(this->event.mouseButton, false);
			break;
		case sf::Event::MouseWheelScrolled:
			this->window->setView(this->gameHistoryBlock->getView());
			gameHistoryBlock->mouseWheelScrolled(this->event.mouseWheelScroll, sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
			this->window->setView(this->currentMainView);
			break;
		case sf::Event::MouseMoved:
			gameHistoryBlock->scroll(*this->window);
			break;
		case sf::Event::TextEntered:
			if (is_game_setup_open)
				gameSetup->update(this->event, this->mousePosition);
			break;
		default:
			break;
		}
	}
}

void GameBoard::scaleBoard()
{
	float min = std::min(this->windowScale.y, (this->window->getSize().x - 195 - 195) / static_cast<float>(570));

	// Update size and position of the board
	this->boardRect.setScale(min, min);
	this->pawnPromotionRect.setScale(min, min);

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

	for (auto &tileBlock : this->tileBlocks)
	{
		tileBlock.setTileRectScale(min, min);
		tileBlock.setTileRectPosition(157.5f + 5 * min + (tileBlock.getTileId() % 8) * TILE_WIDTH * min, 25 + 45 + 5 * min + (tileBlock.getTileId() / 8) * TILE_HEIGHT * min);
	}
}

void GameBoard::moveHandler(sf::Vector2i mousePosition)
{
	if (this->event.type == sf::Event::MouseButtonPressed)
	{
		if (this->event.mouseButton.button == sf::Mouse::Left)
		{
			for (auto &tileBlock : this->tileBlocks)
				if (tileBlock.getTileRect().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					if (this->sourceTile == nullptr)
					{
						this->sourceTile = this->board->getTile(tileBlock.getTileId());
						if ((this->movedPiece = this->sourceTile->getPiece()) == nullptr)
							this->sourceTile = nullptr;
					}
					else
					{
						this->destinationTile = this->board->getTile(tileBlock.getTileId());
						if (this->sourceTile->getTileCoordinate() == this->destinationTile->getTileCoordinate())
						{
							pawnPromotion = false;
							this->sourceTile = nullptr;
							this->destinationTile = nullptr;
							this->movedPiece = nullptr;
						}
						else if (pawnPromotion && pawnPromotionRect.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
						{
							pawnPromotion = false;
							Move *move;
							if (movedPiece->getPieceAlliance() == Alliance::WHITE)
							{
								switch (tileBlock.getTileId() / 8)
								{
								case 0:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8, PieceType::QUEEN);
									break;
								case 1:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8, PieceType::KNIGHT);
									break;
								case 2:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8, PieceType::ROOK);
									break;
								case 3:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8, PieceType::BISHOP);
									break;
								default:
									throw std::runtime_error("Invalid pawn promotion");
								}
							}
							else
							{
								switch (tileBlock.getTileId() / 8)
								{
								case 4:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8 + 56, PieceType::BISHOP);
									break;
								case 5:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8 + 56, PieceType::ROOK);
									break;
								case 6:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8 + 56, PieceType::KNIGHT);
									break;
								case 7:
									move = MoveFactory::createMove(board, sourceTile->getTileCoordinate(), destinationTile->getTileCoordinate() % 8 + 56, PieceType::QUEEN);
									break;
								default:
									throw std::runtime_error("Invalid pawn promotion");
								}
							}
							MoveTransition transition = this->board->getCurrentPlayer()->makeMove(move);
							if (transition.getMoveStatus() == MoveStatus::DONE)
							{
								this->board = transition.getTransitionBoard();
								this->moveLog.addMove(move);
								this->takenPiecesBlock->redo(this->moveLog);
								this->gameHistoryBlock->redo(this->board, this->moveLog);
							}
							this->sourceTile = nullptr;
							this->destinationTile = nullptr;
							this->movedPiece = nullptr;
						}
						else if (movedPiece->getPieceType() == PieceType::PAWN && isPawnPromotable(*this))
						{
							pawnPromotion = true;
						}
						else
						{
							pawnPromotion = false;
							Move *move = MoveFactory::createMove(this->board, this->sourceTile->getTileCoordinate(), this->destinationTile->getTileCoordinate());
							MoveTransition transition = this->board->getCurrentPlayer()->makeMove(move);
							if (transition.getMoveStatus() == MoveStatus::DONE)
							{
								this->board = transition.getTransitionBoard();
								this->moveLog.addMove(move);
								this->takenPiecesBlock->redo(this->moveLog);
								this->gameHistoryBlock->redo(this->board, this->moveLog);
							}
							this->sourceTile = nullptr;
							this->destinationTile = nullptr;
							this->movedPiece = nullptr;
						}
					}
				}
		}
	}
}

bool isPawnPromotable(GameBoard &gameBoard)
{
	if (gameBoard.movedPiece->getPieceAlliance() == Alliance::WHITE)
		return BoardUtils::FIRST_ROW[gameBoard.destinationTile->getTileCoordinate()];
	else
		return BoardUtils::EIGHTH_ROW[gameBoard.destinationTile->getTileCoordinate()];
}

void GameBoard::updateMousePosition()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
}

void GameBoard::updateTileBlocks()
{
	for (auto &tileBlock : this->tileBlocks)
	{
		std::vector<int> legalMoves = legalMoveDestinations();

		if (tileBlock.getTileRect().getGlobalBounds().contains(this->mousePosition.x, this->mousePosition.y))
		{
			tileBlock.setTileRectFillColor(sf::Color(0, 255, 255, 100));
		}
		else if (legalMoves.size() > 0 && std::find(legalMoves.begin(), legalMoves.end(), tileBlock.getTileId()) != legalMoves.end())
		{
			tileBlock.setTileRectFillColor(sf::Color(0, 255, 0, 100));
		}
		else if (this->board->getCurrentPlayer()->isInCheck() && this->board->getCurrentPlayer()->getPlayerKing()->getPiecePosition() == tileBlock.getTileId())
		{
			tileBlock.setTileRectFillColor(sf::Color(255, 0, 0, 100));
		}
		else if (this->sourceTile != nullptr && this->sourceTile->getTileCoordinate() == tileBlock.getTileId())
		{
			tileBlock.setTileRectFillColor(sf::Color(255, 255, 0, 100));
		}
		else
		{
			tileBlock.setTileRectFillColor((tileBlock.getTileId() / 8 + tileBlock.getTileId()) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
		}
	}
}

std::vector<int> GameBoard::legalMoveDestinations()
{
	std::vector<int> moveDestinations;
	if (movedPiece != nullptr && movedPiece->getPieceAlliance() == this->board->getCurrentPlayer()->getPlayerAlliance())
	{
		for (const auto move : this->movedPiece->calculateLegalMoves(*this->board))
			moveDestinations.push_back(move->getDestinationCoordinate());
	}
	return moveDestinations;
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

void GameBoard::renderPawnPromotionOptionPane()
{
	if (pawnPromotion)
	{
		if (movedPiece->getPieceAlliance() == Alliance::WHITE)
		{
			pawnPromotionRect.setPosition(tileBlocks[destinationTile->getTileCoordinate()].getTileRect().getPosition());
			this->window->draw(pawnPromotionRect);
			whiteQueenSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() + QUEEN_OFFSET].getTileRect().getPosition());
			window->draw(whiteQueenSprite);
			whiteKnightSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() + KNIGHT_OFFSET].getTileRect().getPosition());
			window->draw(whiteKnightSprite);
			whiteRookSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() + ROOK_OFFSET].getTileRect().getPosition());
			window->draw(whiteRookSprite);
			whiteBishopSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() + BISHOP_OFFSET].getTileRect().getPosition());
			window->draw(whiteBishopSprite);
		}
		else
		{
			pawnPromotionRect.setPosition(tileBlocks[destinationTile->getTileCoordinate() - 24].getTileRect().getPosition());
			this->window->draw(pawnPromotionRect);
			blackBishopSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() - BISHOP_OFFSET].getTileRect().getPosition());
			window->draw(blackBishopSprite);
			blackRookSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() - ROOK_OFFSET].getTileRect().getPosition());
			window->draw(blackRookSprite);
			blackKnightSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() - KNIGHT_OFFSET].getTileRect().getPosition());
			window->draw(blackKnightSprite);
			blackQueenSprite.setPosition(tileBlocks[destinationTile->getTileCoordinate() - QUEEN_OFFSET].getTileRect().getPosition());
			window->draw(blackQueenSprite);
		}
	}
}

void GameBoard::render()
{
	this->window->clear();

	// Draw the background
	this->window->draw(this->bg);

	// Draw the board
	this->window->draw(this->boardRect);
	renderTileBlocks();
	renderPawnPromotionOptionPane();

	// Draw the taken pieces block
	this->takenPiecesBlock->draw(*this->window);

	// Draw the game history block
	this->gameHistoryBlock->draw(*this->window);
	this->window->setView(this->currentMainView);

	// Draw the menu bar
	this->menuBar->draw(*this->window);

	if (is_game_setup_open)
		gameSetup->draw(*this->window);

	this->window->display();
}