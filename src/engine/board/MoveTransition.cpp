/**
 * @file MoveTransition.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the move transition class
 * @version 1.0.0
 *
 */

#include "engine/board/Board.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/MoveTransition.hpp"

move_transition::move_transition(std::shared_ptr<board> tb, std::shared_ptr<move> m, move_status ms)
    : transition_board_(tb),
      move_(m),
      move_status_(ms) {}

move_status move_transition::get_move_status() const
{
    return this->move_status_;
}

std::shared_ptr<move> move_transition::get_move() const
{
    return this->move_;
}

std::shared_ptr<board> move_transition::get_transition_board() const
{
    return this->transition_board_;
}