#include <gui/GameBoard.hpp>
#include <gui/Menu.hpp>
#include <gui/TakenPieces.hpp>
#include <gui/GameHistory.hpp>
#include <gui/GameSetup.hpp>
#include <gui/Dialogs.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Tile.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/MoveTransition.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/King.hpp>
#include <engine/player/ai/MoveStrategy.hpp>
#include <engine/player/ai/AlphaBeta.hpp>
#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <pgn/FenUtils.hpp>
#include <pgn/PgnUtils.hpp>

/* tile_block */

tile_block::tile_block(int t_id)
{
	tile_id_ = t_id;
	// Initial size and positions
	tile_rect_.setSize(sf::Vector2f(tile_width, tile_height));
	tile_rect_.setFillColor((t_id / 8 + t_id) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
	tile_rect_.setPosition(162.5f + (t_id % 8) * tile_width, 75 + (t_id / 8) * tile_height);
}

int tile_block::get_tile_id() const
{
	return tile_id_;
}

sf::RectangleShape tile_block::get_tile_rect() const
{
	return tile_rect_;
}

void tile_block::get_tile_rect_scale(float x, float y)
{
	tile_rect_.setScale(x, y);
}

void tile_block::set_tile_rect_position(float x, float y)
{
	tile_rect_.setPosition(x, y);
}

void tile_block::set_tile_rect_fill_color(sf::Color color)
{
	tile_rect_.setFillColor(color);
}

/* game_board */

game_board::game_board()
{
	init();
}

game_board::~game_board() = default;

namespace
{
	void print_vector_pieces(std::vector<std::shared_ptr<piece>> vec)
	{
		std::sort(vec.begin(), vec.end(), [](std::shared_ptr<piece> a, std::shared_ptr<piece> b)
				  { return a->get_piece_value() < b->get_piece_value(); });
		std::cout << "[";
		for (std::vector<std::shared_ptr<piece>>::iterator it = vec.begin(); it != vec.end(); it++)
		{
			if ((*it)->get_piece_alliance() == alliance::white)
				std::cout << (*it)->stringify();
			else
				std::cout << static_cast<char>(std::tolower((*it)->stringify()[0]));
			if (it != vec.end() - 1)
				std::cout
					<< ", ";
		}
		std::cout << "]" << std::endl;
	}

	void print_player_info(player *p)
	{
		std::vector<std::shared_ptr<move>> legal_moves = p->get_legal_moves();
		std::cout << "Player: " << p->stringify() << '\n'
				  << "Legal moves (" << legal_moves.size() << ") = [";
		for (std::vector<std::shared_ptr<move>>::iterator it = legal_moves.begin(); it != legal_moves.end(); it++)
		{
			std::cout << (*it)->stringify();
			if (it != legal_moves.end() - 1)
				std::cout << ", ";
		}
		std::cout << "]\n"
				  << "Is in check: " << p->is_in_check() << '\n'
				  << "Is in checkmate: " << p->is_is_checkmate() << '\n'
				  << "Is in stalemate: " << p->is_in_stalemate() << '\n'
				  << "Is castled: " << p->is_castled() << std::endl;
	}
} // namespace

void game_board::init()
{
	board_ = board::create_standard_board();

	window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "Chess");
	window_->setFramerateLimit(60);
	current_main_view_ = window_->getDefaultView();

	back_ground_.setSize(sf::Vector2f(window_width, window_height));
	back_ground_.setFillColor(sf::Color::White);

	board_rect_.setSize(sf::Vector2f(10 + 8 * tile_width, 10 + 8 * tile_height));
	board_rect_.setFillColor(sf::Color(139, 71, 38));
	board_rect_.setPosition(157.5f, 70);

	pawn_promotion_rect_.setSize(sf::Vector2f(1 * tile_width, 4 * tile_height));
	pawn_promotion_rect_.setFillColor(sf::Color(139, 71, 38));

	callback_functions_t call_backs;
	/* All the callback fnctions for the menu bar */
	{
		call_backs.load_FEN = [this]()
		{
			input_dialog_ = std::make_unique<input_dialog>(
				"FEN",
				"Enter FEN:",
				sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75),
				[this](std::string fen)
				{
					std::shared_ptr<board> temp_board = board_;
					undo_all_moves();
					try
					{
						board_ = fen_utils::fen_to_board(fen);
					}
					catch (const std::runtime_error &e)
					{
						board_ = temp_board;
						message_dialog_ = std::make_unique<message_dialog>(
							"Error",
							e.what(),
							sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75));
						message_dialog_->set_active(true);
					}
				});
			input_dialog_->set_active(true);
		};
		call_backs.create_FEN = [this]()
		{
			std::string fen = fen_utils::board_to_fen(*board_);
			message_dialog_ = std::make_unique<message_dialog>(
				"FEN",
				fen,
				sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75));
			message_dialog_->set_active(true);
		};
		call_backs.save_game = [this]()
		{
			input_dialog_ = std::make_unique<input_dialog>(
				"Save Game",
				"Enter File to save PGN to:",
				sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75),
				[this](std::string pgn_file)
				{
					try
					{
						pgn_utils::save_game_to_pgn(pgn_file, move_log_.get_moves(), *board_);
					}
					catch (const std::runtime_error &e)
					{
						message_dialog_ = std::make_unique<message_dialog>(
							"Error",
							e.what(),
							sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75));
						message_dialog_->set_active(true);
					}
				});
			input_dialog_->set_input_text(std::filesystem::current_path().string() + "/game.pgn");
			input_dialog_->set_active(true);
		};
		call_backs.exit = [this]()
		{ window_->close(); };
		call_backs.new_game = [this]()
		{ undo_all_moves(); };
		call_backs.undo_move = [this]()
		{ undo_last_move(); };
		call_backs.evaluate_board = [this]()
		{
			std::cout << standard_board_evaluator::evaluation_details(*board_, game_setup_->get_search_depth()) << std::endl;
		};
		call_backs.current_state = [this]()
		{
			print_player_info(board_->get_white_player().get());
			print_vector_pieces(board_->get_white_pieces());
			print_player_info(board_->get_black_player().get());
			print_vector_pieces(board_->get_black_pieces());
		};
		call_backs.setup_game = [this]()
		{ game_setup_->set_active(true); };
	}

	menu_bar_ = std::make_unique<menu_bar>(*window_, call_backs);

	taken_pieces_block_ = std::make_unique<taken_pieces_block>();

	game_history_block_ = std::make_unique<game_history_block>();

	game_setup_ = std::make_unique<game_setup>([this]() -> void
											   { observe(); });

	ai = std::make_unique<ai_move_generator>(this);

	for (int i = 0; i < 64; i++)
		tile_blocks_.push_back(tile_block(i));

	if (
		!black_pawn_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackPawn.png") ||
		!white_pawn_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whitePawn.png") ||
		!black_king_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKing.png") ||
		!white_king_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKing.png") ||
		!black_bishop_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackBishop.png") ||
		!white_bishop_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteBishop.png") ||
		!black_knight_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKnight.png") ||
		!white_knight_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKnight.png") ||
		!black_rook_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackRook.png") ||
		!white_rook_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteRook.png") ||
		!black_queen_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackQueen.png") ||
		!white_queen_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteQueen.png"))
	{
		throw std::runtime_error("Error loading textures");
	}

	black_pawn_texture_.setSmooth(true);
	white_pawn_texture_.setSmooth(true);
	black_king_texture_.setSmooth(true);
	white_king_texture_.setSmooth(true);
	black_bishop_texture_.setSmooth(true);
	white_bishop_texture_.setSmooth(true);
	black_knight_texture_.setSmooth(true);
	white_knight_texture_.setSmooth(true);
	black_rook_texture_.setSmooth(true);
	white_rook_texture_.setSmooth(true);
	black_queen_texture_.setSmooth(true);
	white_queen_texture_.setSmooth(true);

	black_pawn_sprite_.setTexture(black_pawn_texture_);
	white_pawn_sprite_.setTexture(white_pawn_texture_);
	black_king_sprite_.setTexture(black_king_texture_);
	white_king_sprite_.setTexture(white_king_texture_);
	black_bishop_sprite_.setTexture(black_bishop_texture_);
	white_bishop_sprite_.setTexture(white_bishop_texture_);
	black_knight_sprite_.setTexture(black_knight_texture_);
	white_knight_sprite_.setTexture(white_knight_texture_);
	black_rook_sprite_.setTexture(black_rook_texture_);
	white_rook_sprite_.setTexture(white_rook_texture_);
	black_queen_sprite_.setTexture(black_queen_texture_);
	white_queen_sprite_.setTexture(white_queen_texture_);

	// Initial scales of the sprites, this will get updated everytime the window is resized
	black_pawn_sprite_.setScale(tile_width / black_pawn_sprite_.getLocalBounds().width, tile_height / black_pawn_sprite_.getLocalBounds().height);
	white_pawn_sprite_.setScale(tile_width / white_pawn_sprite_.getLocalBounds().width, tile_height / white_pawn_sprite_.getLocalBounds().height);
	black_king_sprite_.setScale(tile_width / black_king_sprite_.getLocalBounds().width, tile_height / black_king_sprite_.getLocalBounds().height);
	white_king_sprite_.setScale(tile_width / white_king_sprite_.getLocalBounds().width, tile_height / white_king_sprite_.getLocalBounds().height);
	black_bishop_sprite_.setScale(tile_width / black_bishop_sprite_.getLocalBounds().width, tile_height / black_bishop_sprite_.getLocalBounds().height);
	white_bishop_sprite_.setScale(tile_width / white_bishop_sprite_.getLocalBounds().width, tile_height / white_bishop_sprite_.getLocalBounds().height);
	black_knight_sprite_.setScale(tile_width / black_knight_sprite_.getLocalBounds().width, tile_height / black_knight_sprite_.getLocalBounds().height);
	white_knight_sprite_.setScale(tile_width / white_knight_sprite_.getLocalBounds().width, tile_height / white_knight_sprite_.getLocalBounds().height);
	black_rook_sprite_.setScale(tile_width / black_rook_sprite_.getLocalBounds().width, tile_height / black_rook_sprite_.getLocalBounds().height);
	white_rook_sprite_.setScale(tile_width / white_rook_sprite_.getLocalBounds().width, tile_height / white_rook_sprite_.getLocalBounds().height);
	black_queen_sprite_.setScale(tile_width / black_queen_sprite_.getLocalBounds().width, tile_height / black_queen_sprite_.getLocalBounds().height);
	white_queen_sprite_.setScale(tile_width / white_queen_sprite_.getLocalBounds().width, tile_height / white_queen_sprite_.getLocalBounds().height);
}

