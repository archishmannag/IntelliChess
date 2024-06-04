#include <stdexcept>

#include <engine/board/Board.hpp>
#include <engine/board/BoardUtils.hpp>
#include <engine/board/Move.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/Pawn.hpp>
#include <engine/pieces/Rook.hpp>
#include <engine/player/Player.hpp>

/*move*/

move::move(std::shared_ptr<board> b, int dc)
	: board_(b),
	  moved_piece_(nullptr),
	  destination_coordinate_(dc),
	  is_first_move_(false){};

move::move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc)
	: board_(b),
	  moved_piece_(mp),
	  destination_coordinate_(dc),
	  is_first_move_(mp->is_first_move()){};

bool move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const move *otherMove = dynamic_cast<const move *>(&other))
		return false;
	return get_current_coordinate() == other.get_current_coordinate() && get_destination_coordinate() == other.get_destination_coordinate() && *get_moved_piece() == *other.get_moved_piece();
}

int move::get_destination_coordinate() const
{
	return destination_coordinate_;
}

int move::get_current_coordinate() const
{
	return moved_piece_->get_piece_position();
}

std::shared_ptr<piece> move::get_moved_piece() const
{
	return moved_piece_;
}

std::shared_ptr<board> move::get_board() const
{
	return board_.lock();
}

bool move::is_attack() const
{
	return false;
}

bool move::is_castling_move() const
{
	return false;
}

std::shared_ptr<piece> move::get_attacked_piece() const
{
	return nullptr;
}

std::shared_ptr<board> move::execute() const
{
	if (auto board_ptr = board_.lock())
	{
		board_builder builder;
		// Add all the pieces of same alliance to the new board except the moved piece
		for (auto piece : board_ptr->get_current_player()->get_active_pieces())
			if (!(*get_moved_piece() == *piece))
				builder.set_piece(piece);
		// Add all the pieces of opponent alliance to the new board
		for (auto piece : board_ptr->get_current_player()->get_opponent().lock()->get_active_pieces())
			builder.set_piece(piece);
		// Move the moved piece to the destination coordinate
		builder.set_piece(moved_piece_->move_piece(this));
		builder.set_move_maker(board_ptr->get_current_player()->get_opponent().lock()->get_player_alliance());
		builder.set_transition_move(std::make_shared<move>(*this));
		builder.set_previous_board(board_ptr->shared_from_this());
		return builder.build();
	}
	throw std::runtime_error("Board expired!");
}

std::string move::stringify() const
{
	throw std::logic_error("Use subclass functions!");
}

/*major_move*/

major_move::major_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc)
	: move(b, mp, dc){};

bool major_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const major_move *otherMajorMove = dynamic_cast<const major_move *>(&other))
		return move::operator==(other);
	return false;
}

std::string major_move::stringify() const
{
	return moved_piece_->stringify() + board_utils::get_position_at_coordinate(destination_coordinate_);
}

/*attack_move*/

attack_move::attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc)
	: move(b, mp, dc),
	  attacked_piece_(std::move(ap)){};

bool attack_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const attack_move *otherAttackMove = dynamic_cast<const attack_move *>(&other))
		return move::operator==(other) && *get_attacked_piece() == *otherAttackMove->get_attacked_piece();
	return false;
}

bool attack_move::is_attack() const
{
	return true;
}

std::shared_ptr<piece> attack_move::get_attacked_piece() const
{
	return attacked_piece_;
}

/*pawn_promotion*/

pawn_promotion::pawn_promotion(std::shared_ptr<move> im, std::shared_ptr<piece> pp)
	: move(im->get_board(), im->get_moved_piece(), im->get_destination_coordinate()),
	  input_move_(im),
	  promoted_pawn_(std::dynamic_pointer_cast<pawn>(im->get_moved_piece())),
	  promoted_piece_(pp) {}

bool pawn_promotion::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const pawn_promotion *otherPawnPromotion = dynamic_cast<const pawn_promotion *>(&other))
		return move::operator==(other) && *get_promoted_piece() == *otherPawnPromotion->get_promoted_piece();
	return false;
}

std::shared_ptr<board> pawn_promotion::execute() const
{
	std::shared_ptr<board> pawn_moved_board = this->input_move_->execute();
	if ((bool)pawn_moved_board)
	{
		board_builder builder;
		for (auto piece : pawn_moved_board->get_current_player()->get_opponent().lock()->get_active_pieces())
			if (!(*piece == *promoted_pawn_))
				builder.set_piece(piece);
		for (auto piece : pawn_moved_board->get_current_player()->get_active_pieces())
			builder.set_piece(piece);
		builder.set_piece(promoted_piece_->move_piece(this));
		builder.set_move_maker(pawn_moved_board->get_current_player()->get_player_alliance());
		builder.set_transition_move(std::make_shared<pawn_promotion>(*this));
		builder.set_previous_board(board_.lock()->shared_from_this());
		return builder.build();
	}
	throw std::runtime_error("Board expired!");
}

