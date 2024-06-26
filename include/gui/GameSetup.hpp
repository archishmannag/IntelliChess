/**
 * @file GameSetup.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the game setup class
 * @version
 *
 */

#ifndef GAME_SETUP_HPP
#define GAME_SETUP_HPP

#include "PreCompiledHeaders.hpp"

#include "SFML/Graphics.hpp"

// Forward declarations
class player;
class game_board;

/**
 * @brief The type of player in the game
 *
 */
enum class player_type
{
    human,
    computer
};

/**
 * @brief Convert a player type to a string
 *
 * @param player The player type
 * @return std::string - The string representation
 */
std::string to_string(player_type player);

/**
 * @brief The game setup dialog
 *
 */
class game_setup
{
public:
    /**
     * @brief Construct a new game setup dialog
     *
     * @param notify_parent Th callback to call when the setup dialog is accepted
     */
    game_setup(std::function<void()> notify_parent);
    void update(sf::Event event, sf::Vector2i mouse_position);
    void draw(sf::RenderWindow &window);
    void set_active(bool active);

    bool get_active() const;
    bool is_AI_player(player *p) const;
    player_type get_white_player_type() const;
    player_type get_black_player_type() const;
    unsigned int get_search_depth() const;

private:
    void update_locations(sf::Vector2u window_size);

private:
    player_type white_player_ = player_type::human, ///< The white player type
        black_player_ = player_type::human;         ///< The black player type
    int depth_,                                     ///< The search depth
        cursor_position_ = 1;                       ///< The cursor position

    sf::RectangleShape game_setup_rect_; ///< The game setup rectangle
    sf::Font font_;                      ///< The font

    sf::CircleShape white_human_, white_computer_, black_human_, black_computer_;         ///< The player type circles indicating radio buttons
    sf::Text white_text_, black_text_, depth_text_,                                       ///< The heading texts
        white_human_text_, white_computer_text_, black_human_text_, black_computer_text_, ///< The player type texts
        depth_input_text_,                                                                ///< The search depth input text
        setup_text_, cancel_text_;                                                        ///< The setup and cancel texts
    sf::RectangleShape depth_field_rect_;                                                 ///< The search depth field rectangle
    sf::VertexArray depth_increment_, depth_decrement_;                                   ///< The search depth increment and decrement arrows (vertex arrays)

    bool is_white_player_AI_ = false,
         is_black_player_AI_ = false,
         is_game_setup_active_ = false;
    std::function<void()> notify_parent_; ///< The callback to call when the setup dialog is accepted
};

#endif // GAME_SETUP_HPP