bool game_board::is_running() const
{
	return window_->isOpen();
}

void game_board::process_events()
{
	while (window_->pollEvent(event_))
	{
		switch (event_.type)
		{
		case sf::Event::Closed:
			window_->close();
			break;
		case sf::Event::Resized:
		{
			// Set the view to the visible area
			sf::FloatRect visible_area(0, 0, event_.size.width, event_.size.height);
			current_main_view_.setSize(visible_area.width, visible_area.height);
			current_main_view_.setCenter(visible_area.width / 2, visible_area.height / 2);
			current_main_view_.setViewport(sf::FloatRect(0, 0, 1, 1));
			window_->setView(current_main_view_);

			// Update the scale values
			window_scale_ = sf::Vector2f(static_cast<float>(event_.size.width) / window_width, static_cast<float>(event_.size.height) / window_height);

			// Update size of the background
			back_ground_.setSize(sf::Vector2f(event_.size.width, event_.size.height));

			scale_board();
			break;
		}
		case sf::Event::MouseButtonPressed:
			menu_bar_->update_menu_bar(event_, mouse_position_);
			if (game_setup_->get_active() || (message_dialog_ && message_dialog_->is_active()) || (input_dialog_ && input_dialog_->is_active()))
			{
				if (game_setup_->get_active())
					game_setup_->update(event_, mouse_position_);
				if ((message_dialog_ && message_dialog_->is_active()))
					message_dialog_->event_handler(event_);
				if ((input_dialog_ && input_dialog_->is_active()))
					input_dialog_->event_handler(event_);
			}
			else
				move_handler();
			game_history_block_->scroll_bar_scrolled(event_.mouseButton, true);
			break;
		case sf::Event::MouseButtonReleased:
			game_history_block_->scroll_bar_scrolled(event_.mouseButton, false);
			break;
		case sf::Event::MouseWheelScrolled:
			window_->setView(game_history_block_->get_view());
			game_history_block_->mouse_wheel_scrolled(event_.mouseWheelScroll, sf::Vector2f(window_->getSize().x, window_->getSize().y));
			window_->setView(current_main_view_);
			break;
		case sf::Event::MouseMoved:
			game_history_block_->scroll(*window_);
			break;
		case sf::Event::TextEntered:
			if (game_setup_->get_active())
				game_setup_->update(event_, mouse_position_);
			if (input_dialog_ && input_dialog_->is_active())
				input_dialog_->event_handler(event_);
			break;
		case sf::Event::KeyPressed:
			if (game_setup_->get_active())
				game_setup_->update(event_, mouse_position_);
			if (input_dialog_ && input_dialog_->is_active())
				input_dialog_->event_handler(event_);
			break;
		default:
			break;
		}
	}
}