bool pawn_promotion::is_attack() const
{
	return input_move_->is_attack();
}

std::shared_ptr<piece> pawn_promotion::get_attacked_piece() const
{
	return input_move_->get_attacked_piece();
}

std::shared_ptr<piece> pawn_promotion::get_promoted_piece() const
{
	return promoted_piece_;
}

std::string pawn_promotion::stringify() const
{
	return input_move_->stringify() + '=' + promoted_piece_->stringify();
}

/*major_attack_move*/

major_attack_move::major_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc)
	: attack_move(b, mp, ap, dc){};

bool major_attack_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const major_attack_move *otherMajorAttackMove = dynamic_cast<const major_attack_move *>(&other))
		return attack_move::operator==(other);
	return false;
}

std::string major_attack_move::stringify() const
{
	return moved_piece_->stringify() + "x" + board_utils::get_position_at_coordinate(destination_coordinate_);
}

/*pawn_move*/

pawn_move::pawn_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc)
	: move(b, mp, dc){};

bool pawn_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const pawn_move *otherPawnMove = dynamic_cast<const pawn_move *>(&other))
		return move::operator==(other);
	return false;
}

std::string pawn_move::stringify() const
{
	return board_utils::get_position_at_coordinate(destination_coordinate_);
}

/*pawn_attack_move*/

pawn_attack_move::pawn_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc)
	: attack_move(b, mp, ap, dc){};

bool pawn_attack_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const pawn_attack_move *otherPawnAttackMove = dynamic_cast<const pawn_attack_move *>(&other))
		return attack_move::operator==(other);
	return false;
}

std::string pawn_attack_move::stringify() const
{
	return board_utils::get_position_at_coordinate(moved_piece_->get_piece_position()).substr(0, 1) + "x" +
		   board_utils::get_position_at_coordinate(destination_coordinate_);
}

/*pawn_en_passant_attack_move*/

pawn_en_passant_attack_move::pawn_en_passant_attack_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, std::shared_ptr<piece> ap, int dc)
	: pawn_attack_move(b, mp, ap, dc){};

std::shared_ptr<board> pawn_en_passant_attack_move::execute() const
{
	if (auto board_ptr = board_.lock())
	{
		board_builder builder;
		for (auto piece : board_ptr->get_current_player()->get_active_pieces())
			if (!(*piece == *get_moved_piece()))
				builder.set_piece(piece);
		for (auto piece : board_ptr->get_current_player()->get_opponent().lock()->get_active_pieces())
			if (!(*piece == *get_attacked_piece()))
				builder.set_piece(piece);
		builder.set_piece(moved_piece_->move_piece(this));
		builder.set_move_maker(board_ptr->get_current_player()->get_opponent().lock()->get_player_alliance());
		builder.set_transition_move(std::make_shared<pawn_en_passant_attack_move>(*this));
		builder.set_previous_board(board_ptr->shared_from_this());
		return builder.build();
	}
	throw std::runtime_error("Board expired!");
}

bool pawn_en_passant_attack_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const pawn_en_passant_attack_move *otherPawnEnPassantAttackMove = dynamic_cast<const pawn_en_passant_attack_move *>(&other))
		return pawn_attack_move::operator==(other);
	return false;
}

/*pawn_jump*/

pawn_jump::pawn_jump(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc)
	: move(b, mp, dc){};

std::shared_ptr<board> pawn_jump::execute() const
{
	if (auto board_ptr = board_.lock())
	{
		board_builder builder;
		// Add all the pieces of same alliance to the new board except the moved piece
		for (auto piece : board_ptr->get_current_player()->get_active_pieces())
			if (!(*get_moved_piece() == *piece))
				builder.set_piece(piece);
		// Add all the pieces of opponent alliance to the new board
		for (auto piece : board_ptr->get_current_player()->get_opponent().lock()->get_active_pieces())
			builder.set_piece(piece);
		// Move the moved piece to the destination coordinate
		std::shared_ptr<pawn> movedPawn = std::dynamic_pointer_cast<pawn>(this->get_moved_piece()->move_piece(this));
		builder.set_piece(movedPawn);
		builder.set_en_passant_pawn(movedPawn);
		builder.set_move_maker(board_ptr->get_current_player()->get_opponent().lock()->get_player_alliance());
		builder.set_transition_move(std::make_shared<pawn_jump>(*this));
		builder.set_previous_board(board_ptr->shared_from_this());
		return builder.build();
	}
	throw std::runtime_error("Board expired!");
}

