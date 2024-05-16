#ifndef TAKEN_PIECES_HPP
#define TAKEN_PIECES_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class MoveLog;

class TakenPiecesBlock
{
private:
	sf::Vector2f blackPieceAreaPosition, whitePieceAreaPosition;
	sf::RectangleShape takenPieceAreaRect;
	sf::Texture blackPawnTexture, whitePawnTexture, blackKingTexture, whiteKingTexture, blackBishopTexture, whiteBishopTexture, blackKnightTexture, whiteKnightTexture, blackRookTexture, whiteRookTexture, blackQueenTexture, whiteQueenTexture;
	std::vector<sf::Sprite> blackPawnSprites, whitePawnSprites, blackKingSprites, whiteKingSprites, blackBishopSprites, whiteBishopSprites, blackKnightSprites, whiteKnightSprites, blackRookSprites, whiteRookSprites, blackQueenSprites, whiteQueenSprites;

public:
	TakenPiecesBlock();
	void redo(MoveLog &moveLog);
	void draw(sf::RenderWindow &window);
};

#endif