void game_board::scale_board()
{
	float min = std::min(window_scale_.y, (window_->getSize().x - 195 - 195) / static_cast<float>(570));

	// Update size and position of the board
	board_rect_.setScale(min, min);
	pawn_promotion_rect_.setScale(min, min);

	// Update the scale of the sprites
	black_pawn_sprite_.setScale(tile_width / black_pawn_sprite_.getLocalBounds().width * min, tile_height / black_pawn_sprite_.getLocalBounds().height * min);
	white_pawn_sprite_.setScale(tile_width / white_pawn_sprite_.getLocalBounds().width * min, tile_height / white_pawn_sprite_.getLocalBounds().height * min);
	black_king_sprite_.setScale(tile_width / black_king_sprite_.getLocalBounds().width * min, tile_height / black_king_sprite_.getLocalBounds().height * min);
	white_king_sprite_.setScale(tile_width / white_king_sprite_.getLocalBounds().width * min, tile_height / white_king_sprite_.getLocalBounds().height * min);
	black_bishop_sprite_.setScale(tile_width / black_bishop_sprite_.getLocalBounds().width * min, tile_height / black_bishop_sprite_.getLocalBounds().height * min);
	white_bishop_sprite_.setScale(tile_width / white_bishop_sprite_.getLocalBounds().width * min, tile_height / white_bishop_sprite_.getLocalBounds().height * min);
	black_knight_sprite_.setScale(tile_width / black_knight_sprite_.getLocalBounds().width * min, tile_height / black_knight_sprite_.getLocalBounds().height * min);
	white_knight_sprite_.setScale(tile_width / white_knight_sprite_.getLocalBounds().width * min, tile_height / white_knight_sprite_.getLocalBounds().height * min);
	black_rook_sprite_.setScale(tile_width / black_rook_sprite_.getLocalBounds().width * min, tile_height / black_rook_sprite_.getLocalBounds().height * min);
	white_rook_sprite_.setScale(tile_width / white_rook_sprite_.getLocalBounds().width * min, tile_height / white_rook_sprite_.getLocalBounds().height * min);
	black_queen_sprite_.setScale(tile_width / black_queen_sprite_.getLocalBounds().width * min, tile_height / black_queen_sprite_.getLocalBounds().height * min);
	white_queen_sprite_.setScale(tile_width / white_queen_sprite_.getLocalBounds().width * min, tile_height / white_queen_sprite_.getLocalBounds().height * min);

	for (auto &tile_block : tile_blocks_)
	{
		tile_block.get_tile_rect_scale(min, min);
		tile_block.set_tile_rect_position(157.5f + 5 * min + (tile_block.get_tile_id() % 8) * tile_width * min, 25 + 45 + 5 * min + (tile_block.get_tile_id() / 8) * tile_height * min);
	}
}

