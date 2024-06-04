#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <gui/TakenPieces.hpp>
#include <gui/GameBoard.hpp>
#include <engine/board/Move.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/Alliance.hpp>

taken_pieces_block::taken_pieces_block()
{
	if (
		!black_pawn_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackPawn.png") ||
		!white_pawn_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whitePawn.png") ||
		!black_bishop_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackBishop.png") ||
		!white_bishop_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteBishop.png") ||
		!black_knight_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackKnight.png") ||
		!white_knight_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteKnight.png") ||
		!black_rook_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackRook.png") ||
		!white_rook_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteRook.png") ||
		!black_queen_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/blackQueen.png") ||
		!white_queen_texture_.loadFromFile(std::string(PROJECT_SOURCE_DIR) + "/resources/pieces/whiteQueen.png"))
	{
		throw std::runtime_error("Failed to load piece textures");
	}

	black_pawn_texture_.setSmooth(true);
	white_pawn_texture_.setSmooth(true);
	black_bishop_texture_.setSmooth(true);
	white_bishop_texture_.setSmooth(true);
	black_knight_texture_.setSmooth(true);
	white_knight_texture_.setSmooth(true);
	black_rook_texture_.setSmooth(true);
	white_rook_texture_.setSmooth(true);
	black_queen_texture_.setSmooth(true);
	white_queen_texture_.setSmooth(true);

	taken_piece_area_rect_.setSize(sf::Vector2f(1.5f * TILE_WIDTH, 8 * TILE_HEIGHT));
	taken_piece_area_rect_.setPosition(0, 75);
	taken_piece_area_rect_.setFillColor(sf::Color(253, 245, 230));

	black_piece_area_position_ = sf::Vector2f(taken_piece_area_rect_.getPosition());
	white_piece_area_position_ = sf::Vector2f(taken_piece_area_rect_.getPosition() + sf::Vector2f(0, 4 * TILE_HEIGHT));
}

void taken_pieces_block::redo(move_log &ml)
{
	black_queen_sprites_.clear();
	white_queen_sprites_.clear();
	black_rook_sprites_.clear();
	white_rook_sprites_.clear();
	black_bishop_sprites_.clear();
	white_bishop_sprites_.clear();
	black_knight_sprites_.clear();
	white_knight_sprites_.clear();
	black_pawn_sprites_.clear();
	white_pawn_sprites_.clear();

	std::vector<std::shared_ptr<piece>> white_taken_pieces, black_taken_pieces;

	for (auto move : ml.get_moves())
	{
		if (move->is_attack())
		{
			auto taken_piece = move->get_attacked_piece();
			if (alliance_utils::is_white(taken_piece->get_piece_alliance()))
				white_taken_pieces.push_back(taken_piece);
			else if (alliance_utils::is_black(taken_piece->get_piece_alliance()))
				black_taken_pieces.push_back(taken_piece);
			else
				throw std::runtime_error("Invalid piece alliance");
		}
	}

	std::sort(white_taken_pieces.begin(), white_taken_pieces.end(), [](std::shared_ptr<piece> a, std::shared_ptr<piece> b) -> bool
			  { return a->get_piece_value() > b->get_piece_value(); });
	std::sort(black_taken_pieces.begin(), black_taken_pieces.end(), [](std::shared_ptr<piece> a, std::shared_ptr<piece> b) -> bool
			  { return a->get_piece_value() > b->get_piece_value(); });

	sf::Vector2f position = white_piece_area_position_ + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (auto piece : white_taken_pieces)
	{
		sf::Sprite sprite;
		switch (piece->get_piece_type())
		{
		case piece_type::queen:
			sprite.setTexture(white_queen_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			white_queen_sprites_.push_back(sprite);
			break;
		case piece_type::rook:
			sprite.setTexture(white_rook_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			white_rook_sprites_.push_back(sprite);
			break;
		case piece_type::bishop:
			sprite.setTexture(white_bishop_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			white_bishop_sprites_.push_back(sprite);
			break;
		case piece_type::knight:
			sprite.setTexture(white_knight_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			white_knight_sprites_.push_back(sprite);
			break;
		case piece_type::pawn:
			sprite.setTexture(white_pawn_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			white_pawn_sprites_.push_back(sprite);
			break;
		default:
			throw std::runtime_error("Invalid piece type");
		}
		if (position.x > white_piece_area_position_.x + 0.75f * TILE_WIDTH)
			position.x = white_piece_area_position_.x + 0.125f * TILE_WIDTH, position.y += TILE_HEIGHT / 2;
		else
			position.x += TILE_WIDTH * 0.75f;
	}

	position = black_piece_area_position_ + sf::Vector2f(0.125f * TILE_WIDTH, 0);
	for (auto piece : black_taken_pieces)
	{
		sf::Sprite sprite;
		switch (piece->get_piece_type())
		{
		case piece_type::queen:
			sprite.setTexture(black_queen_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			black_queen_sprites_.push_back(sprite);
			break;
		case piece_type::rook:
			sprite.setTexture(black_rook_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			black_rook_sprites_.push_back(sprite);
			break;
		case piece_type::bishop:
			sprite.setTexture(black_bishop_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			black_bishop_sprites_.push_back(sprite);
			break;
		case piece_type::knight:
			sprite.setTexture(black_knight_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			black_knight_sprites_.push_back(sprite);
			break;
		case piece_type::pawn:
			sprite.setTexture(black_pawn_texture_);
			sprite.setScale(TILE_WIDTH / sprite.getLocalBounds().width * 1 / 2, TILE_HEIGHT / sprite.getLocalBounds().height * 1 / 2);
			sprite.setPosition(position);
			black_pawn_sprites_.push_back(sprite);
			break;
		default:
			throw std::runtime_error("Invalid piece type");
		}
		if (position.x > black_piece_area_position_.x + 0.75f * TILE_WIDTH)
			position.x = black_piece_area_position_.x + 0.125f * TILE_WIDTH, position.y += TILE_HEIGHT / 2;
		else
			position.x += TILE_WIDTH * 0.75f;
	}
}

void taken_pieces_block::draw(sf::RenderWindow &window)
{
	window.draw(taken_piece_area_rect_);
	for (const auto &sprite : black_pawn_sprites_)
		window.draw(sprite);
	for (const auto &sprite : white_pawn_sprites_)
		window.draw(sprite);
	for (const auto &sprite : black_knight_sprites_)
		window.draw(sprite);
	for (const auto &sprite : white_knight_sprites_)
		window.draw(sprite);
	for (const auto &sprite : black_bishop_sprites_)
		window.draw(sprite);
	for (const auto &sprite : white_bishop_sprites_)
		window.draw(sprite);
	for (const auto &sprite : black_rook_sprites_)
		window.draw(sprite);
	for (const auto &sprite : white_rook_sprites_)
		window.draw(sprite);
	for (const auto &sprite : black_queen_sprites_)
		window.draw(sprite);
	for (const auto &sprite : white_queen_sprites_)
		window.draw(sprite);
}