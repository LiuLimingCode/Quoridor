#pragma once
#include "Global.h"
#include "GameData.h"

struct MoveNode {
	MoveNode() {}
	MoveNode(int s, int type, CPoint p) {
		score = s;
		order = Order(type, p);
	}
	bool operator <(const MoveNode& t) const { return this->score < t.score; }
	int score;
	Order order;
};

class AI
{
public:
	AI() = default;
	AI(int depth, int id, long time, class GameData* gameData);
	Order getNextMove(void);
	
private:
	bool isRuning;
	int mSelfID;
	int mRivalID;
	int mThinkDepth;
	long mTimeLimited;
	class GameData* mGaveData;

	long alphaBeta(int depth, int playerId, long alpha, long beta);
	int evaluate(void);
	long long getSystemTime(void);
};