void game_board::move_handler()
{
	if (event_.type == sf::Event::MouseButtonPressed)
	{
		if (event_.mouseButton.button == sf::Mouse::Left)
		{
			if (!game_setup_->is_AI_player(board_->get_current_player().get()))
			{
				for (auto &tile_block : tile_blocks_)
					if (tile_block.get_tile_rect().getGlobalBounds().contains(mouse_position_.x, mouse_position_.y))
					{
						if (source_tile_ == nullptr)
						{
							source_tile_ = board_->get_tile(tile_block.get_tile_id());
							if ((moved_piece_ = source_tile_->get_piece()) == nullptr)
								source_tile_ = nullptr;
						}
						else
						{
							destination_tile_ = board_->get_tile(tile_block.get_tile_id());
							if (source_tile_->get_tile_coordinate() == destination_tile_->get_tile_coordinate())
							{
								pawn_promotion_ = false;
								source_tile_ = nullptr;
								destination_tile_ = nullptr;
								moved_piece_ = nullptr;
							}
							else if (pawn_promotion_ && pawn_promotion_rect_.getGlobalBounds().contains(mouse_position_.x, mouse_position_.y))
							{
								pawn_promotion_ = false;
								std::shared_ptr<move> m;
								if (moved_piece_->get_piece_alliance() == alliance::white)
								{
									switch (tile_block.get_tile_id() / 8)
									{
									case 0:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8, piece_type::queen);
										break;
									case 1:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8, piece_type::knight);
										break;
									case 2:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8, piece_type::rook);
										break;
									case 3:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8, piece_type::bishop);
										break;
									default:
										throw std::runtime_error("Invalid pawn promotion");
									}
								}
								else
								{
									switch (tile_block.get_tile_id() / 8)
									{
									case 4:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8 + 56, piece_type::bishop);
										break;
									case 5:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8 + 56, piece_type::rook);
										break;
									case 6:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8 + 56, piece_type::knight);
										break;
									case 7:
										m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate() % 8 + 56, piece_type::queen);
										break;
									default:
										throw std::runtime_error("Invalid pawn promotion");
									}
								}
								move_transition transition = board_->get_current_player()->make_move(m);
								if (transition.get_move_status() == move_status::done)
								{
									board_ = transition.get_transition_board();
									move_log_.add_move(m);
									is_move_made_ = true;
									taken_pieces_block_->redo(move_log_);
									game_history_block_->redo(board_.get(), move_log_);
								}
								source_tile_ = nullptr;
								destination_tile_ = nullptr;
								moved_piece_ = nullptr;
							}
							else if (moved_piece_->get_piece_type() == piece_type::pawn && is_pawn_promotable(*this))
							{
								pawn_promotion_ = true;
							}
							else
							{
								pawn_promotion_ = false;
								std::shared_ptr<move> m = move_factory::create_move(board_, source_tile_->get_tile_coordinate(), destination_tile_->get_tile_coordinate());
								move_transition transition = board_->get_current_player()->make_move(m);
								if (transition.get_move_status() == move_status::done)
								{
									board_ = transition.get_transition_board();
									move_log_.add_move(m);
									is_move_made_ = true;
									taken_pieces_block_->redo(move_log_);
									game_history_block_->redo(board_.get(), move_log_);
								}
								source_tile_ = nullptr;
								destination_tile_ = nullptr;
								moved_piece_ = nullptr;
							}
						}
					}
			}
		}
	}
}

