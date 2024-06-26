/**
 * @file GameHistory.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the game history block
 * @version 1.0.0
 *
 */

#ifndef GAME_HISTORY_HPP
#define GAME_HISTORY_HPP

#include "PreCompiledHeaders.hpp"

#include "SFML/Graphics.hpp"

// Forward declarations
class board;
class move_log;

/**
 * @brief Represents one row in the game history block
 *
 */
class history_row
{
public:
    history_row(sf::Font &font);
    void set_position(sf::Vector2f position);
    void set_white_move(std::string move);
    void set_black_move(std::string move);
    sf::Vector2f get_position() const;
    std::string get_white_move();
    std::string get_black_move();
    void draw(sf::RenderWindow &window);

private:
    sf::Text white_move_, black_move_;       ///< The white and black move texts
    sf::RectangleShape bottom_divider_rect_; ///< The bottom divider rectangle (For seperating next row)
};

/**
 * @brief The game history block
 *
 */
class game_history_block
{
public:
    game_history_block();
    sf::View get_view() const;
    /**
     * @brief Scroll the game history block, if the mouse wheel is scrolled over it
     *
     * @details It takes the window size to find out the viewport dimensions as they are represented by SFML as fractions of the window size
     *
     * @param event The mouse wheel scroll event
     * @param window_size The window size
     */
    void mouse_wheel_scrolled(sf::Event::MouseWheelScrollEvent &event, sf::Vector2f window_size);
    /**
     * @brief Set whether the scroll bar is clicked or not
     *
     * @param event The mouse button event
     * @param button_clicked Whether the mouse button is down or up
     */
    void scroll_bar_scrolled(sf::Event::MouseButtonEvent &event, bool button_clicked);
    /**
     * @brief Scroll the game history block, if the scroll bar is clicked
     *
     * @param window
     */
    void scroll(sf::RenderWindow &window);
    /**
     * @brief Recalculate the game history block
     *
     * @param b The board
     * @param ml The move log
     */
    void redo(board *b, move_log &ml);
    void draw(sf::RenderWindow &window);

private:
    /**
     * @brief Update the location and size of the game history block
     *
     * @param window The SFML window
     */
    void update(sf::RenderWindow &window);
    /**
     * @brief After a scroll event, adjust the rows, scroll bar and its size and positions.
     *
     * @param window_size Window size for calculating the viewport dimensions
     */
    void update_scroll_percentage(sf::Vector2f window_size);

private:
    sf::Vector2f mouse_offset_;                                                  ///< The mouse offset from the scroll bar rectangle
    sf::RectangleShape game_history_area_rect_, scroll_bar_rect_, divider_rect_; ///< The various rectangles in the game history block
    std::vector<history_row> history_rows_;                                      ///< The history rows, each containing a white and black move (ply and reply)
    sf::Font font_;                                                              ///< The font for the text
    std::array<sf::Text, 2> player_names_;                                       ///< The player names (White and Black)
    sf::View view_;                                                              ///< The view for the game history block
    float scroll_percentage_top_ = 0.f,                                          ///< The position of top of the scroll bar in percentage
        scroll_percentage_bottom_ = 100.f;                                       ///< TThe position of bottom of the scroll bar in percentage
    bool scroll_bar_clicked_ = false;                                            ///< Whether the scroll bar is clicked or not
};

#endif // GAME_HISTORY_HPP