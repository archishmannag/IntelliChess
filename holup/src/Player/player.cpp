#include "../../include/player.h"

Player::Player(bool isWhite)
{
	this->isWhite = isWhite;
}

Player::~Player()
{
}

bool Player::getIsWhite()
{
	return isWhite;
}

int Player::getScore()
{
	return score;
}

bool Player::getIsInCheck()
{
	return isInCheck;
}

Player *Player::getOpponent()
{
	return opponent;
}

void Player::setScore(int score)
{
	this->score = score;
}

void Player::setIsInCheck(bool isInCheck)
{
	this->isInCheck = isInCheck;
}

void Player::setOpponent(Player *opponent)
{
	this->opponent = opponent;
}