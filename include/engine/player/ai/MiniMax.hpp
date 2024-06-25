/**
 * @file MiniMax.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the mini max algorithm
 * @version 1.0.0
 * @deprecated This class is deprecated and is replaced by the alpha beta pruning algorithm
 *
 */

#ifndef MINI_MAX_HPP
#define MINI_MAX_HPP

#include "PreCompiledHeaders.hpp"

#include "engine/player/ai/MoveStrategy.hpp"

// Forward declarations
class move;
class board;

/**
 * @brief The mini max algorithm
 *
 */
class mini_max final : public move_strategy
{
public:
    mini_max(unsigned int sd);
    std::shared_ptr<move> execute(std::shared_ptr<board> b) override;

private:
    int min(std::shared_ptr<board> b, unsigned int d);
    int max(std::shared_ptr<board> b, unsigned int d);

private:
    unsigned const search_depth_; ///< The search depth
};

#endif // MINI_MAX_HPP