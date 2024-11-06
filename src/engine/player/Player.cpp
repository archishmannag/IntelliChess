/**
 * @file Player.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the player class
 * @version 1.1.0
 *
 */

#include "engine/player/Player.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/Move.hpp"
#include "engine/board/MoveTransition.hpp"
#include "engine/pieces/King.hpp"
#include "engine/pieces/Piece.hpp"

player::player(std::shared_ptr<board> b)
    : board_(b)
{
}

std::shared_ptr<king> player::establish_king()
{
    for (std::shared_ptr<piece> p : get_active_pieces())
        if (p->get_piece_type() == piece_type::king)
            return std::dynamic_pointer_cast<king>(p);

    throw std::runtime_error("No king found for player!");
}

bool player::has_escape_coves() const
{
    for (std::shared_ptr<move> m : legal_moves_)
    {
        move_transition transition = make_move(m);
        if (transition.get_move_status() == move_status::done)
            return true;
    }
    return false;
}

std::vector<std::shared_ptr<move> > player::calculate_attacks_on_tile(const int tc, std::vector<std::shared_ptr<move> > ol)
{
    std::vector<std::shared_ptr<move> > attack_moves;

    for (std::shared_ptr<move> m : ol)
        if (tc == m->get_destination_coordinate())
            attack_moves.push_back(m);
    return attack_moves;
}

bool player::is_move_legal(const move *m) const
{
    return std::find_if(legal_moves_.begin(), legal_moves_.end(), [m](std::shared_ptr<move> legal_move) -> bool
                        { return *legal_move == *m; })
           != legal_moves_.end();
}

std::shared_ptr<king> player::get_player_king() const
{
    return player_king_;
}

const std::vector<std::shared_ptr<move> > &player::get_legal_moves() const
{
    return legal_moves_;
}

bool player::fifty_move_rule() const
{
    return board_.lock()->get_half_move_clock() >= 100;
}

bool player::is_in_check() const
{
    return checked_;
}

bool player::is_is_checkmate() const
{
    return checked_ && !has_escape_coves();
}

bool player::is_in_stalemate() const
{
    return fifty_move_rule() || (!checked_ && !has_escape_coves());
}

bool player::is_castled() const
{
    return player_king_->is_castled();
}

bool player::is_castle_capable() const
{
    return player_king_->is_king_side_castle_capable() || player_king_->is_queen_side_castle_capable();
}

bool player::is_king_side_castle_capable() const
{
    return player_king_->is_king_side_castle_capable();
}

bool player::is_queen_side_castle_capable() const
{
    return player_king_->is_queen_side_castle_capable();
}

move_transition player::make_move(std::shared_ptr<move> m) const
{
    if (!is_move_legal(m.get()))
        return move_transition(board_.lock(), m, move_status::illegal_move);
    std::shared_ptr<board> transition_board = m->execute();
    std::vector<std::shared_ptr<move> > king_attacks = player::calculate_attacks_on_tile(transition_board->get_current_player()->get_opponent().lock()->get_player_king()->get_piece_position(), transition_board->get_current_player()->get_legal_moves());
    if (!king_attacks.empty())
        return move_transition(board_.lock(), m, move_status::leaves_player_in_check);
    return move_transition(transition_board, m, move_status::done);
}

move_transition player::unmake_move(std::shared_ptr<move> m) const
{
    return move_transition(m->undo(), m, move_status::done);
}

std::vector<std::shared_ptr<piece> > player::get_active_pieces() const
{
    throw std::logic_error("This must be overridden");
}

alliance player::get_player_alliance() const
{
    throw std::logic_error("This function must be overridden!");
}

std::weak_ptr<player> player::get_opponent() const
{
    throw std::logic_error("This function must be overridden!");
}

std::vector<std::shared_ptr<move> > player::calculate_king_castles(const std::vector<std::shared_ptr<move> > &ol) const
{
    throw std::logic_error("This function must be overridden!");
}

std::string player::stringify() const
{
    throw std::logic_error("This function must be overridden!");
}