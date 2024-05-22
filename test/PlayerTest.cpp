#include <gtest/gtest.h>

#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Rook.hpp>

TEST(PlayerTest, testSimpleEvaluation)
{
	Board *board = Board::createStandardBoard();
	MoveTransition t1 = board->getCurrentPlayer()->makeMove(MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("e2"), BoardUtils::getCoordinateAtPosition("e4"))),
				   t2 = t1.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t1.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("e7"), BoardUtils::getCoordinateAtPosition("e5")));
	ASSERT_EQ(MoveStatus::DONE, t1.getMoveStatus());
	ASSERT_EQ(MoveStatus::DONE, t2.getMoveStatus());
}

TEST(PlayerTest, testBug)
{
	Board *board = Board::createStandardBoard();
	MoveTransition t1 = board->getCurrentPlayer()->makeMove(MoveFactory::createMove(board, BoardUtils::getCoordinateAtPosition("c2"), BoardUtils::getCoordinateAtPosition("c3")));
	ASSERT_EQ(MoveStatus::DONE, t1.getMoveStatus());

	MoveTransition t2 = t1.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t1.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("b8"), BoardUtils::getCoordinateAtPosition("a6")));
	ASSERT_EQ(MoveStatus::DONE, t2.getMoveStatus());

	MoveTransition t3 = t2.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t2.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("d1"), BoardUtils::getCoordinateAtPosition("a4")));
	ASSERT_EQ(MoveStatus::DONE, t3.getMoveStatus());

	MoveTransition t4 = t3.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(t3.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("d7"), BoardUtils::getCoordinateAtPosition("d6")));
	ASSERT_NE(MoveStatus::DONE, t4.getMoveStatus());
}

TEST(PlayerTest, testDiscoveredCheck){
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	builder.setPiece(new Rook(24, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Bishop(44, Alliance::WHITE));
	builder.setPiece(new Rook(52, Alliance::WHITE));
	builder.setPiece(new King(58, Alliance::WHITE));

	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();
}