void game_board::observe()
{
	is_move_made_ = false;
	if (board_->get_current_player()->is_is_checkmate())
	{
		message_dialog_ = std::make_unique<message_dialog>(
			"Checkmate",
			board_->get_current_player()->get_opponent().lock()->stringify() + " won by checkmate!",
			sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75),
			[this]() -> void
			{
				undo_all_moves();
				message_dialog_.reset();
			});
		message_dialog_->set_active(true);
	}
	else if (board_->get_current_player()->is_in_stalemate())
	{
		message_dialog_ = std::make_unique<message_dialog>(
			"Stalemate",
			"Stalemate!",
			sf::Vector2f(window_->getSize().x / 2, window_->getSize().y / 2) - sf::Vector2f(200, 75),
			[this]() -> void
			{
				undo_all_moves();
				message_dialog_.reset();
			});
		message_dialog_->set_active(true);
	}
	else if (game_setup_->is_AI_player(board_->get_current_player().get()) &&
			 !board_->get_current_player()->is_is_checkmate() &&
			 !board_->get_current_player()->is_in_stalemate())
	{
		std::cout << board_->get_current_player()->stringify() << " is thinking..." << std::endl;
		ai->run();
	}
}

bool is_pawn_promotable(game_board &gb)
{
	if (gb.moved_piece_->get_piece_alliance() == alliance::white)
		return board_utils::second_row[gb.source_tile_->get_tile_coordinate()] && board_utils::first_row[gb.destination_tile_->get_tile_coordinate()];
	else
		return board_utils::seventh_row[gb.source_tile_->get_tile_coordinate()] && board_utils::eighth_row[gb.destination_tile_->get_tile_coordinate()];
}

void game_board::update_mouse_position()
{
	mouse_position_ = sf::Mouse::getPosition(*window_);
}

