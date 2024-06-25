/**
 * @file GuiUtils.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of the GUI utilities
 * @version 0.1
 * @date 25-06-2024
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "gui/GuiUtils.hpp"

/* move_log */

std::vector<std::shared_ptr<move>> move_log::get_moves() const
{
    return moves_;
}

int move_log::get_moves_count() const
{
    return moves_.size();
}

void move_log::add_move(std::shared_ptr<move> m)
{
    moves_.push_back(m);
}

std::shared_ptr<move> move_log::remove_move(int index)
{
    std::shared_ptr<move> m = moves_[index];
    moves_.erase(moves_.begin() + index);
    return m;
}

void move_log::remove_move(std::shared_ptr<move> m)
{
    moves_.erase(std::remove(moves_.begin(), moves_.end(), m), moves_.end());
}

void move_log::clear_moves()
{
    moves_.clear();
}

/* hourglass */

hourglass::hourglass()
{
    texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/images/hourglass.png");
    sprite_.setTexture(texture_);
    sprite_.setTextureRect(rect_);
    sprite_.setPosition(window_width - 230, 45);
}

void hourglass::set_active(bool active)
{
    active_ = active;
    clock_.restart();
    rect_.left = 0;
    sprite_.setTextureRect(rect_);
}

bool hourglass::is_active() const
{
    return active_;
}

void hourglass::draw(sf::RenderWindow &window)
{
    update(sf::Vector2f(window.getSize().x - 230, sprite_.getPosition().y));
    window.draw(sprite_);
}

void hourglass::update(sf::Vector2f position)
{
    sprite_.setPosition(position);
}

void hourglass::update()
{
    // Move the texture rect every 48 ms to create animation @ ≈ 21 FPS
    if (clock_.getElapsedTime().asMilliseconds() > 48)
    {
        rect_.left = (rect_.left + 48) % 1344; // Hardcoded values for the spriteshet
        sprite_.setTextureRect(rect_);
        clock_.restart();
    }
}