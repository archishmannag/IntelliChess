/**
 * @file MoveTransition.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the move transition class
 * @version 1.0.0
 *
 */

#ifndef MOVE_TRANSITION_HPP
#define MOVE_TRANSITION_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class move;
class board;
enum class move_status;

/**
 * @brief Class representing a transition to a new board after a move's execution
 *
 * @details This class is used for storing whether a move is successful, illegal, or leaves the player in check.
 *
 */
class move_transition
{
public:
    /**
     * @brief Construct a new move transition
     *
     * @param tb The new board after the move
     * @param m The move executed
     * @param ms The move status
     */
    move_transition(std::shared_ptr<board> tb, std::shared_ptr<move> m, move_status ms);

public: // Getters
    move_status get_move_status() const;
    std::shared_ptr<move> get_move() const;
    std::shared_ptr<board> get_transition_board() const;

private:
    std::shared_ptr<board> transition_board_; ///< The new board after the move
    std::shared_ptr<move> move_;              ///< The move executed
    move_status move_status_;                 ///< The move status
};
#endif // MOVE_TRANSITION_HPP