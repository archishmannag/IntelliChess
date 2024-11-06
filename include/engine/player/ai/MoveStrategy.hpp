/**
 * @file MoveStrategy.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the move strategy interface
 * @version 1.1.0
 *
 */

#ifndef MOVE_STRATEGY_HPP
#define MOVE_STRATEGY_HPP

// Forward declarations
class move;
class board;

class move_strategy
{
public:
    virtual std::shared_ptr<move> execute(std::shared_ptr<board> b) = 0;
};

#endif // MOVE_STRATEGY_HPP