void game_board::update_tile_blocks()
{
	for (auto &tile_block : tile_blocks_)
	{
		std::vector<int> legal_moves = legal_move_destinations();

		if (tile_block.get_tile_rect().getGlobalBounds().contains(mouse_position_.x, mouse_position_.y))
		{
			tile_block.set_tile_rect_fill_color(sf::Color(0, 255, 255, 100));
		}
		else if (legal_moves.size() > 0 && std::find(legal_moves.begin(), legal_moves.end(), tile_block.get_tile_id()) != legal_moves.end())
		{
			tile_block.set_tile_rect_fill_color((tile_block.get_tile_id() / 8 + tile_block.get_tile_id()) % 2 == 0 ? sf::Color(/*White*/ 164, 212, 238) : sf::Color(/*Black*/ 0, 134, 138));
		}
		else if (board_->get_current_player()->is_in_check() && board_->get_current_player()->get_player_king()->get_piece_position() == tile_block.get_tile_id())
		{
			tile_block.set_tile_rect_fill_color(sf::Color(255, 0, 0, 100));
		}
		else if (move_log_.get_moves_count() > 0 && (move_log_.get_moves().back()->get_moved_piece()->get_piece_position() == tile_block.get_tile_id() || move_log_.get_moves().back()->get_destination_coordinate() == tile_block.get_tile_id()))
		{
			tile_block.set_tile_rect_fill_color(sf::Color(0, 255, 0, 100));
		}
		else if (source_tile_ != nullptr && source_tile_->get_tile_coordinate() == tile_block.get_tile_id())
		{
			tile_block.set_tile_rect_fill_color(sf::Color(255, 255, 0, 100));
		}
		else
		{
			tile_block.set_tile_rect_fill_color((tile_block.get_tile_id() / 8 + tile_block.get_tile_id()) % 2 == 0 ? sf::Color(/*White*/ 255, 250, 205) : sf::Color(/*Black*/ 89, 62, 26));
		}
	}
}

std::vector<int> game_board::legal_move_destinations()
{
	std::vector<int> move_destinations;
	if (moved_piece_ != nullptr && moved_piece_->get_piece_alliance() == board_->get_current_player()->get_player_alliance())
	{
		auto legal_moves = board_->get_current_player()->get_legal_moves();
		legal_moves.erase(
			std::remove_if(
				legal_moves.begin(),
				legal_moves.end(),
				[this](std::shared_ptr<move> m)
				{
					if (*m->get_moved_piece() == *moved_piece_)
						return board_->get_current_player()->make_move(m).get_move_status() != move_status::done;
					return true; }),
			legal_moves.end());
		for (auto m : legal_moves)
			move_destinations.push_back(m->get_destination_coordinate());
	}
	return move_destinations;
}

void game_board::update()
{
	process_events();
	update_mouse_position();
	update_tile_blocks();
	if (hourglass_.is_active())
		hourglass_.update();
	if (is_move_made_)
		observe();
}

void game_board::render_tile_blocks()
{
	for (auto &tile_block : tile_blocks_)
	{
		window_->draw(tile_block.get_tile_rect());
		if (board_->get_tile(tile_block.get_tile_id())->is_tile_occupied())
		{
			// Draw piece
			auto piece = board_->get_tile(tile_block.get_tile_id())->get_piece();
			switch (piece->get_piece_type())
			{
			case piece_type::pawn:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_pawn_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_pawn_sprite_);
				}
				else
				{
					black_pawn_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_pawn_sprite_);
				}
				break;
			case piece_type::knight:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_knight_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_knight_sprite_);
				}
				else
				{
					black_knight_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_knight_sprite_);
				}
				break;
			case piece_type::bishop:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_bishop_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_bishop_sprite_);
				}
				else
				{
					black_bishop_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_bishop_sprite_);
				}
				break;
			case piece_type::rook:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_rook_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_rook_sprite_);
				}
				else
				{
					black_rook_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_rook_sprite_);
				}
				break;
			case piece_type::queen:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_queen_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_queen_sprite_);
				}
				else
				{
					black_queen_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_queen_sprite_);
				}
				break;
			case piece_type::king:
				if (piece->get_piece_alliance() == alliance::white)
				{
					white_king_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(white_king_sprite_);
				}
				else
				{
					black_king_sprite_.setPosition(tile_block.get_tile_rect().getPosition().x, tile_block.get_tile_rect().getPosition().y);
					window_->draw(black_king_sprite_);
				}
				break;
			default:
				break;
			}
		}
	}
}

