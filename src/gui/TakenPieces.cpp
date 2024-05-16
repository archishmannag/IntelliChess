#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "../../include/gui/TakenPieces.hpp"
#include "../../include/gui/GameBoard.hpp"
#include "../../include/engine/board/Move.hpp"
#include "../../include/engine/pieces/Piece.hpp"
#include "../../include/engine/Alliance.hpp"

TakenPiecesBlock::TakenPiecesBlock()
{
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

	this->takenPieceAreaRect.setSize(sf::Vector2f(1.5f * TILE_WIDTH, 8 * TILE_HEIGHT));
	this->takenPieceAreaRect.setPosition(0, 75);
	this->takenPieceAreaRect.setFillColor(sf::Color(253, 245, 230));

	this->blackPieceAreaPosition = sf::Vector2f(this->takenPieceAreaRect.getPosition());
	this->whitePieceAreaPosition = sf::Vector2f(this->takenPieceAreaRect.getPosition() + sf::Vector2f(0, 4 * TILE_HEIGHT));
}

void TakenPiecesBlock::redo(MoveLog &moveLog)
{
	blackKingSprites.clear();
	whiteKingSprites.clear();
	blackQueenSprites.clear();
	whiteQueenSprites.clear();
	blackRookSprites.clear();
	whiteRookSprites.clear();
	blackBishopSprites.clear();
	whiteBishopSprites.clear();
	blackKnightSprites.clear();
	whiteKnightSprites.clear();
	blackPawnSprites.clear();
	whitePawnSprites.clear();

	std::vector<Piece *> whiteTakenPieces, blackTakenPieces;

	for (const auto move : moveLog.getMoves())
	{
		if (move->isAttack())
		{
			const auto takenPiece = move->getAttackedPiece();
			if (AllianceUtils::isWhite(takenPiece->getPieceAlliance()))
				whiteTakenPieces.push_back(takenPiece);
			else if (AllianceUtils::isBlack(takenPiece->getPieceAlliance()))
				blackTakenPieces.push_back(takenPiece);
			else
				throw std::runtime_error("Invalid piece alliance");
		}
	}

	std::sort(whiteTakenPieces.begin(), whiteTakenPieces.end(), [](Piece *a, Piece *b) -> bool
			  { return a->getPieceValue() > b->getPieceValue(); });
	std::sort(blackTakenPieces.begin(), blackTakenPieces.end(), [](Piece *a, Piece *b) -> bool
			  { return a->getPieceValue() > b->getPieceValue(); });

	sf::Vector2f position = this->whitePieceAreaPosition + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (const auto piece : whiteTakenPieces)
	{
		sf::Sprite sprite;
		switch (piece->getPieceType())
		{
		case PieceType::KING:
			sprite.setTexture(this->whiteKingTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whiteKingSprites.push_back(sprite);
			break;
		case PieceType::QUEEN:
			sprite.setTexture(this->whiteQueenTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whiteQueenSprites.push_back(sprite);
			break;
		case PieceType::ROOK:
			sprite.setTexture(this->whiteRookTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whiteRookSprites.push_back(sprite);
			break;
		case PieceType::BISHOP:
			sprite.setTexture(this->whiteBishopTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whiteBishopSprites.push_back(sprite);
			break;
		case PieceType::KNIGHT:
			sprite.setTexture(this->whiteKnightTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whiteKnightSprites.push_back(sprite);
			break;
		case PieceType::PAWN:
			sprite.setTexture(this->whitePawnTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->whitePawnSprites.push_back(sprite);
			break;
		default:
			throw std::runtime_error("Invalid piece type");
		}
		if (position.x > whitePieceAreaPosition.x + 0.75f * TILE_WIDTH)
			position.x = whitePieceAreaPosition.x + 0.125f * TILE_WIDTH, position.y += TILE_HEIGHT / 2;
		else
			position.x += TILE_WIDTH * 0.75f;
	}

	position = this->blackPieceAreaPosition + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (const auto piece : blackTakenPieces)
	{
		sf::Sprite sprite;
		switch (piece->getPieceType())
		{
		case PieceType::KING:
			sprite.setTexture(this->blackKingTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackKingSprites.push_back(sprite);
			break;
		case PieceType::QUEEN:
			sprite.setTexture(this->blackQueenTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackQueenSprites.push_back(sprite);
			break;
		case PieceType::ROOK:
			sprite.setTexture(this->blackRookTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackRookSprites.push_back(sprite);
			break;
		case PieceType::BISHOP:
			sprite.setTexture(this->blackBishopTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackBishopSprites.push_back(sprite);
			break;
		case PieceType::KNIGHT:
			sprite.setTexture(this->blackKnightTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackKnightSprites.push_back(sprite);
			break;
		case PieceType::PAWN:
			sprite.setTexture(this->blackPawnTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			this->blackPawnSprites.push_back(sprite);
			break;
		default:
			throw std::runtime_error("Invalid piece type");
		}
		if (position.x > blackPieceAreaPosition.x + 0.75f * TILE_WIDTH)
			position.x = blackPieceAreaPosition.x + 0.125f * TILE_WIDTH, position.y += TILE_HEIGHT / 2;
		else
			position.x += TILE_WIDTH * 0.75f;
	}
}

void TakenPiecesBlock::draw(sf::RenderWindow &window)
{
	window.draw(this->takenPieceAreaRect);
	for (const auto &sprite : this->blackPawnSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whitePawnSprites)
		window.draw(sprite);
	for (const auto &sprite : this->blackKnightSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whiteKnightSprites)
		window.draw(sprite);
	for (const auto &sprite : this->blackBishopSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whiteBishopSprites)
		window.draw(sprite);
	for (const auto &sprite : this->blackRookSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whiteRookSprites)
		window.draw(sprite);
	for (const auto &sprite : this->blackQueenSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whiteQueenSprites)
		window.draw(sprite);
	for (const auto &sprite : this->blackKingSprites)
		window.draw(sprite);
	for (const auto &sprite : this->whiteKingSprites)
		window.draw(sprite);
}