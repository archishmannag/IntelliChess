/**
 * @file BoardTest.cpp
 * @author your name (you@domain.com)
 * @version 1.0.0
 *
 */

#include <gtest/gtest.h>
#include <PreCompiledHeaders.hpp>

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
    std::shared_ptr<board> b = board::create_standard_board();
    EXPECT_EQ(20, b->get_current_player()->get_legal_moves().size());
    EXPECT_EQ(20, b->get_current_player()->get_opponent().lock()->get_legal_moves().size());

    ASSERT_FALSE(b->get_current_player()->is_in_check());
    ASSERT_FALSE(b->get_current_player()->is_is_checkmate());
    ASSERT_FALSE(b->get_current_player()->is_castled());

    ASSERT_FALSE(b->get_current_player()->get_opponent().lock()->is_in_check());
    ASSERT_FALSE(b->get_current_player()->get_opponent().lock()->is_is_checkmate());
    ASSERT_FALSE(b->get_current_player()->get_opponent().lock()->is_castled());

    ASSERT_EQ(b->get_current_player(), b->get_white_player());
    ASSERT_EQ(b->get_current_player()->get_opponent().lock(), b->get_black_player());

    ASSERT_STREQ("White", alliance_utils::stringify(b->get_current_player()->get_player_alliance()).c_str());
    ASSERT_STREQ("Black", alliance_utils::stringify(b->get_current_player()->get_opponent().lock()->get_player_alliance()).c_str());

    std::vector<std::shared_ptr<piece>> all_pieces = b->get_white_pieces(),
                                        black_pieces = b->get_black_pieces();
    all_pieces.insert(all_pieces.end(), black_pieces.begin(), black_pieces.end());
    std::vector<std::shared_ptr<move>> all_moves = b->get_all_legal_moves();
    for (auto m : all_moves)
    {
        ASSERT_FALSE(m->is_attack_move());
        ASSERT_FALSE(m->is_castling_move());
    }

    ASSERT_EQ(32, all_pieces.size());
    ASSERT_EQ(40, all_moves.size());
    ASSERT_EQ(nullptr, b->get_tile(35)->get_piece_on_tile());
}

TEST(BoardTest, testPlainKingMove)
{
    board_builder builder;
    // Black Layout
    builder.set_piece(std::make_shared<king>(4, alliance::black));
    builder.set_piece(std::make_shared<pawn>(12, alliance::black));
    // White Layout
    builder.set_piece(std::make_shared<pawn>(52, alliance::white));
    builder.set_piece(std::make_shared<king>(60, alliance::white));
    builder.set_move_maker(alliance::white);
    std::shared_ptr<board> b = builder.build();

    ASSERT_EQ(6, b->get_white_player()->get_legal_moves().size());
    ASSERT_EQ(6, b->get_black_player()->get_legal_moves().size());
    ASSERT_FALSE(b->get_white_player()->is_in_check());
    ASSERT_FALSE(b->get_white_player()->is_is_checkmate());
    ASSERT_FALSE(b->get_white_player()->is_castled());
    ASSERT_FALSE(b->get_black_player()->is_in_check());
    ASSERT_FALSE(b->get_black_player()->is_is_checkmate());
    ASSERT_FALSE(b->get_black_player()->is_castled());
    ASSERT_EQ(b->get_white_player(), b->get_current_player());
    ASSERT_EQ(b->get_black_player(), b->get_white_player()->get_opponent().lock());

    auto m = move_factory::create_move(
        b,
        board_utils::get_coordinate_at_position("e1"),
        board_utils::get_coordinate_at_position("f1"));
    auto transition = b->get_current_player()->make_move(m);
    ASSERT_EQ(m, transition.get_move());
    ASSERT_EQ(transition.get_transition_board()->get_current_player(), transition.get_transition_board()->get_black_player());
    ASSERT_TRUE(transition.get_move_status() == move_status::done);
    ASSERT_EQ(61, transition.get_transition_board()->get_white_player()->get_player_king()->get_piece_position());
}

