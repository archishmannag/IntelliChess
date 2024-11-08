/**
 * @file GameHistory.cpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Implementation of the game history class
 * @version 1.1.0
 *
 */

#include "gui/GameHistory.hpp"
#include "engine/Alliance.hpp"
#include "engine/board/Board.hpp"
#include "engine/board/BoardUtils.hpp"
#include "engine/board/Move.hpp"
#include "engine/pieces/Piece.hpp"
#include "engine/player/Player.hpp"
#include "gui/GuiUtils.hpp"

/* history_row */

history_row::history_row(sf::Font &font)
{
    white_move_.setFont(font);
    white_move_.setCharacterSize(18);
    white_move_.setFillColor(sf::Color::Black);

    black_move_.setFont(font);
    black_move_.setCharacterSize(18);
    black_move_.setFillColor(sf::Color::Black);

    bottom_divider_rect_.setSize(sf::Vector2f(160, 2));
    bottom_divider_rect_.setFillColor(sf::Color(0, 0, 0, 100));
}

void history_row::set_position(sf::Vector2f position)
{
    white_move_.setPosition(position + sf::Vector2f(7, 0));
    black_move_.setPosition(position + sf::Vector2f(80, 0) + sf::Vector2f(7, 0));
    bottom_divider_rect_.setPosition(position + sf::Vector2f(0, 23));
}

void history_row::set_white_move(std::string move)
{
    white_move_.setString(move);
}

void history_row::set_black_move(std::string move)
{
    black_move_.setString(move);
}

sf::Vector2f history_row::get_position() const
{
    return bottom_divider_rect_.getPosition() + sf::Vector2f(0, 2);
}

std::string history_row::get_white_move()
{
    return white_move_.getString();
}

std::string history_row::get_black_move()
{
    return black_move_.getString();
}

void history_row::draw(sf::RenderWindow &window)
{
    window.draw(white_move_);
    window.draw(black_move_);
    window.draw(bottom_divider_rect_);
}

/* game_history_block */

game_history_block::game_history_block()
{
    if (!font_.loadFromFile(std::string(PROJECT_RESOURCE_DIR) + "/fonts/arial.ttf"))
        throw std::runtime_error("Failed to load font!");

    scroll_percentage_top_ = 0.f;
    scroll_percentage_bottom_ = 100.f;

    scroll_bar_clicked_ = false;

    game_history_area_rect_.setSize(sf::Vector2f(180, 560));
    game_history_area_rect_.setPosition(780, 75);
    game_history_area_rect_.setFillColor(sf::Color(253, 245, 230));

    scroll_bar_rect_.setSize(sf::Vector2f(20, 560));
    scroll_bar_rect_.setPosition(940, 75);
    scroll_bar_rect_.setFillColor(sf::Color(200, 200, 200));

    divider_rect_.setSize(sf::Vector2f(2, 0));
    divider_rect_.setPosition(860, 75);
    divider_rect_.setFillColor(sf::Color(0, 0, 0, 100));

    mouse_offset_ = sf::Vector2f(0, 0);

    player_names_[0].setFont(font_);
    player_names_[0].setCharacterSize(18);
    player_names_[0].setFillColor(sf::Color::Black);
    player_names_[0].setString("White");
    player_names_[0].setPosition(800, 50);

    player_names_[1].setFont(font_);
    player_names_[1].setCharacterSize(18);
    player_names_[1].setFillColor(sf::Color::Black);
    player_names_[1].setString("Black");
    player_names_[1].setPosition(880, 50);

    view_.setSize(160, 560);
    view_.setCenter(860, 355);
    // recLeft = 780, recTop = 75, recWidth = 180, recHeight = 560
    view_.setViewport(sf::FloatRect(0.8125f, 0.107f, 0.1667f, 0.8f));
}

sf::View game_history_block::get_view() const
{
    return view_;
}

