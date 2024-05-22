#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <gui/TakenPieces.hpp>
#include <gui/GameBoard.hpp>
#include <engine/board/Move.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/Alliance.hpp>

TakenPiecesBlock::TakenPiecesBlock()
{
	if (
		!blackPawnTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackPawn.png") ||
		!whitePawnTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whitePawn.png") ||
		!blackKingTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKing.png") ||
		!whiteKingTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKing.png") ||
		!blackBishopTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackBishop.png") ||
		!whiteBishopTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteBishop.png") ||
		!blackKnightTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKnight.png") ||
		!whiteKnightTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKnight.png") ||
		!blackRookTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackRook.png") ||
		!whiteRookTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteRook.png") ||
		!blackQueenTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackQueen.png") ||
		!whiteQueenTexture.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteQueen.png"))
	{
		throw std::runtime_error("Failed to load piece textures");
	}

	blackPawnTexture.setSmooth(true);
	whitePawnTexture.setSmooth(true);
	blackKingTexture.setSmooth(true);
	whiteKingTexture.setSmooth(true);
	blackBishopTexture.setSmooth(true);
	whiteBishopTexture.setSmooth(true);
	blackKnightTexture.setSmooth(true);
	whiteKnightTexture.setSmooth(true);
	blackRookTexture.setSmooth(true);
	whiteRookTexture.setSmooth(true);
	blackQueenTexture.setSmooth(true);
	whiteQueenTexture.setSmooth(true);

	takenPieceAreaRect.setSize(sf::Vector2f(1.5f * TILE_WIDTH, 8 * TILE_HEIGHT));
	takenPieceAreaRect.setPosition(0, 75);
	takenPieceAreaRect.setFillColor(sf::Color(253, 245, 230));

	blackPieceAreaPosition = sf::Vector2f(takenPieceAreaRect.getPosition());
	whitePieceAreaPosition = sf::Vector2f(takenPieceAreaRect.getPosition() + sf::Vector2f(0, 4 * TILE_HEIGHT));
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

	sf::Vector2f position = whitePieceAreaPosition + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (const auto piece : whiteTakenPieces)
	{
		sf::Sprite sprite;
		switch (piece->getPieceType())
		{
		case PieceType::KING:
			sprite.setTexture(whiteKingTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whiteKingSprites.push_back(sprite);
			break;
		case PieceType::QUEEN:
			sprite.setTexture(whiteQueenTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whiteQueenSprites.push_back(sprite);
			break;
		case PieceType::ROOK:
			sprite.setTexture(whiteRookTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whiteRookSprites.push_back(sprite);
			break;
		case PieceType::BISHOP:
			sprite.setTexture(whiteBishopTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whiteBishopSprites.push_back(sprite);
			break;
		case PieceType::KNIGHT:
			sprite.setTexture(whiteKnightTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whiteKnightSprites.push_back(sprite);
			break;
		case PieceType::PAWN:
			sprite.setTexture(whitePawnTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			whitePawnSprites.push_back(sprite);
			break;
		default:
			throw std::runtime_error("Invalid piece type");
		}
		if (position.x > whitePieceAreaPosition.x + 0.75f * TILE_WIDTH)
			position.x = whitePieceAreaPosition.x + 0.125f * TILE_WIDTH, position.y += TILE_HEIGHT / 2;
		else
			position.x += TILE_WIDTH * 0.75f;
	}

	position = blackPieceAreaPosition + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (const auto piece : blackTakenPieces)
	{
		sf::Sprite sprite;
		switch (piece->getPieceType())
		{
		case PieceType::KING:
			sprite.setTexture(blackKingTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackKingSprites.push_back(sprite);
			break;
		case PieceType::QUEEN:
			sprite.setTexture(blackQueenTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackQueenSprites.push_back(sprite);
			break;
		case PieceType::ROOK:
			sprite.setTexture(blackRookTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackRookSprites.push_back(sprite);
			break;
		case PieceType::BISHOP:
			sprite.setTexture(blackBishopTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackBishopSprites.push_back(sprite);
			break;
		case PieceType::KNIGHT:
			sprite.setTexture(blackKnightTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackKnightSprites.push_back(sprite);
			break;
		case PieceType::PAWN:
			sprite.setTexture(blackPawnTexture);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			blackPawnSprites.push_back(sprite);
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
	window.draw(takenPieceAreaRect);
	for (const auto &sprite : blackPawnSprites)
		window.draw(sprite);
	for (const auto &sprite : whitePawnSprites)
		window.draw(sprite);
	for (const auto &sprite : blackKnightSprites)
		window.draw(sprite);
	for (const auto &sprite : whiteKnightSprites)
		window.draw(sprite);
	for (const auto &sprite : blackBishopSprites)
		window.draw(sprite);
	for (const auto &sprite : whiteBishopSprites)
		window.draw(sprite);
	for (const auto &sprite : blackRookSprites)
		window.draw(sprite);
	for (const auto &sprite : whiteRookSprites)
		window.draw(sprite);
	for (const auto &sprite : blackQueenSprites)
		window.draw(sprite);
	for (const auto &sprite : whiteQueenSprites)
		window.draw(sprite);
	for (const auto &sprite : blackKingSprites)
		window.draw(sprite);
	for (const auto &sprite : whiteKingSprites)
		window.draw(sprite);
}