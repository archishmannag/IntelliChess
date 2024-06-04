#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <memory>
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 700
#define TILE_HEIGHT 70
#define TILE_WIDTH 70

class board;
class tile;
class piece;
class menu_bar;
class taken_pieces_block;
class game_history_block;
class game_setup;
class move;
enum class player_type;

class tile_block
{
private:
	sf::RectangleShape tile_rect_;
	int tile_id_;

public:
	tile_block(int t_id);
	int get_tile_id() const;
	sf::RectangleShape get_tile_rect() const;
	void get_tile_rect_scale(float x, float y);
	void set_tile_rect_position(float x, float y);
	void set_tile_rect_fill_color(sf::Color color);
};

class move_log
{
private:
	std::vector<std::shared_ptr<move>> moves;

public:
	std::vector<std::shared_ptr<move>> get_moves() const;
	int get_moves_count() const;
	void add_move(std::shared_ptr<move> m);
	std::shared_ptr<move> remove_move(int index);
	void remove_move(std::shared_ptr<move> m);
	void clear_moves();
};

class game_board
{
private:
	// Window and event
	std::shared_ptr<sf::RenderWindow> window_;
	sf::Event event_;
	sf::RectangleShape back_ground_;
	sf::View current_main_view_;

	// Window scale
	sf::Vector2f window_scale_;

	// Mouse position and event
	sf::Vector2i mouse_position_;

	// Main board, textures and sprites
	sf::RectangleShape board_rect_;
	std::vector<tile_block> tile_blocks_;
	sf::Texture black_pawn_texture_, white_pawn_texture_,
		black_knight_texture_, white_knight_texture_,
		black_bishop_texture_, white_bishop_texture_,
		black_king_texture_, white_king_texture_,
		black_rook_texture_, white_rook_texture_,
		black_queen_texture_, white_queen_texture_;
	sf::Sprite black_pawn_sprite_, white_pawn_sprite_,
		black_knight_sprite_, white_knight_sprite_,
		black_bishop_sprite_, white_bishop_sprite_,
		black_king_sprite_, white_king_sprite_,
		black_rook_sprite_, white_rook_sprite_,
		black_queen_sprite_, white_queen_sprite_;

	// Menu bar
	std::unique_ptr<menu_bar> menu_bar_;

	// Taken pieces
	std::unique_ptr<taken_pieces_block> taken_pieces_block_;

	// Game history
	std::unique_ptr<game_history_block> game_history_block_;

	// Game setup
	std::unique_ptr<game_setup> game_setup_;
	bool is_game_setup_open_ = false;
	bool is_move_made_ = false;

	// Move log
	move_log move_log_;
	std::shared_ptr<board> board_;
	std::shared_ptr<tile> source_tile_, destination_tile_;
	std::shared_ptr<piece> moved_piece_;

	// Pawn Promotion
	sf::RectangleShape pawn_promotion_rect_;
	bool pawn_promotion_ = false;

	friend bool is_pawn_promotable(game_board &gb);

	void init();
	void undo_last_move();
	void undo_all_moves();
	void process_events();
	void update_mouse_position();
	void scale_board();
	void render_tile_blocks();
	void render_pawn_promotion_option_pane();
	void update_tile_blocks();
	std::vector<int> legal_move_destinations();
	void move_handler();
	void observe();

	class ai_move_generator
	{
	public:
		ai_move_generator(game_board *parent);
		void run();
		void done(std::shared_ptr<move> best_move);
		std::shared_ptr<move> get_best_move();

	private:
		game_board *parent_;
	};

	std::unique_ptr<ai_move_generator> ai;

public:
	game_board();
	~game_board();
	bool is_running() const;
	void update();
	void render();
};

bool is_pawn_promotable(game_board &gameBoard);

#endif