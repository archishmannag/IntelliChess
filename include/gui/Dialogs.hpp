/**
 * @file Dialogs.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the dialog classes
 * @version 1.0.0
 *
 */

#ifndef DIALOGS_HPP
#define DIALOGS_HPP

#include "PreCompiledHeaders.hpp"
#include "SFML/Graphics.hpp"

/**
 * @brief Polymorphic dialog class
 *
 * @details This class represents the base class for all dialog boxes. It cannot be instantiated.
 *
 */
class dialog
{
public:
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void event_handler(sf::Event &event) = 0;
    void set_active(bool active);
    bool is_active() const;
    void set_heading_text(std::string text);
    void set_dialog_text(std::string text);

protected:
    dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position);
    void update_text_positions();

protected:
    sf::RectangleShape dialog_box_, ///< The dialog box background
        heading_box_;               ///< The heading background
    sf::Text heading_text_,         ///< The heading text
        dialog_text_;               ///< The dialog text
    sf::Font font_;                 ///< Font for the text
    bool is_active_ = false;        ///< Is the dialog active?
};

/**
 * @brief Message dialogs show information to the user without taking any inputs.
 *
 */
class message_dialog final : public dialog
{
public:
    /**
     * @brief Construct a new message dialog
     *
     * @param heading_text The heading string
     * @param dialog_text The dialog text
     * @param position The position of the dialog box in the window
     * @param ok_callback The callback function for the OK button
     */
    message_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void()> ok_callback = []() {});
    void draw(sf::RenderWindow &window) override;
    void event_handler(sf::Event &event) override;

private:
    sf::RectangleShape ok_button_;      ///< The OK button shape
    sf::Text ok_text_;                  ///< The OK button text
    std::function<void()> ok_callback_; ///< The OK button callback, which expects no arguments and returns void
};

/**
 * @brief Input dialogs are meant to take inputs from the user and then hand them over for processing.
 *
 */
class input_dialog final : public dialog
{
public:
    /**
     * @brief Construct a new input dialog
     *
     * @param heading_text The heading string
     * @param dialog_text The dialog text
     * @param position The position of the dialog box in the window
     * @param ok_callback The callback function for the OK button. Expects a string which will be filled with the user input.
     * @param cancel_callback The callback function for the Cancel button. Maybe set for doing some cleanup.
     */
    input_dialog(std::string heading_text, std::string dialog_text, sf::Vector2f position, std::function<void(std::string)> ok_callback, std::function<void()> cancel_callback = []() {});
    void draw(sf::RenderWindow &window) override;
    void event_handler(sf::Event &event) override;
    void set_input_text(std::string text);

private:
    /**
     * @brief Update the input text view, so that the part of the text that is being edited is always visible.
     *
     */
    void update_input_text_view();
    /**
     * @brief Update the input text view, so that the part of the text that is being edited is always visible.
     *
     * @details SFML's views capture a part of the drawn canvas, and display it where we set.
     * The viewport, where the captured part is drawn is to be specified as a fraction of the window size.
     * This function calculates the viewport based on the window dimensions.
     *
     * @param window_dimensions
     */
    void update_input_text_view(sf::Vector2u window_dimensions);

private:
    int cursor_position_ = 0;                      ///< The cursor position in the input text
    sf::RectangleShape ok_button_,                 ///< The OK button shape
        cancel_button_,                            ///< The Cancel button shape
        input_box_;                                ///< The input box rectangle
    sf::Text ok_text_,                             ///< The OK button text
        cancel_text_,                              ///< The Cancel button text
        input_text_;                               ///< The input text, which the user populates
    sf::Font input_text_font_;                     ///< The font for the input text. A mono-spaced font is recommended for easy cursor positioning.
    sf::View input_text_view_;                     ///< The view for the input text. This is used to allow the input text to exceed the input box width.
    sf::Clipboard clipboard_;                      ///< The clipboard for the input text. This is used to paste text. @todo: Move this to base class and add copy functionality.
    std::function<void(std::string)> ok_callback_; ///< The OK button callback, which expects a string and returns void (must be set)
    std::function<void()> cancel_callback_;        ///< The Cancel button callback, which expects no arguments and returns void (may be set)
};

#endif // DIALOGS_HPP