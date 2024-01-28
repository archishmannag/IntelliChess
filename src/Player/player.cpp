#include "player.h"

class Player
{
private:
	int score;
	bool isInCheck;
	Player *opponent;

public:
	Player();
	~Player();
};