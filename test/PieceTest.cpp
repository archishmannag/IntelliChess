#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

#include <engine/Alliance.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/board/Tile.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Knight.hpp>
#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/Queen.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/player/Player.hpp>

TEST(PieceTest, testMiddleQueenOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Queen(36, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(), blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(31, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e8"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("a4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("b4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("c4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("d4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("f4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("g4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("h4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testLegalMoveAllAvailable)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	builder.setPiece(new Knight(28, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Knight(36, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves();
	ASSERT_EQ(13, whiteLegalMoves.size());

	Move *wm1 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("d6")),
		 *wm2 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("f6")),
		 *wm3 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("c5")),
		 *wm4 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("g5")),
		 *wm5 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("c3")),
		 *wm6 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("g3")),
		 *wm7 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("d2")),
		 *wm8 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("f2"));

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm1](Move *m) -> bool
					{ return *m == *wm1; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm2](Move *m) -> bool
					{ return *m == *wm2; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm3](Move *m) -> bool
					{ return *m == *wm3; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm4](Move *m) -> bool
					{ return *m == *wm4; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm5](Move *m) -> bool
					{ return *m == *wm5; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm6](Move *m) -> bool
					{ return *m == *wm6; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm7](Move *m) -> bool
					{ return *m == *wm7; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm8](Move *m) -> bool
					{ return *m == *wm8; }) != whiteLegalMoves.end());

	BoardBuilder builder2;
	// Black Layout
	builder2.setPiece(new King(4, Alliance::BLACK));
	builder2.setPiece(new Knight(28, Alliance::BLACK));
	// White Layout
	builder2.setPiece(new Knight(36, Alliance::WHITE));
	builder2.setPiece(new King(60, Alliance::WHITE));
	builder2.setMoveMaker(Alliance::BLACK);
	Board *board2 = builder2.build();
	std::vector<Move *> blackLegalMoves = board2->getBlackPlayer()->getLegalMoves();
	ASSERT_EQ(13, blackLegalMoves.size());

	Move *bm1 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("d7")),
		 *bm2 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("f7")),
		 *bm3 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("c6")),
		 *bm4 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("g6")),
		 *bm5 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("c4")),
		 *bm6 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("g4")),
		 *bm7 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("d3")),
		 *bm8 = MoveFactory::createMove(board2, BoardUtils::getCoordinateAtPosition("e5"), BoardUtils::getCoordinateAtPosition("f3"));

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm1](Move *m) -> bool
					{ return *m == *bm1; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm2](Move *m) -> bool
					{ return *m == *bm2; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm3](Move *m) -> bool
					{ return *m == *bm3; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm4](Move *m) -> bool
					{ return *m == *bm4; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm5](Move *m) -> bool
					{ return *m == *bm5; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm6](Move *m) -> bool
					{ return *m == *bm6; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm7](Move *m) -> bool
					{ return *m == *bm7; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm8](Move *m) -> bool
					{ return *m == *bm8; }) != blackLegalMoves.end());
}

TEST(PieceTest, testKnightInCorners)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	builder.setPiece(new Knight(0, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Knight(56, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(7, whiteLegalMoves.size());
	ASSERT_EQ(7, blackLegalMoves.size());

	Move *wm1 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("b3")),
		 *wm2 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("c2")),
		 *bm1 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("b6")),
		 *bm2 = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("c7"));

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm1](Move *m) -> bool
					{ return *m == *wm1; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[wm2](Move *m) -> bool
					{ return *m == *wm2; }) != whiteLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm1](Move *m) -> bool
					{ return *m == *bm1; }) != blackLegalMoves.end());

	ASSERT_TRUE(std::find_if(
					blackLegalMoves.begin(),
					blackLegalMoves.end(),
					[bm2](Move *m) -> bool
					{ return *m == *bm2; }) != blackLegalMoves.end());
}

TEST(PieceTest, testMiddleBishopOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(35, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(18, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("a7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("b6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("c5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("e3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("f2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("g1"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("a1"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());

	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("d4"), BoardUtils::getCoordinateAtPosition("b2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testTopLeftBishopOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(0, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);

	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(board->getTile(0)->getPiece(), board->getTile(0)->getPiece());
	ASSERT_NE(nullptr, board->getTile(0)->getPiece());

	ASSERT_EQ(12, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("b7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("c6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("d5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("e4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("f3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("g2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a8"), BoardUtils::getCoordinateAtPosition("h1"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testTopRightBishopOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(7, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);

	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(board->getTile(7)->getPiece(), board->getTile(7)->getPiece());
	ASSERT_NE(nullptr, board->getTile(7)->getPiece());

	ASSERT_EQ(12, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("g7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("f6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("e5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("d4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("c3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("b2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h8"), BoardUtils::getCoordinateAtPosition("a1"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testBottomLeftBishopOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(56, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);

	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(board->getTile(56)->getPiece(), board->getTile(56)->getPiece());
	ASSERT_NE(nullptr, board->getTile(56)->getPiece());

	ASSERT_EQ(12, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("b2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("c3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("d4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("e5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("f6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("g7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("a1"), BoardUtils::getCoordinateAtPosition("h8"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testBottomRightBishopOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(63, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);

	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(board->getTile(63)->getPiece(), board->getTile(63)->getPiece());
	ASSERT_NE(nullptr, board->getTile(63)->getPiece());

	ASSERT_EQ(12, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("g2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("f3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("e4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("d5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("c6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("b7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h1"), BoardUtils::getCoordinateAtPosition("a8"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testMiddleRookOnEmptyBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Rook(36, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
	std::vector<Move *> whiteLegalMoves = board->getWhitePlayer()->getLegalMoves(),
						blackLegalMoves = board->getBlackPlayer()->getLegalMoves();

	ASSERT_EQ(18, whiteLegalMoves.size());
	ASSERT_EQ(5, blackLegalMoves.size());

	Move *move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e8"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e7"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e6"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e5"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e3"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("e2"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("a4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("b4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("c4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("d4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("f4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("g4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
	move = MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e4"), BoardUtils::getCoordinateAtPosition("h4"));
	ASSERT_TRUE(std::find_if(
					whiteLegalMoves.begin(),
					whiteLegalMoves.end(),
					[move](Move *m) -> bool
					{ return *m == *move; }) != whiteLegalMoves.end());
}

TEST(PieceTest, testPawnPromotion)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(22, Alliance::BLACK));
	builder.setPiece(new Rook(3, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Pawn(15, Alliance::WHITE));
	builder.setPiece(new King(52, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();

	MoveTransition t1 = board->getCurrentPlayer()->makeMove(MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("h7"), BoardUtils::getCoordinateAtPosition("h8")));
	ASSERT_EQ(MoveStatus::DONE, t1.getMoveStatus());

	MoveTransition t2 = t1.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t1.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("d8"), BoardUtils::getCoordinateAtPosition("h8")));
	ASSERT_EQ(MoveStatus::DONE, t2.getMoveStatus());

	MoveTransition t3 = t2.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t2.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("e2"), BoardUtils::getCoordinateAtPosition("d2")));
	ASSERT_EQ(MoveStatus::DONE, t3.getMoveStatus());
}

TEST(PieceTest, testKingEquality)
{
	const Board *const board = Board::createStandardBoard(),
					   *const board2 = Board::createStandardBoard();

	ASSERT_TRUE(*board->getTile(60)->getPiece() == *board2->getTile(60)->getPiece());
	ASSERT_FALSE(board->getTile(60)->getPiece() == nullptr);
}