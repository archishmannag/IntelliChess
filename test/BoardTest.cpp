#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>

#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/board/Tile.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/Bishop.hpp>
#include <engine/pieces/King.hpp>
#include <engine/pieces/Knight.hpp>
#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Queen.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/player/Player.hpp>
#include <engine/player/ai/MoveStrategy.hpp>
#include <engine/player/ai/MiniMax.hpp>
#include <engine/Alliance.hpp>

TEST(BoardTest, testInitialBoard)
{
	const Board *board = Board::createStandardBoard();
	EXPECT_EQ(20, board->getCurrentPlayer()->getLegalMoves().size());
	EXPECT_EQ(20, board->getCurrentPlayer()->getOpponent()->getLegalMoves().size());

	ASSERT_FALSE(board->getCurrentPlayer()->isInCheck());
	ASSERT_FALSE(board->getCurrentPlayer()->isInCheckMate());
	ASSERT_FALSE(board->getCurrentPlayer()->isCastled());

	ASSERT_FALSE(board->getCurrentPlayer()->getOpponent()->isInCheck());
	ASSERT_FALSE(board->getCurrentPlayer()->getOpponent()->isInCheckMate());
	ASSERT_FALSE(board->getCurrentPlayer()->getOpponent()->isCastled());

	ASSERT_EQ(board->getCurrentPlayer(), board->getWhitePlayer());
	ASSERT_EQ(board->getCurrentPlayer()->getOpponent(), board->getBlackPlayer());

	ASSERT_STREQ("White", AllianceUtils::stringify(board->getCurrentPlayer()->getPlayerAlliance()).c_str());
	ASSERT_STREQ("Black", AllianceUtils::stringify(board->getCurrentPlayer()->getOpponent()->getPlayerAlliance()).c_str());

	std::vector<Piece *> allPieces = board->getWhitePieces(),
						 blackPieces = board->getBlackPieces();
	allPieces.insert(allPieces.end(), blackPieces.begin(), blackPieces.end());
	std::vector<Move *> allMoves = board->getAllLegalMoves();
	for (const auto move : allMoves)
	{
		ASSERT_FALSE(move->isAttack());
		ASSERT_FALSE(move->isCastlingMove());
	}

	ASSERT_EQ(32, allPieces.size());
	ASSERT_EQ(40, allMoves.size());
	ASSERT_EQ(nullptr, board->getTile(35)->getPiece());
}

TEST(BoardTest, testPlainKingMove)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new King(4, Alliance::BLACK));
	builder.setPiece(new Pawn(12, Alliance::BLACK));
	// White Layout
	builder.setPiece(new Pawn(52, Alliance::WHITE));
	builder.setPiece(new King(60, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);
	Board *board = builder.build();

	ASSERT_EQ(6, board->getWhitePlayer()->getLegalMoves().size());
	ASSERT_EQ(6, board->getBlackPlayer()->getLegalMoves().size());
	ASSERT_FALSE(board->getWhitePlayer()->isInCheck());
	ASSERT_FALSE(board->getWhitePlayer()->isInCheckMate());
	ASSERT_FALSE(board->getWhitePlayer()->isCastled());
	ASSERT_FALSE(board->getBlackPlayer()->isInCheck());
	ASSERT_FALSE(board->getBlackPlayer()->isInCheckMate());
	ASSERT_FALSE(board->getBlackPlayer()->isCastled());
	ASSERT_EQ(board->getWhitePlayer(), board->getCurrentPlayer());
	ASSERT_EQ(board->getBlackPlayer(), board->getWhitePlayer()->getOpponent());

	auto move = MoveFactory::createMove(
		board,
		BoardUtils::getCoordinateAtPosition("e1"),
		BoardUtils::getCoordinateAtPosition("f1"));
	auto transition = board->getCurrentPlayer()->makeMove(move);
	ASSERT_EQ(move, transition.getMove());
	ASSERT_EQ(transition.getTransitionBoard()->getCurrentPlayer(), transition.getTransitionBoard()->getBlackPlayer());
	ASSERT_TRUE(transition.getMoveStatus() == MoveStatus::DONE);
	ASSERT_EQ(61, transition.getTransitionBoard()->getWhitePlayer()->getPlayerKing()->getPiecePosition());
}

