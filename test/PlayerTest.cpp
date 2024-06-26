/**
 * @file PlayerTest.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @version 1.0.0
 *
 */

#include <gtest/gtest.h>
#include <PreCompiledHeaders.hpp>

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
    std::shared_ptr<board> b = board::create_standard_board();
    move_transition t1 = b->get_current_player()->make_move(move_factory::create_move(b, board_utils::get_coordinate_at_position("e2"), board_utils::get_coordinate_at_position("e4"))),
                    t2 = t1.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t1.get_transition_board(), board_utils::get_coordinate_at_position("e7"), board_utils::get_coordinate_at_position("e5")));
    ASSERT_EQ(move_status::done, t1.get_move_status());
    ASSERT_EQ(move_status::done, t2.get_move_status());
}

TEST(PlayerTest, testBug)
{
    std::shared_ptr<board> b = board::create_standard_board();
    move_transition t1 = b->get_current_player()->make_move(move_factory::create_move(b, board_utils::get_coordinate_at_position("c2"), board_utils::get_coordinate_at_position("c3")));
    ASSERT_EQ(move_status::done, t1.get_move_status());

    move_transition t2 = t1.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t1.get_transition_board(), board_utils::get_coordinate_at_position("b8"), board_utils::get_coordinate_at_position("a6")));
    ASSERT_EQ(move_status::done, t2.get_move_status());

    move_transition t3 = t2.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t2.get_transition_board(), board_utils::get_coordinate_at_position("d1"), board_utils::get_coordinate_at_position("a4")));
    ASSERT_EQ(move_status::done, t3.get_move_status());

    move_transition t4 = t3.get_transition_board()->get_current_player()->make_move(move_factory::create_move(t3.get_transition_board(), board_utils::get_coordinate_at_position("d7"), board_utils::get_coordinate_at_position("d6")));
    ASSERT_NE(move_status::done, t4.get_move_status());
}

TEST(PlayerTest, testDiscoveredCheck)
{
    board_builder builder;
    // Black Layout
    builder.set_piece(std::make_shared<king>(4, alliance::black));
    builder.set_piece(std::make_shared<rook>(24, alliance::black));
    // White Layout
    builder.set_piece(std::make_shared<bishop>(44, alliance::white));
    builder.set_piece(std::make_shared<rook>(52, alliance::white));
    builder.set_piece(std::make_shared<king>(58, alliance::white));

    builder.set_move_maker(alliance::white);
    std::shared_ptr<board> b = builder.build();
}