#include <stdexcept>
#include <algorithm>

#include <engine/player/Player.hpp>
#include <engine/board/Move.hpp>
#include <engine/board/Board.hpp>
#include <engine/pieces/Piece.hpp>
#include <engine/pieces/King.hpp>
#include <engine/board/MoveTransition.hpp>

Player::Player(Board *board) : board(board)
{
}

King *Player::establishKing()
{
	for (auto piece : this->getActivePieces())
	{
		if (piece->getPieceType() == PieceType::KING)
		{
			return dynamic_cast<King *>(piece);
		}
	}

	throw std::runtime_error("No king found for player!");
}

bool Player::hasEscapeMoves() const
{
	for (auto move : this->legalMoves)
	{
		MoveTransition transition = makeMove(move);
		if (transition.getMoveStatus() == MoveStatus::DONE)
			return true;
	}
	return false;
}

std::vector<Move *> Player::calculateAttacksOnTile(const int piecePosition, std::vector<Move *> opponentMoves)
{
	std::vector<Move *> attackMoves;

	for (const auto move : opponentMoves)
		if (piecePosition == move->getDestinationCoordinate())
			attackMoves.push_back(move);
	return attackMoves;
}

bool Player::isMoveLegal(const Move *move) const
{
	return std::find(this->legalMoves.begin(), this->legalMoves.end(), move) != this->legalMoves.end();
}

King *Player::getPlayerKing() const
{
	return this->playerKing;
}

std::vector<Move *> Player::getLegalMoves() const
{
	return this->legalMoves;
}

bool Player::isInCheck() const
{
	return this->inCheck;
}

bool Player::isInCheckMate() const
{
	return this->inCheck && !hasEscapeMoves();
}

bool Player::isInStaleMate() const
{
	return !this->inCheck && !hasEscapeMoves();
}

bool Player::isCastled() const
{
	return false;
}

MoveTransition Player::makeMove(Move *move) const
{
	if (!isMoveLegal(move))
		return MoveTransition(this->board, move, MoveStatus::ILLEGAL_MOVE);
	const Board *transitionBoard = move->execute();
	std::vector<Move *> kingAttacks = Player::calculateAttacksOnTile(transitionBoard->getCurrentPlayer()->getOpponent()->getPlayerKing()->getPiecePosition(), transitionBoard->getCurrentPlayer()->getLegalMoves());
	if (!kingAttacks.empty())
		return MoveTransition(this->board, move, MoveStatus::LEAVES_PLAYER_IN_CHECK);
	return MoveTransition(transitionBoard, move, MoveStatus::DONE);
}

std::vector<Piece *> Player::getActivePieces() const
{
	throw std::logic_error("getActivePieces() must be overridden");
}

Alliance Player::getPlayerAlliance() const
{
	throw std::logic_error("This function must be overridden!");
}

const Player *Player::getOpponent() const
{
	throw std::logic_error("This function must be overridden!");
}

std::vector<Move *> Player::calculateKingCastles(const std::vector<Move *> playerLegals, const std::vector<Move *> opponentLegals) const
{
	throw std::logic_error("This function must be overridden!");
}

std::string Player::stringify() const
{
	throw std::logic_error("This function must be overridden!");
}