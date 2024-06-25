/**
 * @file Tile.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the tile class
 * @version 1.0.0
 *
 */

#ifndef TILE_HPP
#define TILE_HPP

#include "PreCompiledHeaders.hpp"

// Forward declarations
class piece;
class empty_tile;

/**
 * @brief Polymorphic class representing a tile on the board. It can be empty or occupied by a piece.
 *
 */
class tile
{
public:
    /**
     * @brief Create a tile (empty or occupied)
     *
     * @param c The tile coordinate
     * @param p The piece on the tile (nullptr by default)
     * @return Pointer to the tile created
     */
    static std::shared_ptr<tile> create_tile(int c, std::shared_ptr<piece> p = nullptr);
    int get_tile_coordinate() const;
    virtual bool is_tile_occupied() const;
    virtual std::shared_ptr<piece> get_piece_on_tile() const;
    /**
     * @brief String representation of the tile
     *
     * @return std::string
     */
    virtual std::string stringify() const;

protected: // Ctor
    /**
     * @brief Construct a new tile
     *
     * @param c The tile coordinate
     */
    tile(int c);

protected:
    const int tile_coordinate_; ///< The tile coordinate

private:
    /**
     * @brief Create cache of empty tiles
     *
     * @return Unordered map of the empty tiles
     */
    static std::unordered_map<int, std::shared_ptr<empty_tile>> initialize_all_empty_tiles();

private:
    static std::unordered_map<int, std::shared_ptr<empty_tile>> empty_tiles_cache; ///< Cache of empty tiles
};

/**
 * @brief Class representing an empty tile
 *
 */
class empty_tile final : public tile
{
public:
    /**
     * @brief Construct a new empty tile
     *
     * @param c The tile coordinate
     */
    empty_tile(int c);
    bool is_tile_occupied() const override;
    std::shared_ptr<piece> get_piece_on_tile() const override;
    /**
     * @brief String representation of the tile
     *
     * @return std::string
     */
    std::string stringify() const override;
};

/**
 * @brief Class representing an occupied tile
 *
 */
class occupied_tile final : public tile
{
public:
    /**
     * @brief Construct a new occupied tile
     *
     * @param c The tile coordinate
     * @param p The piece on the tile
     */
    occupied_tile(int c, std::shared_ptr<piece> p);
    bool is_tile_occupied() const override;
    std::shared_ptr<piece> get_piece_on_tile() const override;
    /**
     * @brief String representation of the tile
     *
     * @return std::string
     */
    std::string stringify() const override;

private:
    std::shared_ptr<piece> piece_on_tile_; ///< The piece on the tile
};

#endif // TILE_HPP