TEST(BoardTest, testAlgebraicNotation)
{
	ASSERT_STREQ("a8", BoardUtils::getPositionAtCoordinate(0).c_str());
	ASSERT_STREQ("b8", BoardUtils::getPositionAtCoordinate(1).c_str());
	ASSERT_STREQ("c8", BoardUtils::getPositionAtCoordinate(2).c_str());
	ASSERT_STREQ("d8", BoardUtils::getPositionAtCoordinate(3).c_str());
	ASSERT_STREQ("e8", BoardUtils::getPositionAtCoordinate(4).c_str());
	ASSERT_STREQ("f8", BoardUtils::getPositionAtCoordinate(5).c_str());
	ASSERT_STREQ("g8", BoardUtils::getPositionAtCoordinate(6).c_str());
	ASSERT_STREQ("h8", BoardUtils::getPositionAtCoordinate(7).c_str());
	ASSERT_STREQ("a1", BoardUtils::getPositionAtCoordinate(56).c_str());
	ASSERT_STREQ("b1", BoardUtils::getPositionAtCoordinate(57).c_str());
	ASSERT_STREQ("c1", BoardUtils::getPositionAtCoordinate(58).c_str());
	ASSERT_STREQ("d1", BoardUtils::getPositionAtCoordinate(59).c_str());
	ASSERT_STREQ("e1", BoardUtils::getPositionAtCoordinate(60).c_str());
	ASSERT_STREQ("f1", BoardUtils::getPositionAtCoordinate(61).c_str());
	ASSERT_STREQ("g1", BoardUtils::getPositionAtCoordinate(62).c_str());
	ASSERT_STREQ("h1", BoardUtils::getPositionAtCoordinate(63).c_str());
}

TEST(BoardTest, testInvalidBoard)
{
	BoardBuilder builder;
	// Black Layout
	builder.setPiece(new Rook(0, Alliance::BLACK));
	builder.setPiece(new Knight(1, Alliance::BLACK));
	builder.setPiece(new Bishop(2, Alliance::BLACK));
	builder.setPiece(new Queen(3, Alliance::BLACK));
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
	// White Layout
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
	builder.setPiece(new Bishop(61, Alliance::WHITE));
	builder.setPiece(new Knight(62, Alliance::WHITE));
	builder.setPiece(new Rook(63, Alliance::WHITE));
	builder.setMoveMaker(Alliance::WHITE);

	ASSERT_THROW(builder.build(), std::runtime_error);
}

int calculatedActivesFor(Board *board, Alliance alliance)
{
	int count = 0;
	for (auto piece : board->getAllPieces())
	{
		if (piece->getPieceAlliance() == alliance)
		{
			count++;
		}
	}
	return count;
}

