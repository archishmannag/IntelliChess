#ifndef TAKEN_PIECES_HPP
#define TAKEN_PIECES_HPP

#include <PreCompiledHeaders.hpp>

#include <SFML/Graphics.hpp>

class move_log;

class taken_pieces_block
{
private:
	sf::Vector2f black_piece_area_position_, white_piece_area_position_;
	sf::RectangleShape taken_piece_area_rect_;
	sf::Texture black_pawn_texture_, white_pawn_texture_,
		black_bishop_texture_, white_bishop_texture_,
		black_knight_texture_, white_knight_texture_,
		black_rook_texture_, white_rook_texture_,
		black_queen_texture_, white_queen_texture_;
	std::vector<sf::Sprite> black_pawn_sprites_, white_pawn_sprites_,
		black_bishop_sprites_, white_bishop_sprites_,
		black_knight_sprites_, white_knight_sprites_,
		black_rook_sprites_, white_rook_sprites_,
		black_queen_sprites_, white_queen_sprites_;

public:
	taken_pieces_block();
	void redo(move_log &ml);
	void draw(sf::RenderWindow &window);
};

#endif