/**
 * @file Tile.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the tile class
 * @version 1.0.0
 *
 */

#include "engine/board/Tile.hpp"
#include "engine/Alliance.hpp"
#include "engine/pieces/Piece.hpp"

/* tile */

tile::tile(int c)
    : tile_coordinate_(c){};

std::unordered_map<int, std::shared_ptr<empty_tile>> tile::initialize_all_empty_tiles()
{
    std::unordered_map<int, std::shared_ptr<empty_tile>> empty_tile_map;

    for (int i = 0; i < 64; i++)
        empty_tile_map.insert(std::pair<int, std::shared_ptr<empty_tile>>(i, std::make_shared<empty_tile>(i)));

    return empty_tile_map;
}

std::unordered_map<int, std::shared_ptr<empty_tile>> tile::empty_tiles_cache = tile::initialize_all_empty_tiles();

std::shared_ptr<tile> tile::create_tile(int c, std::shared_ptr<piece> p)
{
    if (p == nullptr)
        return (tile::empty_tiles_cache.at(c));
    else
        return std::make_shared<occupied_tile>(c, p);
}

int tile::get_tile_coordinate() const
{
    return tile_coordinate_;
}

bool tile::is_tile_occupied() const
{
    throw std::logic_error("Use derived class functions.");
};

std::shared_ptr<piece> tile::get_piece_on_tile() const
{
    throw std::logic_error("Use derived class functions.");
};

std::string tile::stringify() const
{
    throw std::logic_error("Use derived class functions.");
};

/* empty_tile */

empty_tile::empty_tile(const int c)
    : tile(c){};

bool empty_tile::is_tile_occupied() const
{
    return false;
}

std::shared_ptr<piece> empty_tile::get_piece_on_tile() const
{
    return nullptr;
}

std::string empty_tile::stringify() const
{
    return "-";
}

/* occupied_tile */

occupied_tile::occupied_tile(int c, std::shared_ptr<piece> p)
    : tile(c),
      piece_on_tile_(p){};

bool occupied_tile::is_tile_occupied() const
{
    return true;
}

std::shared_ptr<piece> occupied_tile::get_piece_on_tile() const
{
    return piece_on_tile_;
}

std::string occupied_tile::stringify() const
{
    // If the piece is black, convert the string to lowercase
    if (alliance_utils::is_black(get_piece_on_tile()->get_piece_alliance()))
    {
        std::string str = get_piece_on_tile()->stringify();
        for (char &c : str)
            c = std::tolower(c);
        return str;
    }
    else
        return get_piece_on_tile()->stringify();
}