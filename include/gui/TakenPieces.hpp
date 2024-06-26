/**
 * @file TakenPieces.hpp
 * @author Archishman Nag (nag.archishman@gmail.com)
 * @brief Header file for the taken pieces class
 * @version 1.0.0
 *
 */

#ifndef TAKEN_PIECES_HPP
#define TAKEN_PIECES_HPP

#include "PreCompiledHeaders.hpp"

#include "SFML/Graphics.hpp"

// Forward declarations
class move_log;

/**
 * @brief A GUI element to display all the captured pieces
 *
 */
class taken_pieces_block
{
public:
    taken_pieces_block();
    /**
     * @brief Calculate the captured pieces after a move
     *
     * @param ml The move log
     */
    void redo(move_log &ml);
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2f black_piece_area_position_, white_piece_area_position_; ///< The position of the black and white captured pieces
    sf::RectangleShape taken_piece_area_rect_;                           ///< The rectangle shape for the whole element
    sf::Texture black_pawn_texture_, white_pawn_texture_,                ///< The textures for the black and white pawns
        black_bishop_texture_, white_bishop_texture_,                    ///< The textures for the black and white bishops
        black_knight_texture_, white_knight_texture_,                    ///< The textures for the black and white knights
        black_rook_texture_, white_rook_texture_,                        ///< The textures for the black and white rooks
        black_queen_texture_, white_queen_texture_;                      ///< The textures for the black and white queens
    std::vector<sf::Sprite> black_pawn_sprites_, white_pawn_sprites_,    ///< The sprites for the black and white pawns
        black_bishop_sprites_, white_bishop_sprites_,                    ///< The sprites for the black and white bishops
        black_knight_sprites_, white_knight_sprites_,                    ///< The sprites for the black and white knights
        black_rook_sprites_, white_rook_sprites_,                        ///< The sprites for the black and white rooks
        black_queen_sprites_, white_queen_sprites_;                      ///< The sprites for the black and white queens
                                                                         // No kings as they can't be captured
};

#endif // TAKEN_PIECES_HPP