std::string pawn_jump::stringify() const
{
	return board_utils::get_position_at_coordinate(this->destination_coordinate_);
}

/*castle_move*/

castle_move::castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd)
	: move(b, mp, dc),
	  castling_rook_(cr),
	  castling_rook_start_square_(crss),
	  castling_rook_destination_(crd){};

bool castle_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const castle_move *otherCastleMove = dynamic_cast<const castle_move *>(&other))
		return move::operator==(other) && *get_castling_rook() == *otherCastleMove->get_castling_rook();
	return false;
}

std::shared_ptr<rook> castle_move::get_castling_rook() const
{
	return castling_rook_;
}

bool castle_move::is_castling_move() const
{
	return true;
}

std::shared_ptr<board> castle_move::execute() const
{
	if (auto board_ptr = board_.lock())
	{
		board_builder builder;
		// Add all the pieces of same alliance to the new board except the moved piece and the castle rook
		for (auto piece : board_ptr->get_current_player()->get_active_pieces())
			if (!(*get_moved_piece() == *piece) && !(*get_castling_rook() == *piece))
				builder.set_piece(piece);
		// Add all the pieces of opponent alliance to the new board
		for (auto piece : board_ptr->get_current_player()->get_opponent().lock()->get_active_pieces())
			builder.set_piece(piece);
		// Move the moved piece (King) to the destination coordinate
		builder.set_piece(moved_piece_->move_piece(this));
		// Move the castle rook to the destination coordinate
		builder.set_piece(std::make_shared<rook>(castling_rook_destination_, castling_rook_->get_piece_alliance(), false));
		builder.set_move_maker(board_ptr->get_current_player()->get_opponent().lock()->get_player_alliance());
		builder.set_transition_move(std::make_shared<castle_move>(*this));
		builder.set_previous_board(board_ptr->shared_from_this());
		return builder.build();
	}
	throw std::runtime_error("Board expired!");
}

/*king_side_castle_move*/

king_side_castle_move::king_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd)
	: castle_move(b, mp, dc, cr, crss, crd){};

bool king_side_castle_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const king_side_castle_move *otherKingSideCastleMove = dynamic_cast<const king_side_castle_move *>(&other))
		return castle_move::operator==(other);
	return false;
}

std::string king_side_castle_move::stringify() const
{
	return std::string("O-O");
}

/*queen_side_castle_move*/

queen_side_castle_move::queen_side_castle_move(std::shared_ptr<board> b, std::shared_ptr<piece> mp, int dc, std::shared_ptr<rook> cr, int crss, int crd)
	: castle_move(b, mp, dc, cr, crss, crd){};

bool queen_side_castle_move::operator==(const move &other) const
{
	if (this == &other)
		return true;
	if (const queen_side_castle_move *otherQueenSideCastleMove = dynamic_cast<const queen_side_castle_move *>(&other))
		return castle_move::operator==(other);
	return false;
}

std::string queen_side_castle_move::stringify() const
{
	return std::string("O-O-O");
}

/*null_move*/

null_move::null_move() : move(nullptr, -1){};

std::shared_ptr<board> null_move::execute() const
{
	throw std::logic_error("Cannot execute the null move!");
}

std::string null_move::stringify() const
{
	return std::string("Null Move");
}

/*Namespace move_factory*/

std::shared_ptr<move> move_factory::create_move(std::shared_ptr<board> b, int cc, int dc)
{
	std::shared_ptr<move> selected_move = nullptr;
	for (auto move : b->get_all_legal_moves())
		if (move->get_current_coordinate() == cc && move->get_destination_coordinate() == dc)
		{
			selected_move = move;
			break;
		}
	return selected_move;
}

std::shared_ptr<move> move_factory::create_move(std::shared_ptr<board> b, int cc, int dc, piece_type ppt)
{
	std::shared_ptr<move> selected_move = nullptr;
	for (auto move : b->get_all_legal_moves())
		if (move->get_current_coordinate() == cc &&
			move->get_destination_coordinate() == dc &&
			typeid(*move) == typeid(pawn_promotion) &&
			(std::dynamic_pointer_cast<pawn_promotion>(move))->get_promoted_piece()->get_piece_type() == ppt)
		{
			selected_move = move;
			break;
		}
	return selected_move;
}