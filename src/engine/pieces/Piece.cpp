/**
 * @file Piece.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the piece class
 * @version 1.0.0
 *
 */

#include "engine/pieces/Piece.hpp"

piece::piece(const int pp, const alliance pa, const piece_type pt, bool fm)
    : piece_position_(pp),
      piece_alliance_(pa),
      first_move_(fm),
      piece_type_(pt){};

bool piece::operator==(const piece &other)
{
    if (this == &other)
        return true;
    else
        return piece_position_ == other.get_piece_position() &&
               piece_alliance_ == other.get_piece_alliance() &&
               piece_type_ == other.get_piece_type() &&
               first_move_ == other.is_first_move();
}

std::vector<std::shared_ptr<move>> piece::calculate_legal_moves(std::shared_ptr<board> b)
{
    throw std::logic_error("This method must be overridden by a subclass.");
}

std::shared_ptr<piece> piece::move_piece(const move *const m) const
{
    throw std::logic_error("This method must be overridden by a subclass.");
}

int piece::get_piece_position() const
{
    return piece_position_;
}

alliance piece::get_piece_alliance() const
{
    return piece_alliance_;
}

bool piece::is_first_move() const
{
    return first_move_;
}

piece_type piece::get_piece_type() const
{
    return piece_type_;
}

int piece::get_piece_value() const
{
    switch (piece_type_)
    {
    case piece_type::pawn:
        return 100;
        break;
    case piece_type::knight:
    case piece_type::bishop:
        return 300;
        break;
    case piece_type::rook:
        return 500;
        break;
    case piece_type::queen:
        return 900;
        break;
    case piece_type::king:
        return 10000;
        break;
    default:
        throw std::runtime_error("Invalid piece type");
    }
}

std::string piece::stringify() const
{
    std::string type_string = "";
    switch (piece_type_)
    {
    case piece_type::pawn:
        type_string += "P";
        break;
    case piece_type::knight:
        type_string += "N";
        break;
    case piece_type::bishop:
        type_string += "B";
        break;
    case piece_type::rook:
        type_string += "R";
        break;
    case piece_type::queen:
        type_string += "Q";
        break;
    case piece_type::king:
        type_string += "K";
        break;
    }
    return type_string;
}