#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <string>

#include "Tile.hpp"
#include "../Alliance.hpp"

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

	const std::vector<Tile *> gameBoard;
	const std::vector<Piece *> whitePieces;
	const std::vector<Piece *> blackPieces;

	std::vector<Move *> calculateLegalMoves(std::vector<Piece *> pieces);
	static std::vector<Piece *> calculateActivePieces(std::vector<Tile *> gameBoard, Alliance alliance);
	static std::vector<Tile *> createGameBoard(BoardBuilder builder);
	explicit Board(BoardBuilder &builder);

public:
	Tile *getTile(int tileCoordinate) const;
	static Board createStandardBoard();
	std::string stringify() const;
};

#endif