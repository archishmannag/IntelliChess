#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <string>

#include "../Alliance.hpp"

class Move;
class Pawn;
class Tile;
class Piece;
class Player;
class WhitePlayer;
class BlackPlayer;

class BoardBuilder
{
private:
	Alliance nextMoveMaker;
	Pawn *enPassantPawn = nullptr;

public:
	std::map<int, Piece *> boardConfig;

	BoardBuilder setPiece(Piece *piece);
	void setEnPassantPawn(Pawn *enPassantPawn);
	BoardBuilder setMoveMaker(Alliance moveMaker);
	Alliance getNextMoveMaker() const;
	Board *build();
};

class Board
{
private:
	friend class BoardBuilder;

	std::vector<Tile *> gameBoard;
	std::vector<Piece *> whitePieces;
	std::vector<Piece *> blackPieces;

	const WhitePlayer *whitePlayer;
	const BlackPlayer *blackPlayer;
	Player *currentPlayer;

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
	Player *getCurrentPlayer() const;
	std::vector<Move *> getAllLegalMoves() const;
	static Board *createStandardBoard();
	std::string stringify() const;
};

#endif