void game_history_block::redo(board *board, move_log &ml)
{
    if (ml.get_moves().size() == 0)
    {
        history_rows_.clear();
        view_.setCenter(860, 355);
        divider_rect_.setSize(sf::Vector2f(2, 0));
        return;
    }

    // TODO: Refactor this code to add check notation to the moves' string
    // keep track of all checks as the check notation (+) is not added to the moves' string
    std::list<std::string> past_checks;
    for (long unsigned int i = 0; i < history_rows_.size(); i++)
    {
        if (history_rows_[i].get_white_move().find("+") != std::string::npos)
            past_checks.push_back(std::to_string(i) + 'W');
        if (history_rows_[i].get_black_move().find("+") != std::string::npos)
            past_checks.push_back(std::to_string(i) + 'B');
    }

    history_rows_.clear();
    int current_row = 0;
    if (ml.get_moves().size() > 0)
    {
        for (std::size_t i = 0; i < ml.get_moves().size(); i += 2)
        {
            history_row hr(font_);
            hr.set_position(sf::Vector2f(game_history_area_rect_.getPosition().x, 75 + current_row * 25));

            // Very ugly code, but it works. Will refactor later
            hr.set_white_move(
                ml.get_moves()[i]->stringify() + ((past_checks.front() == std::to_string(current_row) + 'W') ? past_checks.pop_front(), "+" : ""));
            if (i + 1 < ml.get_moves().size())
                hr.set_black_move(
                    ml.get_moves()[i + 1]->stringify() + ((past_checks.front() == std::to_string(current_row) + 'B') ? past_checks.pop_front(), "+" : ""));
            history_rows_.push_back(hr);
            current_row++;
        }
        const std::shared_ptr<move> &last_move = ml.get_moves().back();
        const std::string last_move_string = last_move->stringify() + board_utils::calculate_check_and_checkmate(board);
        history_row &last_row = history_rows_.back();
        if (alliance_utils::is_white(last_move->get_moved_piece()->get_piece_alliance()))
            last_row.set_white_move(last_move_string);
        else
            last_row.set_black_move(last_move_string);
    }
    divider_rect_.setSize(sf::Vector2f(2, 25 * current_row));
    game_history_area_rect_.setSize(sf::Vector2f(180, std::max(25 * current_row, 560)));
}

// If mouse is scrolled over this block, we directly scroll the view.
void game_history_block::mouse_wheel_scrolled(sf::Event::MouseWheelScrollEvent &event, sf::Vector2f window_size)
{
    // Get the viewport and convert its dimensions to pixels from fractions of window size
    sf::FloatRect view_port_dim = view_.getViewport();
    sf::FloatRect dim(window_size.x * view_port_dim.left, window_size.y * view_port_dim.top, window_size.x * view_port_dim.width, window_size.y * view_port_dim.height);
    if (dim.contains(event.x, event.y))
    {
        // Move 1 row up or down
        if (event.delta > 0)
        {
            if (scroll_percentage_top_ > 0)
                view_.move(0, -25);
        }
        else if (scroll_percentage_bottom_ < 100)
            view_.move(0, 25);
    }
    update_scroll_percentage(window_size);
}

// This function, just observes whether the scroll bar is clicked for scrolling. The actual scrolling is done in scroll function.
void game_history_block::scroll_bar_scrolled(sf::Event::MouseButtonEvent &event, bool mouse_button_down)
{
    if (mouse_button_down && event.button == sf::Mouse::Button::Left && scroll_bar_rect_.getGlobalBounds().contains(event.x, event.y))
    {
        scroll_bar_clicked_ = true;
        // Offset set so that the relative position of the mouse to the scroll bar is maintained.
        mouse_offset_ = scroll_bar_rect_.getPosition() - sf::Vector2f(event.x, event.y);
    }
    else
        scroll_bar_clicked_ = false;
}

