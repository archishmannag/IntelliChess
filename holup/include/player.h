#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	bool isWhite;
	int score;
	bool isInCheck;
	Player *opponent;

public:
	Player(bool isWhite);
	~Player();
	bool getIsWhite();
	int getScore();
	bool getIsInCheck();
	Player *getOpponent();
	void setScore(int score);
	void setIsInCheck(bool isInCheck);
	void setOpponent(Player *opponent);
};

#endif