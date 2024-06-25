/**
 * @file GameBoard.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the game board class
 * @version 1.0.0
 *
 */

#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include "PreCompiledHeaders.hpp"

#include "gui/GuiUtils.hpp"

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

// Forward declarations
class board;
class tile;
class piece;
class menu_bar;
class taken_pieces_block;
class game_history_block;
class game_setup;
class message_dialog;
class input_dialog;
class move;
enum class player_type;

/**
 * @brief Represents a tile block in the GUI.
 *
 */
class tile_block
{
public:
    tile_block(int t_id);
    int get_tile_id() const;
    sf::RectangleShape get_tile_rect() const;
    void set_tile_rect_scale(float x, float y);
    void set_tile_rect_position(float x, float y);
    void set_tile_rect_fill_color(sf::Color color);

private:
    sf::RectangleShape tile_rect_; ///< The tile rectangle
    int tile_id_;                  ///< The tile id, 0-63
};

/**
 * @brief The main GUI class consisting of all the GUI elements.
 *
 */
class game_board
{
public:
    game_board();
    ~game_board();
    bool is_running() const;
    void update();
    void render();

private:
    void init();
    std::vector<int> legal_move_destinations();

private: // GUI-related methods
    void process_events();
    void update_mouse_position();
    void scale_board();
    void render_tile_blocks();
    void render_pawn_promotion_option_pane();
    void update_tile_blocks();

private: // Game-related methods
    void move_handler();
    void observe();
    void undo_last_move();
    void undo_all_moves();

private:
    // Window and event
    std::shared_ptr<sf::RenderWindow> window_; ///< The SFML window
    sf::Event event_;                          ///< The SFML event (for polling)
    sf::RectangleShape back_ground_;           ///< The background rectangle
    sf::View current_main_view_;               ///< The current main view

    // Window scale
    sf::Vector2f window_scale_; ///< The window scale

    // Mouse position and event
    sf::Vector2i mouse_position_; ///< The mouse position

    // Main board, textures and sprites
    sf::RectangleShape board_rect_;                       ///< The board rectangle(For an outline giving a table-like look)
    std::vector<tile_block> tile_blocks_;                 //< The tile blocks
    sf::Texture black_pawn_texture_, white_pawn_texture_, ///< The textures for the pawns
        black_knight_texture_, white_knight_texture_,     ///< The textures for the knights
        black_bishop_texture_, white_bishop_texture_,     ///< The textures for the bishops
        black_king_texture_, white_king_texture_,         ///< The textures for the kings
        black_rook_texture_, white_rook_texture_,         ///< The textures for the rooks
        black_queen_texture_, white_queen_texture_;       ///< The textures for the queens
    sf::Sprite black_pawn_sprite_, white_pawn_sprite_,    ///< The sprites for the pawns
        black_knight_sprite_, white_knight_sprite_,       ///< The sprites for the knights
        black_bishop_sprite_, white_bishop_sprite_,       ///< The sprites for the bishops
        black_king_sprite_, white_king_sprite_,           ///< The sprites for the kings
        black_rook_sprite_, white_rook_sprite_,           ///< The sprites for the rooks
        black_queen_sprite_, white_queen_sprite_;         ///< The sprites for the queens

    // Menu bar
    std::unique_ptr<menu_bar> menu_bar_; ///< The menu bar

    // Taken pieces
    std::unique_ptr<taken_pieces_block> taken_pieces_block_; ///< The element showing all the captured pieces

    // Game history
    std::unique_ptr<game_history_block> game_history_block_; ///< The element showing the move history

    // Game setup
    std::unique_ptr<game_setup> game_setup_; ///< The game setup dialog

    // Dialogs
    std::unique_ptr<message_dialog> message_dialog_; ///< The message dialog
    std::unique_ptr<input_dialog> input_dialog_;     ///< The input dialog

    // Move log
    move_log move_log_; ///< The move log

    // Move-related
    bool is_move_made_ = false;
    std::shared_ptr<board> board_;                                             ///< The board
    std::shared_ptr<tile> source_tile_ = nullptr, destination_tile_ = nullptr; ///< The source and destination tiles for the move
    std::shared_ptr<piece> moved_piece_ = nullptr;                             ///< The moved piece

    // Pawn Promotion
    sf::RectangleShape pawn_promotion_rect_; ///< The pawn promotion rectangle
    bool pawn_promotion_ = false;            ///< Is the pawn promotion pane active?

    // Hourglass
    hourglass hourglass_; ///< The hourglass animation to be shown when the AI is thinking

    /**
     * @brief The AI move generator class
     *
     * @details This class is responsible for invoking the move search algorithm in a separate thread, taking care of asynchronous operations.
     *
     */
    class ai_move_generator
    {
    public:
        /**
         * @brief Construct a new ai move generator
         *
         * @param parent Pointer to the parent to access members and methods
         */
        ai_move_generator(game_board *parent);
        /**
         * @brief Runs the get_best_move() function in a separate thread
         *
         */
        void run();
        /**
         * @brief Upon completion of the algorithm, this method is called to notify the parent
         *
         * @details As an inner class method, this class has access to parent's members and methods. So this function need not return anything but it modifies the state of the parent internally.
         *
         * @param best_move
         */
        void done(std::shared_ptr<move> best_move);
        std::shared_ptr<move> get_best_move();

    private:
        game_board *parent_; ///< The parent game board
    };

    std::unique_ptr<ai_move_generator> ai; ///< The AI move generator

    friend bool is_pawn_promotable(game_board &gb);
};

bool is_pawn_promotable(game_board &gameBoard);

#endif // GAME_BOARD_HPP