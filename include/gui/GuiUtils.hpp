#ifndef GUI_UTILS_HPP
#define GUI_UTILS_HPP

#include <PreCompiledHeaders.hpp>

#include <SFML/Graphics.hpp>

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
}

class move;

class move_log
{
private:
	std::vector<std::shared_ptr<move>> moves_;

public:
	std::vector<std::shared_ptr<move>> get_moves() const;
	int get_moves_count() const;
	void add_move(std::shared_ptr<move> m);
	std::shared_ptr<move> remove_move(int index);
	void remove_move(std::shared_ptr<move> m);
	void clear_moves();
};

class hourglass
{
public:
	hourglass();
	void set_active(bool active);
	bool is_active() const;
	void draw(sf::RenderWindow &window);
	void update();

private:
	sf::Texture texture_;
	sf::IntRect rect_ = sf::IntRect(0, 0, 48, 48);
	sf::Sprite sprite_;
	sf::Clock clock_;
	bool active_ = false;

private:
	void update(sf::Vector2f position);
};

#endif