#include <gtest/gtest.h>
#include <vector>
#include <memory>
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
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<queen>(36, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(), black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(31, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e8"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("a4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("b4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("c4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("d4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("f4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("g4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("h4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testLegalMoveAllAvailable)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	builder.set_piece(std::make_shared<knight>(28, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<knight>(36, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves();
	ASSERT_EQ(13, white_legal_moves.size());

	std::shared_ptr<move> wm1 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("d6")),
						  wm2 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("f6")),
						  wm3 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("c5")),
						  wm4 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("g5")),
						  wm5 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("c3")),
						  wm6 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("g3")),
						  wm7 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("d2")),
						  wm8 = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("f2"));

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm1](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm1; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm2](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm2; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm3](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm3; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm4](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm4; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm5](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm5; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm6](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm6; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm7](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm7; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm8](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm8; }) != white_legal_moves.end());

	board_builder builder2;
	// Black Layout
	builder2.set_piece(std::make_shared<king>(4, alliance::black));
	builder2.set_piece(std::make_shared<knight>(28, alliance::black));
	// White Layout
	builder2.set_piece(std::make_shared<knight>(36, alliance::white));
	builder2.set_piece(std::make_shared<king>(60, alliance::white));
	builder2.set_move_maker(alliance::black);
	std::shared_ptr<board> board2 = builder2.build();
	std::vector<std::shared_ptr<move>> black_legal_moves = board2->get_black_player()->get_legal_moves();
	ASSERT_EQ(13, black_legal_moves.size());

	std::shared_ptr<move> bm1 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("d7")),
						  bm2 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("f7")),
						  bm3 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("c6")),
						  bm4 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("g6")),
						  bm5 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("c4")),
						  bm6 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("g4")),
						  bm7 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("d3")),
						  bm8 = move_factory::create_move(board2, board_utils::get_coordinate_at_position("e5"), board_utils::get_coordinate_at_position("f3"));

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm1](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm1; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm2](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm2; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm3](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm3; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm4](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm4; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm5](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm5; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm6](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm6; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm7](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm7; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm8](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm8; }) != black_legal_moves.end());
}

TEST(PieceTest, testKnightInCorners)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	builder.set_piece(std::make_shared<knight>(0, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<knight>(56, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(7, white_legal_moves.size());
	ASSERT_EQ(7, black_legal_moves.size());

	std::shared_ptr<move> wm1 = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("b3")),
						  wm2 = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("c2")),
						  bm1 = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("b6")),
						  bm2 = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("c7"));

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm1](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm1; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[wm2](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *wm2; }) != white_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm1](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm1; }) != black_legal_moves.end());

	ASSERT_TRUE(std::find_if(
					black_legal_moves.begin(),
					black_legal_moves.end(),
					[bm2](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *bm2; }) != black_legal_moves.end());
}

TEST(PieceTest, testMiddleBishopOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<bishop>(35, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(18, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("a7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("b6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("c5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("e3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("f2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("g1"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("a1"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());

	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("d4"), board_utils::get_coordinate_at_position("b2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testTopLeftBishopOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<bishop>(0, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);

	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(b->get_tile(0)->get_piece(), b->get_tile(0)->get_piece());
	ASSERT_NE(nullptr, b->get_tile(0)->get_piece());

	ASSERT_EQ(12, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("b7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("c6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("d5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("e4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("f3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("g2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a8"), board_utils::get_coordinate_at_position("h1"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testTopRightBishopOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<bishop>(7, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);

	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(b->get_tile(7)->get_piece(), b->get_tile(7)->get_piece());
	ASSERT_NE(nullptr, b->get_tile(7)->get_piece());

	ASSERT_EQ(12, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("g7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("f6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("e5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("d4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("c3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("b2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h8"), board_utils::get_coordinate_at_position("a1"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testBottomLeftBishopOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<bishop>(56, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);

	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(b->get_tile(56)->get_piece(), b->get_tile(56)->get_piece());
	ASSERT_NE(nullptr, b->get_tile(56)->get_piece());

	ASSERT_EQ(12, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("b2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("c3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("d4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("e5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("f6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("g7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("a1"), board_utils::get_coordinate_at_position("h8"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testBottomRightBishopOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<bishop>(63, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);

	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(b->get_tile(63)->get_piece(), b->get_tile(63)->get_piece());
	ASSERT_NE(nullptr, b->get_tile(63)->get_piece());

	ASSERT_EQ(12, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("g2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("f3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("e4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("d5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("c6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("b7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("h1"), board_utils::get_coordinate_at_position("a8"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testMiddleRookOnEmptyBoard)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(4, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<rook>(36, alliance::white));
	builder.set_piece(std::make_shared<king>(60, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();
	std::vector<std::shared_ptr<move>> white_legal_moves = b->get_white_player()->get_legal_moves(),
									   black_legal_moves = b->get_black_player()->get_legal_moves();

	ASSERT_EQ(18, white_legal_moves.size());
	ASSERT_EQ(5, black_legal_moves.size());

	std::shared_ptr<move> m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e8"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e7"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e6"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e5"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e3"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("e2"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("a4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("b4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("c4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("d4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("f4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("g4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
	m = move_factory::create_move(b, board_utils::get_coordinate_at_position("e4"), board_utils::get_coordinate_at_position("h4"));
	ASSERT_TRUE(std::find_if(
					white_legal_moves.begin(),
					white_legal_moves.end(),
					[m](std::shared_ptr<move> legal_move) -> bool
					{ return *legal_move == *m; }) != white_legal_moves.end());
}

TEST(PieceTest, testPawnPromotion)
{
	board_builder builder;
	// Black Layout
	builder.set_piece(std::make_shared<king>(22, alliance::black));
	builder.set_piece(std::make_shared<rook>(3, alliance::black));
	// White Layout
	builder.set_piece(std::make_shared<pawn>(15, alliance::white));
	builder.set_piece(std::make_shared<king>(52, alliance::white));
	builder.set_move_maker(alliance::white);
	std::shared_ptr<board> b = builder.build();

	move_transition t1 = b->get_current_player()->make_move(move_factory::create_move(b, board_utils::get_coordinate_at_position("h7"), board_utils::get_coordinate_at_position("h8")));
	ASSERT_EQ(move_status::done, t1.get_move_status());

	move_transition t2 = t1.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t1.get_transition_board(), board_utils::get_coordinate_at_position("d8"), board_utils::get_coordinate_at_position("h8")));
	ASSERT_EQ(move_status::done, t2.get_move_status());

	move_transition t3 = t2.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t2.get_transition_board(), board_utils::get_coordinate_at_position("e2"), board_utils::get_coordinate_at_position("d2")));
	ASSERT_EQ(move_status::done, t3.get_move_status());
}

TEST(PieceTest, testKingEquality)
{
	std::shared_ptr<board> b = board::create_standard_board(),
						   board2 = board::create_standard_board();

	ASSERT_TRUE(*b->get_tile(60)->get_piece() == *board2->get_tile(60)->get_piece());
	ASSERT_FALSE(b->get_tile(60)->get_piece() == nullptr);
}