TEST(BoardTest, testBoardConsistency)
{
	Board *board = Board::createStandardBoard();
	ASSERT_EQ(board->getWhitePlayer(), board->getCurrentPlayer());

	MoveTransition t1 = board->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		board,
		BoardUtils::getCoordinateAtPosition("e2"),
		BoardUtils::getCoordinateAtPosition("e4")));

	MoveTransition t2 = t1.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t1.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("e7"),
		BoardUtils::getCoordinateAtPosition("e5")));

	MoveTransition t3 = t2.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t2.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("g1"),
		BoardUtils::getCoordinateAtPosition("f3")));

	MoveTransition t4 = t3.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t3.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("d7"),
		BoardUtils::getCoordinateAtPosition("d5")));

	MoveTransition t5 = t4.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t4.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("e4"),
		BoardUtils::getCoordinateAtPosition("d5")));

	MoveTransition t6 = t5.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t5.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("d8"),
		BoardUtils::getCoordinateAtPosition("d5")));

	MoveTransition t7 = t6.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t6.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("f3"),
		BoardUtils::getCoordinateAtPosition("g5")));

	MoveTransition t8 = t7.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t7.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("f7"),
		BoardUtils::getCoordinateAtPosition("f6")));

	MoveTransition t9 = t8.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t8.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("d1"),
		BoardUtils::getCoordinateAtPosition("h5")));

	MoveTransition t10 = t9.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t9.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("g7"),
		BoardUtils::getCoordinateAtPosition("g6")));

	MoveTransition t11 = t10.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t10.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("h5"),
		BoardUtils::getCoordinateAtPosition("h4")));

	MoveTransition t12 = t11.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t11.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("f6"),
		BoardUtils::getCoordinateAtPosition("g5")));

	MoveTransition t13 = t12.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t12.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("h4"),
		BoardUtils::getCoordinateAtPosition("g5")));

	MoveTransition t14 = t13.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t13.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("d5"),
		BoardUtils::getCoordinateAtPosition("e4")));

	ASSERT_TRUE(t14.getTransitionBoard()->getWhitePlayer()->isInCheck());
	ASSERT_TRUE(t14.getTransitionBoard()->getWhitePlayer()->getActivePieces().size() == calculatedActivesFor(t14.getTransitionBoard(), Alliance::WHITE));
	ASSERT_TRUE(t14.getTransitionBoard()->getBlackPlayer()->getActivePieces().size() == calculatedActivesFor(t14.getTransitionBoard(), Alliance::BLACK));
}

#ifdef UNIX
size_t getCurrentMemoryUsage()
{
	// Run garbage collection
	std::system("sync && echo 3 > /proc/sys/vm/drop_caches");

	// Get current memory usage
	std::FILE *file = std::fopen("/proc/self/statm", "r");
	if (file == nullptr)
	{
		std::cerr << "Failed to open /proc/self/statm file" << std::endl;
		return 0;
	}

	size_t pages;
	std::fscanf(file, "%*s %zu", &pages);
	std::fclose(file);

	// Convert pages to bytes (assuming page size is 4096 bytes)
	return pages * 4096;
}

TEST(BoardTest, testMemFootprint)
{
	size_t initialMemory = getCurrentMemoryUsage();
	Board *board = Board::createStandardBoard();
	size_t finalMemory = getCurrentMemoryUsage();
	std::cout << "Memory usage: " << finalMemory - initialMemory << std::endl;
	ASSERT_LT(finalMemory - initialMemory, 1000000);
}
#endif

TEST(BoardTest, testFoolsMate)
{
	Board *board = Board::createStandardBoard();
	MoveTransition t1 = board->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		board,
		BoardUtils::getCoordinateAtPosition("f2"),
		BoardUtils::getCoordinateAtPosition("f3")));
	ASSERT_EQ(MoveStatus::DONE, t1.getMoveStatus());

	MoveTransition t2 = t1.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t1.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("e7"),
		BoardUtils::getCoordinateAtPosition("e5")));
	ASSERT_EQ(MoveStatus::DONE, t2.getMoveStatus());

	MoveTransition t3 = t2.getTransitionBoard()->getCurrentPlayer()->makeMove(MoveFactory::createMove(
		t2.getTransitionBoard(),
		BoardUtils::getCoordinateAtPosition("g2"),
		BoardUtils::getCoordinateAtPosition("g4")));
	ASSERT_EQ(MoveStatus::DONE, t3.getMoveStatus());

	MoveStrategy *strategy = new MiniMax(4);
	Move *aiMove = strategy->execute(t3.getTransitionBoard()),
		 *bestMove = MoveFactory::createMove(t3.getTransitionBoard(), BoardUtils::getCoordinateAtPosition("d8"), BoardUtils::getCoordinateAtPosition("h4"));
	ASSERT_TRUE(*aiMove == *bestMove);
}