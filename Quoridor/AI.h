#pragma once

#include "Global.h"
#include "GameService.h"

struct MoveNode {
	MoveNode() {}
	MoveNode(int s, int type, Vec2 p) {
		score = s;
		moveType = type;
		pos = p;
	}
	bool operator <(const MoveNode& t) const { return this->score < t.score; }
	int score;
	int moveType;
	Vec2 pos;
};

class AI
{
public:
	AI() = default;
	AI(int depth, long time, class GameService* game);
	std::pair<Vec2, int> getNextMove(void);
	long alphaBeta(int depth, int playerId, long alpha, long beta);
	int evaluate(void);
	long long getSystemTime(void);
	
	
private:
	bool isRuning;
	int _depth;
	int _time;
	class GameService* _game;
};