void game_board::render_pawn_promotion_option_pane()
{
	if (pawn_promotion_)
	{
		if (moved_piece_->get_piece_alliance() == alliance::white)
		{
			pawn_promotion_rect_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate()].get_tile_rect().getPosition());
			window_->draw(pawn_promotion_rect_);
			white_queen_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() + queen_offset].get_tile_rect().getPosition());
			window_->draw(white_queen_sprite_);
			white_knight_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() + knight_offset].get_tile_rect().getPosition());
			window_->draw(white_knight_sprite_);
			white_rook_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() + rook_offset].get_tile_rect().getPosition());
			window_->draw(white_rook_sprite_);
			white_bishop_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() + bishop_offset].get_tile_rect().getPosition());
			window_->draw(white_bishop_sprite_);
		}
		else
		{
			pawn_promotion_rect_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() - 24].get_tile_rect().getPosition());
			window_->draw(pawn_promotion_rect_);
			black_bishop_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() - bishop_offset].get_tile_rect().getPosition());
			window_->draw(black_bishop_sprite_);
			black_rook_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() - rook_offset].get_tile_rect().getPosition());
			window_->draw(black_rook_sprite_);
			black_knight_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() - knight_offset].get_tile_rect().getPosition());
			window_->draw(black_knight_sprite_);
			black_queen_sprite_.setPosition(tile_blocks_[destination_tile_->get_tile_coordinate() - queen_offset].get_tile_rect().getPosition());
			window_->draw(black_queen_sprite_);
		}
	}
}

void game_board::render()
{
	window_->clear();

	// Draw the background
	window_->draw(back_ground_);

	// Draw the board
	window_->draw(board_rect_);
	render_tile_blocks();
	render_pawn_promotion_option_pane();

	// Draw the taken pieces block
	taken_pieces_block_->draw(*window_);

	// Draw the game history block
	game_history_block_->draw(*window_);
	window_->setView(current_main_view_);

	// Draw the menu bar
	menu_bar_->draw(*window_);

	// Draw hourglass
	if (hourglass_.is_active())
		hourglass_.draw(*window_);

	// Draw the message dialog
	if ((message_dialog_ && message_dialog_->is_active()))
		message_dialog_->draw(*window_);

	// Draw the input dialog
	if ((input_dialog_ && input_dialog_->is_active()))
		input_dialog_->draw(*window_);

	if (game_setup_->get_active())
		game_setup_->draw(*window_);

	window_->display();
}

void game_board::undo_last_move()
{
	if (move_log_.get_moves_count() > 0)
	{
		board_ = board_->get_previous_board();
		move_log_.remove_move(move_log_.get_moves_count() - 1);
		game_history_block_->redo(board_.get(), move_log_);
		taken_pieces_block_->redo(move_log_);
	}
}

void game_board::undo_all_moves()
{
	move_log_.clear_moves();
	board_ = board::create_standard_board();
	game_history_block_->redo(board_.get(), move_log_);
	taken_pieces_block_->redo(move_log_);
}

/* game_board::ai_move_generator */

game_board::ai_move_generator::ai_move_generator(game_board *parent)
	: parent_(parent) {}

void game_board::ai_move_generator::run()
{
	std::future<std::shared_ptr<move>> future = std::async(std::launch::async, [this]
														   { return get_best_move(); });
	std::future_status move_calculation_status;
	parent_->hourglass_.set_active(true);
	do
	{
		move_calculation_status = future.wait_for(std::chrono::milliseconds(15));
		if (move_calculation_status == std::future_status::timeout)
		{
			parent_->render();
			parent_->update();
		}
		if (parent_->is_running() == false)
			break;

	} while (move_calculation_status != std::future_status::ready);
	if (parent_->is_running() == false)
	{
		std::cout << "Program aborted!\n"
				  << "Waiting for AI calculator thread to stop..."
				  << std::endl;
		future.get();
		return;
	}
	parent_->hourglass_.set_active(false);
	std::shared_ptr<move> best_move = future.get();
	done(best_move);
}

std::shared_ptr<move> game_board::ai_move_generator::get_best_move()
{
	alpha_beta ab(parent_->game_setup_->get_search_depth());
	std::shared_ptr<move> best_move = ab.execute(parent_->board_);
	return best_move;
}

void game_board::ai_move_generator::done(std::shared_ptr<move> best_move)
{
	parent_->board_ = parent_->board_->get_current_player()->make_move(best_move).get_transition_board();
	parent_->move_log_.add_move(best_move);
	parent_->taken_pieces_block_->redo(parent_->move_log_);
	parent_->game_history_block_->redo(parent_->board_.get(), parent_->move_log_);
	parent_->render();
	parent_->update();
	if (parent_->is_running())
		parent_->is_move_made_ = true;
}