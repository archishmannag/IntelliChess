/**
 * @file GuiUtils.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the GUI utilities
 * @version 1.0.0
 *
 */

#ifndef GUI_UTILS_HPP
#define GUI_UTILS_HPP

#include "PreCompiledHeaders.hpp"

#include "SFML/Graphics.hpp"

// Forward declarations
class move;

/**
 * @brief Various constants for the GUI
 *
 */
namespace
{
    int window_width = 960,
        window_height = 700,
        tile_width = 70,
        tile_height = 70,
        queen_offset = 0,
        knight_offset = 8,
        rook_offset = 16,
        bishop_offset = 24;
} // namespace

/**
 * @brief A class to keep track of the moves made
 *
 */
class move_log
{
public:
    std::vector<std::shared_ptr<move>> get_moves() const;
    int get_moves_count() const;
    void add_move(std::shared_ptr<move> m);
    std::shared_ptr<move> remove_move(int index);
    void remove_move(std::shared_ptr<move> m);
    void clear_moves();

private:
    std::vector<std::shared_ptr<move>> moves_; ///< The moves
};

/**
 * @brief The class for the hourglass animation
 *
 * @details The hourglass animation is used to indicate that the AI is thinking. It uses spritesheet for animation.
 *
 */
class hourglass
{
public:
    hourglass();
    void set_active(bool active);
    bool is_active() const;
    void draw(sf::RenderWindow &window);
    void update();

private:
    void update(sf::Vector2f position);

private:
    sf::Texture texture_;                          ///< The texture
    sf::IntRect rect_ = sf::IntRect(0, 0, 48, 48); ///< The rectangle for spritesheet
    sf::Sprite sprite_;                            ///< The sprite
    sf::Clock clock_;                              ///< The clock for animation
    bool active_ = false;
};

#endif // GUI_UTILS_HPP