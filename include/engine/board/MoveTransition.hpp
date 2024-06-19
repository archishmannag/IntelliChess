#ifndef MOVE_TRANSITION_HPP
#define MOVE_TRANSITION_HPP

#include <PreCompiledHeaders.hpp>

class move;
class board;
enum class move_status;

class move_transition
{
public:
	move_transition(std::shared_ptr<board> tb, std::shared_ptr<move> m, move_status ms);
	move_status get_move_status() const;
	std::shared_ptr<move> get_move() const;
	std::shared_ptr<board> get_transition_board() const;

private:
	std::shared_ptr<board> transition_board_;
	std::shared_ptr<move> move_;
	move_status move_status_;
};
#endif // MOVE_TRANSITION_HPP