TEST(BoardTest, testAlgebraicNotation)
{
    ASSERT_STREQ("a8", board_utils::get_position_at_coordinate(0).c_str());
    ASSERT_STREQ("b8", board_utils::get_position_at_coordinate(1).c_str());
    ASSERT_STREQ("c8", board_utils::get_position_at_coordinate(2).c_str());
    ASSERT_STREQ("d8", board_utils::get_position_at_coordinate(3).c_str());
    ASSERT_STREQ("e8", board_utils::get_position_at_coordinate(4).c_str());
    ASSERT_STREQ("f8", board_utils::get_position_at_coordinate(5).c_str());
    ASSERT_STREQ("g8", board_utils::get_position_at_coordinate(6).c_str());
    ASSERT_STREQ("h8", board_utils::get_position_at_coordinate(7).c_str());
    ASSERT_STREQ("a1", board_utils::get_position_at_coordinate(56).c_str());
    ASSERT_STREQ("b1", board_utils::get_position_at_coordinate(57).c_str());
    ASSERT_STREQ("c1", board_utils::get_position_at_coordinate(58).c_str());
    ASSERT_STREQ("d1", board_utils::get_position_at_coordinate(59).c_str());
    ASSERT_STREQ("e1", board_utils::get_position_at_coordinate(60).c_str());
    ASSERT_STREQ("f1", board_utils::get_position_at_coordinate(61).c_str());
    ASSERT_STREQ("g1", board_utils::get_position_at_coordinate(62).c_str());
    ASSERT_STREQ("h1", board_utils::get_position_at_coordinate(63).c_str());
}

TEST(BoardTest, testInvalidBoard)
{
    board_builder builder;
    // Black Layout
    builder.set_piece(std::make_shared<rook>(0, alliance::black));
    builder.set_piece(std::make_shared<knight>(1, alliance::black));
    builder.set_piece(std::make_shared<bishop>(2, alliance::black));
    builder.set_piece(std::make_shared<queen>(3, alliance::black));
    builder.set_piece(std::make_shared<bishop>(5, alliance::black));
    builder.set_piece(std::make_shared<knight>(6, alliance::black));
    builder.set_piece(std::make_shared<rook>(7, alliance::black));
    builder.set_piece(std::make_shared<pawn>(8, alliance::black));
    builder.set_piece(std::make_shared<pawn>(9, alliance::black));
    builder.set_piece(std::make_shared<pawn>(10, alliance::black));
    builder.set_piece(std::make_shared<pawn>(11, alliance::black));
    builder.set_piece(std::make_shared<pawn>(12, alliance::black));
    builder.set_piece(std::make_shared<pawn>(13, alliance::black));
    builder.set_piece(std::make_shared<pawn>(14, alliance::black));
    builder.set_piece(std::make_shared<pawn>(15, alliance::black));
    // White Layout
    builder.set_piece(std::make_shared<pawn>(48, alliance::white));
    builder.set_piece(std::make_shared<pawn>(49, alliance::white));
    builder.set_piece(std::make_shared<pawn>(50, alliance::white));
    builder.set_piece(std::make_shared<pawn>(51, alliance::white));
    builder.set_piece(std::make_shared<pawn>(52, alliance::white));
    builder.set_piece(std::make_shared<pawn>(53, alliance::white));
    builder.set_piece(std::make_shared<pawn>(54, alliance::white));
    builder.set_piece(std::make_shared<pawn>(55, alliance::white));
    builder.set_piece(std::make_shared<rook>(56, alliance::white));
    builder.set_piece(std::make_shared<knight>(57, alliance::white));
    builder.set_piece(std::make_shared<bishop>(58, alliance::white));
    builder.set_piece(std::make_shared<queen>(59, alliance::white));
    builder.set_piece(std::make_shared<bishop>(61, alliance::white));
    builder.set_piece(std::make_shared<knight>(62, alliance::white));
    builder.set_piece(std::make_shared<rook>(63, alliance::white));
    builder.set_move_maker(alliance::white);

    ASSERT_THROW(builder.build(), std::runtime_error);
}

int calculatedActivesFor(std::shared_ptr<board> b, alliance a)
{
    int count = 0;
    for (auto piece : b->get_all_pieces())
    {
        if (piece->get_piece_alliance() == a)
        {
            count++;
        }
    }
    return count;
}

