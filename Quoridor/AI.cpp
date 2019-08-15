#include "stdafx.h"
#include "AI.h"
#include "GameData.h"
#include <sys/timeb.h>
#include <algorithm>

AI::AI(int depth, int id, long time, GameData* gameData)
{
	mThinkDepth = depth;
	mSelfID = id;
	mRivalID = 1 - id;
	mTimeLimited = time;
	mGaveData = gameData;
	isRuning = false;
}

Order AI::getNextMove(void)
{
	isRuning = true;
	long long startTime = getSystemTime();

	std::vector<MoveNode> moveVt;

	std::vector<CPoint> moves = mGaveData->getMoveVaild(mSelfID);
	std::vector<std::pair<CPoint, int>> wallMoves = mGaveData->getWallVaild(mSelfID);

	for (auto move : moves)
	{
		//2表示落子
		moveVt.push_back(MoveNode(0, 2, move));
	}


	for (auto wallMove : wallMoves)
	{
		moveVt.push_back(MoveNode(0, wallMove.second, wallMove.first));
	}

	auto size = moveVt.size();
	MoveNode ans;

	for (int i_depth = 1; i_depth <= mThinkDepth; i_depth++)
	{
		long long timeLen = getSystemTime() - startTime;

		if (timeLen >= mTimeLimited)
		{
//			log("%fs %d层", timeLen / 1000.0, i_depth);
			break;
		}
		long val;
		long alpha = -1000000;
		long beta = 1000000;
		MoveNode moveNode;

		for (size_t i = 0; i < size; i++)
		{
			int x = moveVt[i].order.point.x;
			int y = moveVt[i].order.point.y;

			if (moveVt[i].order.type == 2)//表示走子
			{
				auto tempPos = mGaveData->getCurrentPosition(mSelfID);
				mGaveData->setMove(mSelfID, x, y);
				val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
				mGaveData->setMove(mSelfID, tempPos.x, tempPos.y);
			}
			else
			{
				mGaveData->setWall(mSelfID, moveVt[i].order.type, x, y);
				val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
				mGaveData->resetWall(moveVt[i].order.type, x, y);
			}

			if (val > alpha)
			{
				moveNode = moveVt[i];
				alpha = val;
			}
			moveVt[i].score = alpha;
		}

		ans = moveNode;

		std::sort(moveVt.begin(), moveVt.end());
	}

	isRuning = false;

	return Order(ans.order.type, ans.order.point);
}

long AI::alphaBeta(int depth, int player, long alpha, long beta)
{
	if (depth == 0)
	{
		long score = evaluate();
		if (player == mRivalID)
			score = -score;

		return score;
	}

	std::vector<CPoint> moves = mGaveData->getMoveVaild(player);

	long val;

	for (auto move : moves)
	{
		CPoint tempPos = mGaveData->getCurrentPosition(player);
		mGaveData->setMove(player, move.x, move.y);
		val = -alphaBeta(depth - 1, 1 - player, -beta, -alpha);
		mGaveData->setMove(player, tempPos.x, tempPos.y);
		if (val >= beta)
			return beta;
		if (val > alpha)
			alpha = val;
	}

	std::vector<std::pair<CPoint, int>> wallMoves = mGaveData->getWallVaild(player);

	for (auto wallMove : wallMoves)
	{
		mGaveData->setWall(player, wallMove.second, (int)wallMove.first.x, (int)wallMove.first.y);
		val = -alphaBeta(depth - 1, 1 - player, -beta, -alpha);
		mGaveData->resetWall(wallMove.second, (int)wallMove.first.x, (int)wallMove.first.y);

		if (val >= beta)
			return beta;
		if (val > alpha)
			alpha = val;
	}

	return alpha;
}

int AI::evaluate(void)
{
	int selfShortLength = mGaveData->getShortPath(mSelfID, mGaveData->getCurrentPosition(mSelfID));
	int rivalShortLength = mGaveData->getShortPath(mRivalID, mGaveData->getCurrentPosition(mRivalID));
	int selfWallNum = mGaveData->getCurrentWallNum(mSelfID);
	int rivalWallNum = mGaveData->getCurrentWallNum(mRivalID);

	if (selfShortLength == 0)
		return 200;

	if (rivalShortLength == 0)
		return 0;

	int score = 100 - selfShortLength + rivalShortLength;
	//    int score = 100 - cmpShortLength;
	return score;
}

long long AI::getSystemTime(void)
{
	struct timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
}