// If scroll bar is click held, start scrolling the view.
void game_history_block::scroll(sf::RenderWindow &window)
{
    if (scroll_bar_clicked_)
    {
        // The mouse wheel scroll and this scroll, both scroll the view in discrete steps, 1 row at a time. So the scrolling is not smooth.

        sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window)),             // Current mouse position
            current_rect_position = scroll_bar_rect_.getPosition(),                                        // Current position of the scroll bar
            new_rect_position = sf::Vector2f(current_rect_position.x, mouse_position.y + mouse_offset_.y), // New position of the scroll bar (if it were continuous)
            distance = new_rect_position - current_rect_position,
                     window_size = window.getView().getSize();
        int number_of_entries_traversed = distance.y / 25; // Convert continuous scroll to discrete

        if (distance.y > 0 && scroll_percentage_bottom_ < 100.f)
        {
            view_.move(0, 25 * number_of_entries_traversed);
        }
        else if (distance.y < 0 && scroll_percentage_top_ > 0.f)
        {
            view_.move(0, 25 * number_of_entries_traversed);
        }
        update_scroll_percentage(window_size);
    }
}

void game_history_block::update(sf::RenderWindow &window)
{
    // Static elements
    sf::Vector2u window_size = window.getSize();
    player_names_[0].setPosition(window_size.x - 160, 50);
    player_names_[1].setPosition(window_size.x - 80, 50);
    game_history_area_rect_.setPosition(window_size.x - 180, 75);
    scroll_bar_rect_.setPosition(window_size.x - 20, scroll_bar_rect_.getPosition().y);
    divider_rect_.setPosition(window_size.x - 100, 75);

    // View
    float y = view_.getSize().y;
    view_.setSize(160, std::min(560u, window_size.y - 75));
    y -= view_.getSize().y;
    view_.setCenter(window_size.x - 100, view_.getCenter().y - y / 2);
    view_.setViewport(sf::FloatRect((window_size.x - 180) / static_cast<float>(window_size.x),
                                    75 / static_cast<float>(window_size.y),
                                    160 / static_cast<float>(window_size.x),
                                    (std::min(560u, window_size.y - 75)) / static_cast<float>(window_size.y)));

    update_scroll_percentage(sf::Vector2f(window_size.x, window_size.y));
    for (history_row &historyRow : history_rows_)
        historyRow.set_position(sf::Vector2f(game_history_area_rect_.getPosition().x, historyRow.get_position().y - 25));
}

void game_history_block::update_scroll_percentage(sf::Vector2f window_size)
{
    // Reset view if all rows are visible (Useful when starting a new game and flushing all moves)
    if (history_rows_.size() == 0 || (history_rows_.front().get_position().y > view_.getCenter().y - view_.getSize().y / 2 && history_rows_.back().get_position().y < view_.getCenter().y + view_.getSize().y / 2))
    {
        scroll_percentage_top_ = 0.f;
        scroll_percentage_bottom_ = 100.f;
        scroll_bar_rect_.setSize(sf::Vector2f(20, view_.getSize().y));
        scroll_bar_rect_.setPosition(window_size.x - 20, 75);
    }
    else
    {
        scroll_percentage_bottom_ = (view_.getCenter().y - 75 + view_.getSize().y / 2) / (history_rows_.back().get_position().y - 75) * 100.f;
        scroll_percentage_top_ = std::max(0.f, scroll_percentage_bottom_ - 100.f * view_.getSize().y / (history_rows_.back().get_position().y - 75));
        scroll_bar_rect_.setSize(sf::Vector2f(20, std::min(560.f, window_size.y - 75.f) * view_.getSize().y / (history_rows_.back().get_position().y - 75)));
        scroll_bar_rect_.setPosition(window_size.x - 20, 75 + view_.getSize().y * scroll_percentage_top_ / 100.f);
    }
}

void game_history_block::draw(sf::RenderWindow &window)
{
    update(window);
    window.draw(player_names_[0]);
    window.draw(player_names_[1]);
    window.draw(scroll_bar_rect_);
    window.setView(view_);
    window.draw(game_history_area_rect_);
    window.draw(divider_rect_);
    for (history_row &history_row : history_rows_)
        history_row.draw(window);
}