TEST(BoardTest, testBoardConsistency)
{
    std::shared_ptr<board> b = board::create_standard_board();
    ASSERT_EQ(b->get_white_player(), b->get_current_player());

    move_transition t1 = b->get_current_player()->make_move(move_factory::create_move(
        b,
        board_utils::get_coordinate_at_position("e2"),
        board_utils::get_coordinate_at_position("e4")));

    move_transition t2 = t1.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t1.get_transition_board(),
        board_utils::get_coordinate_at_position("e7"),
        board_utils::get_coordinate_at_position("e5")));

    move_transition t3 = t2.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t2.get_transition_board(),
        board_utils::get_coordinate_at_position("g1"),
        board_utils::get_coordinate_at_position("f3")));

    move_transition t4 = t3.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t3.get_transition_board(),
        board_utils::get_coordinate_at_position("d7"),
        board_utils::get_coordinate_at_position("d5")));

    move_transition t5 = t4.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t4.get_transition_board(),
        board_utils::get_coordinate_at_position("e4"),
        board_utils::get_coordinate_at_position("d5")));

    move_transition t6 = t5.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t5.get_transition_board(),
        board_utils::get_coordinate_at_position("d8"),
        board_utils::get_coordinate_at_position("d5")));

    move_transition t7 = t6.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t6.get_transition_board(),
        board_utils::get_coordinate_at_position("f3"),
        board_utils::get_coordinate_at_position("g5")));

    move_transition t8 = t7.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t7.get_transition_board(),
        board_utils::get_coordinate_at_position("f7"),
        board_utils::get_coordinate_at_position("f6")));

    move_transition t9 = t8.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t8.get_transition_board(),
        board_utils::get_coordinate_at_position("d1"),
        board_utils::get_coordinate_at_position("h5")));

    move_transition t10 = t9.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t9.get_transition_board(),
        board_utils::get_coordinate_at_position("g7"),
        board_utils::get_coordinate_at_position("g6")));

    move_transition t11 = t10.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t10.get_transition_board(),
        board_utils::get_coordinate_at_position("h5"),
        board_utils::get_coordinate_at_position("h4")));

    move_transition t12 = t11.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t11.get_transition_board(),
        board_utils::get_coordinate_at_position("f6"),
        board_utils::get_coordinate_at_position("g5")));

    move_transition t13 = t12.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t12.get_transition_board(),
        board_utils::get_coordinate_at_position("h4"),
        board_utils::get_coordinate_at_position("g5")));

    move_transition t14 = t13.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t13.get_transition_board(),
        board_utils::get_coordinate_at_position("d5"),
        board_utils::get_coordinate_at_position("e4")));

    ASSERT_TRUE(t14.get_transition_board()->get_white_player()->is_in_check());
    ASSERT_TRUE(t14.get_transition_board()->get_white_player()->get_active_pieces().size() == calculatedActivesFor(t14.get_transition_board(), alliance::white));
    ASSERT_TRUE(t14.get_transition_board()->get_black_player()->get_active_pieces().size() == calculatedActivesFor(t14.get_transition_board(), alliance::black));
}

TEST(BoardTest, testFoolsMate)
{
    std::shared_ptr<board> b = board::create_standard_board();
    move_transition t1 = b->get_current_player()->make_move(move_factory::create_move(
        b,
        board_utils::get_coordinate_at_position("f2"),
        board_utils::get_coordinate_at_position("f3")));
    ASSERT_EQ(move_status::done, t1.get_move_status());

    move_transition t2 = t1.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t1.get_transition_board(),
        board_utils::get_coordinate_at_position("e7"),
        board_utils::get_coordinate_at_position("e5")));
    ASSERT_EQ(move_status::done, t2.get_move_status());

    move_transition t3 = t2.get_transition_board()->get_current_player()->make_move(move_factory::create_move(
        t2.get_transition_board(),
        board_utils::get_coordinate_at_position("g2"),
        board_utils::get_coordinate_at_position("g4")));
    ASSERT_EQ(move_status::done, t3.get_move_status());

    std::shared_ptr<move_strategy> strategy = std::make_shared<mini_max>(4);
    std::shared_ptr<move> ai_move = strategy->execute(t3.get_transition_board()),
                          best_move = move_factory::create_move(t3.get_transition_board(), board_utils::get_coordinate_at_position("d8"), board_utils::get_coordinate_at_position("h4"));
    ASSERT_TRUE(*ai_move == *best_move);
}