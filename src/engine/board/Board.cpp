#include "../../../include/engine/board/Board.hpp"
#include "../../../include/engine/pieces/Piece.hpp"
#include "../../../include/engine/pieces/Pawn.hpp"
#include "../../../include/engine/pieces/Rook.hpp"
#include "../../../include/engine/pieces/Knight.hpp"
#include "../../../include/engine/pieces/Bishop.hpp"
#include "../../../include/engine/pieces/Queen.hpp"
#include "../../../include/engine/pieces/King.hpp"
#include "../../../include/engine/board/Move.hpp"
#include "../../../include/engine/board/Tile.hpp"
#include "../../../include/engine/player/WhitePlayer.hpp"
#include "../../../include/engine/player/BlackPlayer.hpp"

/* BoardBuilder */
BoardBuilder BoardBuilder::setPiece(Piece *piece)
{
	this->boardConfig[piece->getPiecePosition()] = piece;
	return *this;
}

void BoardBuilder::setEnPassantPawn(Pawn *enPassantPawn)
{
	this->enPassantPawn = enPassantPawn;
}

BoardBuilder BoardBuilder::setMoveMaker(const Alliance moveMaker)
{
	this->nextMoveMaker = moveMaker;
	return *this;
}

Alliance BoardBuilder::getNextMoveMaker() const
{
	return this->nextMoveMaker;
}

Board *BoardBuilder::build()
{
	return new Board(*this);
}

/* Board */

/**
 * @brief Construct a new Board object
 *
 * @param builder An instance of BoardBuilder used to instantiate the Board object
 */
Board::Board(BoardBuilder &builder) : gameBoard(Board::createGameBoard(builder)), whitePieces(Board::calculateActivePieces(gameBoard, Alliance::WHITE)), blackPieces(Board::calculateActivePieces(gameBoard, Alliance::BLACK)), whitePlayer(new WhitePlayer(this, this->calculateLegalMoves(this->whitePieces), this->calculateLegalMoves(this->blackPieces))), blackPlayer(new BlackPlayer(this, this->calculateLegalMoves(this->whitePieces), this->calculateLegalMoves(this->blackPieces))), currentPlayer(const_cast<Player *>(AllianceUtils::choosePlayer(builder.getNextMoveMaker(), this))) {}

std::vector<Move *> Board::calculateLegalMoves(const std::vector<Piece *> pieces)
{
	std::vector<Move *> legalMoves;
	for (const auto &piece : pieces)
	{
		const std::vector<Move *> pieceLegalMoves = piece->calculateLegalMoves(*this);
		legalMoves.insert(legalMoves.end(), pieceLegalMoves.begin(), pieceLegalMoves.end());
	}
	return legalMoves;
}

std::vector<Piece *> Board::calculateActivePieces(std::vector<Tile *> gameBoard, Alliance alliance)
{
	std::vector<Piece *> activePieces;
	for (const auto &tile : gameBoard)
	{
		if (tile->isTileOccupied())
		{
			auto piece = tile->getPiece();
			if (piece->getPieceAlliance() == alliance)
				activePieces.push_back(piece);
		}
	}
	return activePieces;
}

std::vector<Tile *> Board::createGameBoard(const BoardBuilder builder)
{
	std::vector<Tile *> tiles(64, nullptr);
	for (int i = 0; i < 64; i++)
	{
		auto iter = builder.boardConfig.find(i);
		if (iter != builder.boardConfig.end())
			tiles[i] = Tile::createTile(i, iter->second);
		else
			tiles[i] = Tile::createTile(i, nullptr);
	}
	return tiles;
}

Tile *Board::getTile(const int tileCoordinate) const
{
	return gameBoard[tileCoordinate];
}

std::vector<Piece *> Board::getWhitePieces() const
{
	return this->whitePieces;
}

std::vector<Piece *> Board::getBlackPieces() const
{
	return this->blackPieces;
}

const Player *Board::getWhitePlayer() const
{
	return this->whitePlayer;
}

const Player *Board::getBlackPlayer() const
{
	return this->blackPlayer;
}

Player *Board::getCurrentPlayer() const
{
	return this->currentPlayer;
}

std::vector<Move *> Board::getAllLegalMoves() const
{
	std::vector<Move *> allLegalMoves;
	allLegalMoves.insert(allLegalMoves.end(), this->whitePlayer->getLegalMoves().begin(), this->whitePlayer->getLegalMoves().end());
	allLegalMoves.insert(allLegalMoves.end(), this->blackPlayer->getLegalMoves().begin(), this->blackPlayer->getLegalMoves().end());
	return allLegalMoves;
}

Board *Board::createStandardBoard()
{
	BoardBuilder builder;

	// Black Pieces
	builder.setPiece(new Rook(0, Alliance::BLACK));
	builder.setPiece(new Knight(1, Alliance::BLACK));
	builder.setPiece(new Bishop(2, Alliance::BLACK));
	builder.setPiece(new Queen(3, Alliance::BLACK));
	builder.setPiece(new King(4, Alliance::BLACK));
	builder.setPiece(new Bishop(5, Alliance::BLACK));
	builder.setPiece(new Knight(6, Alliance::BLACK));
	builder.setPiece(new Rook(7, Alliance::BLACK));
	builder.setPiece(new Pawn(8, Alliance::BLACK));
	builder.setPiece(new Pawn(9, Alliance::BLACK));
	builder.setPiece(new Pawn(10, Alliance::BLACK));
	builder.setPiece(new Pawn(11, Alliance::BLACK));
	builder.setPiece(new Pawn(12, Alliance::BLACK));
	builder.setPiece(new Pawn(13, Alliance::BLACK));
	builder.setPiece(new Pawn(14, Alliance::BLACK));
	builder.setPiece(new Pawn(15, Alliance::BLACK));

	// White Pieces
	builder.setPiece(new Pawn(48, Alliance::WHITE));
	builder.setPiece(new Pawn(49, Alliance::WHITE));
	builder.setPiece(new Pawn(50, Alliance::WHITE));
	builder.setPiece(new Pawn(51, Alliance::WHITE));
	builder.setPiece(new Pawn(52, Alliance::WHITE));
	builder.setPiece(new Pawn(53, Alliance::WHITE));
	builder.setPiece(new Pawn(54, Alliance::WHITE));
	builder.setPiece(new Pawn(55, Alliance::WHITE));
	builder.setPiece(new Rook(56, Alliance::WHITE));
	builder.setPiece(new Knight(57, Alliance::WHITE));
	builder.setPiece(new Bishop(58, Alliance::WHITE));
	builder.setPiece(new Queen(59, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setPiece(new Bishop(61, Alliance::WHITE));
	builder.setPiece(new Knight(62, Alliance::WHITE));
	builder.setPiece(new Rook(63, Alliance::WHITE));

	// Starting player is white
	builder.setMoveMaker(Alliance::WHITE);

	return builder.build();
}

std::string Board::stringify() const
{
	std::string boardString = "";
	for (int i = 0; i < 64; i++)
	{
		boardString += this->gameBoard[i]->stringify();
		if ((i + 1) % 8 == 0)
			boardString += "\n";
	}
	return boardString;
}