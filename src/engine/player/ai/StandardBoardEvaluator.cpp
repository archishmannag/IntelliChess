#include <engine/player/ai/StandardBoardEvaluator.hpp>
#include <engine/player/ai/PawnStructureAnalyzer.hpp>
#include <engine/board/Board.hpp>
#include <engine/board/Move.hpp>
#include <engine/player/Player.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/Alliance.hpp>

// The following values are used to calculate the score of a player
namespace
{
	int checkmate_bonus = 10000,
		check_bonus = 45,
		castle_bonus = 25,
		mobility_multiplier = 5,
		attack_multiplier = 1,
		two_bishops_bonus = 25,
		depth_bonus = 100;
}

namespace
{
	int mobility(const player *p)
	{
		return mobility_multiplier * static_cast<int>(((static_cast<int>(p->get_legal_moves().size())) * 10.f) / static_cast<int>(p->get_opponent().lock()->get_legal_moves().size()));
	}

	int check_value(const player *p)
	{
		return p->get_opponent().lock()->is_in_check() ? check_bonus : 0;
	}

	int bonus_on_depth(int d)
	{
		return d == 0 ? 1 : depth_bonus * d;
	}

	int king_threats(const player *p, int d)
	{
		return p->get_opponent().lock()->is_is_checkmate() ? checkmate_bonus * bonus_on_depth(d) : check_value(p);
	}

	int attacks(const player *p)
	{
		int attack_score = 0;
		for (std::shared_ptr<move> m : p->get_legal_moves())
			if (m->is_attack())
			{
				std::shared_ptr<piece> moved_piece = m->get_moved_piece(),
									   attacked_piece = m->get_attacked_piece();
				if (moved_piece->get_piece_value() <= attacked_piece->get_piece_value())
					attack_score++;
			}
		return attack_score + attack_multiplier;
	}

	int has_castled(const player *p)
	{
		return p->is_castled() ? castle_bonus : 0;
	}

	int piece_value(const player *p)
	{
		int total_piece_value = 0,
			num_bishops = 0;
		for (std::shared_ptr<piece> piece_ptr : p->get_active_pieces())
		{
			total_piece_value += piece_ptr->get_piece_value() + alliance_utils::get_location_bonus(piece_ptr.get());
			if (piece_ptr->get_piece_type() == piece_type::bishop)
				num_bishops++;
		}
		return total_piece_value + (num_bishops == 2 ? two_bishops_bonus : 0);
	}

	int pawn_structure(const player *p)
	{
		return pawn_structure_analyzer::pawn_structure_score(p);
	}

	int player_score(const player *p, int d)
	{
		return mobility(p) +
			   king_threats(p, d) +
			   attacks(p) +
			   has_castled(p) +
			   piece_value(p) +
			   pawn_structure(p);
	}
} // namespace

int standard_board_evaluator::evaluate(const board &b, int d)
{
	return player_score(b.get_white_player().get(), d) - player_score(b.get_black_player().get(), d);
}

std::string standard_board_evaluator::evaluation_details(const board &b, const int d)
{
	return "White Mobility : " + std::to_string(mobility(b.get_white_player().get())) + '\n' +
		   "White King Threats : " + std::to_string(king_threats(b.get_white_player().get(), d)) + '\n' +
		   "White Attacks : " + std::to_string(attacks(b.get_white_player().get())) + '\n' +
		   "White Castle : " + std::to_string(has_castled(b.get_white_player().get())) + '\n' +
		   "White Piece Value : " + std::to_string(piece_value(b.get_white_player().get())) + '\n' +
		   "White Pawn Structure : " + std::to_string(pawn_structure(b.get_white_player().get())) + '\n' +
		   "------------------------------\n" +
		   "Black Mobility : " + std::to_string(mobility(b.get_black_player().get())) + '\n' +
		   "Black King Threats : " + std::to_string(king_threats(b.get_black_player().get(), d)) + '\n' +
		   "Black Attacks : " + std::to_string(attacks(b.get_black_player().get())) + '\n' +
		   "Black Castle : " + std::to_string(has_castled(b.get_black_player().get())) + '\n' +
		   "Black Piece Value : " + std::to_string(piece_value(b.get_black_player().get())) + '\n' +
		   "Black Pawn Structure : " + std::to_string(pawn_structure(b.get_black_player().get())) + "\n\n" +
		   "Final Score : " + std::to_string(evaluate(b, d));
}