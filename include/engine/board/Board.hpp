#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <string>

#include "Tile.hpp"
#include "../Alliance.hpp"
#include "../player/WhitePlayer.hpp"
#include "../player/BlackPlayer.hpp"

class Move;

class BoardBuilder
{
private:
	Alliance nextMoveMaker;

public:
	std::map<int, Piece *> boardConfig;

	BoardBuilder setPiece(Piece *piece);
	BoardBuilder setMoveMaker(Alliance moveMaker);
	Board build();
};

class Board
{
private:
	friend class BoardBuilder;

	const WhitePlayer *whitePlayer;
	const BlackPlayer *blackPlayer;
	Player *currentPlayer;

	std::vector<Tile *> gameBoard;
	std::vector<Piece *> whitePieces;
	std::vector<Piece *> blackPieces;

	std::vector<Move *> calculateLegalMoves(std::vector<Piece *> pieces);
	static std::vector<Piece *> calculateActivePieces(std::vector<Tile *> gameBoard, Alliance alliance);
	static std::vector<Tile *> createGameBoard(BoardBuilder builder);
	explicit Board(BoardBuilder &builder);

public:
	Tile *getTile(int tileCoordinate) const;
	std::vector<Piece *> getWhitePieces() const;
	std::vector<Piece *> getBlackPieces() const;
	const Player *getWhitePlayer() const;
	const Player *getBlackPlayer() const;
	const Player *getCurrentPlayer() const;
	static Board createStandardBoard();
	std::string stringify() const;
};

#endif