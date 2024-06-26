/**
 * @file Menu.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the menu bar
 * @version 1.0.0
 *
 */

#ifndef MENU_HPP
#define MENU_HPP

#include "PreCompiledHeaders.hpp"

#include "SFML/Graphics.hpp"

/**
 * @brief A struct to hold the callback functions for the menu bar
 *
 * @details As the menu bar has several menu items, passing so many callbacks individually is cumbersome and error-prone.
 * So this struct is to be initialied, and passed to the menu bar constructor.
 * All the functions are to take as well as return void, only to change the state in their body.
 *
 */
typedef struct callback_functions
{
    std::function<void()> load_FEN_, create_FEN_, save_game_, exit_,         // File menu
        new_game_, undo_move_, evaluate_board_, current_state_, setup_game_; // Option menu
} callback_functions_t;

/**
 * @brief The class representing the menu bar
 *
 */
class menu_bar
{
public:
    /**
     * @brief Construct a new menu bar
     *
     * @param window The window to draw the menu bar on
     * @param callback_functions The callback functions for the menu bar
     */
    menu_bar(sf::RenderWindow &window, callback_functions_t callback_functions);
    void update_menu_bar(sf::Event event, sf::Vector2i mouse_position);
    void draw(sf::RenderWindow &window);

private:
    void update(sf::RenderWindow &window);

private:
    sf::RectangleShape menu_bar_rect_; ///< The menu bar rectangle
    sf::Font font_;                    ///< The font for the text

    // Main menu text
    sf::Text file_text_, option_text_; ///< The main menu items text

    // File menu text and rectangle
    bool file_menu_open_ = false;
    sf::RectangleShape file_menu_rect_;                                     ///< The file menu rectangle
    sf::Text load_FEN_text_, create_FEN_text_, save_game_text_, exit_text_; ///< The various file menu items text

    // Option menu text and rectangle
    bool option_menu_open_ = false;
    sf::RectangleShape option_menu_rect_;                                                                  ///< The option menu rectangle
    sf::Text new_game_text_, undo_move_text_, evaluate_board_text_, current_state_text_, setup_game_text_; ///< The various option menu items text

    callback_functions_t callback_functions_; ///< The callback functions for the menu bar
};

#endif // MENU_HPP