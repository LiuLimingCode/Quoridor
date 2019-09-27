#include "stdafx.h"
#include "GameAI.h"
#include "GameData.h"
#include "GameGlobal.h"
#include <sys/timeb.h>
#include <algorithm>

struct MoveNode {
    MoveNode() {}
    MoveNode(int s, int type, Point p) {
        score = s;
        order = Order(type, p);
    }
    bool operator <(const MoveNode& t) const { return this->score < t.score; }
    int score = 0;
    Order order;
};

GameAI::GameAI(int depth, int id, long time, const GameData* gameData)
{
    mThinkDepth = depth;
    mSelfID = id;
    mRivalID = 1 - id;
    mTimeLimited = time;
    mGameDataBackup = gameData;
    isAIRunning = false;
}

Order GameAI::getNextMove(void)
{
    isAIRunning = true;
    mGameData = new GameData(*mGameDataBackup);
    long long startTime = getSystemTime();

    std::vector<MoveNode> moveVt;

    std::vector<Point> moves = mGameData->getMoveVaild(mSelfID);
    std::vector<std::pair<Point, int>> wallMoves = mGameData->getWallVaild(mSelfID);

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
//            log("%fs %d层", timeLen / 1000.0, i_depth);
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
                auto tempPos = mGameData->getCurrentPosition(mSelfID);
                mGameData->setMove(mSelfID, x, y);
                val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
                mGameData->setMove(mSelfID, tempPos.x, tempPos.y);
            }
            else
            {
                mGameData->setWall(mSelfID, moveVt[i].order.type, x, y);
                val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
                mGameData->resetWall(moveVt[i].order.type, x, y);
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
    delete mGameData;
    isAIRunning = false;

    return Order(ans.order.type, ans.order.point);
}

long GameAI::alphaBeta(int depth, int player, long alpha, long beta)
{
    if (depth == 0)
    {
        long score = evaluate();
        if (player == mRivalID)
            score = -score;

        return score;
    }

    std::vector<Point> moves = mGameData->getMoveVaild(player);

    long val;

    for (auto move : moves)
    {
        Point tempPos = mGameData->getCurrentPosition(player);
        mGameData->setMove(player, move.x, move.y);
        val = -alphaBeta(depth - 1, 1 - player, -beta, -alpha);
        mGameData->setMove(player, tempPos.x, tempPos.y);
        if (val >= beta)
            return beta;
        if (val > alpha)
            alpha = val;
    }

    std::vector<std::pair<Point, int>> wallMoves = mGameData->getWallVaild(player);

    for (auto wallMove : wallMoves)
    {
        mGameData->setWall(player, wallMove.second, (int)wallMove.first.x, (int)wallMove.first.y);
        val = -alphaBeta(depth - 1, 1 - player, -beta, -alpha);
        mGameData->resetWall(wallMove.second, (int)wallMove.first.x, (int)wallMove.first.y);

        if (val >= beta)
            return beta;
        if (val > alpha)
            alpha = val;
    }

    return alpha;
}

int GameAI::evaluate(void) const
{
    int selfShortLength = mGameData->getShortPath(mSelfID);
    int rivalShortLength = mGameData->getShortPath(mRivalID);
    int selfWallNum = mGameData->getCurrentWallNum(mSelfID);
    int rivalWallNum = mGameData->getCurrentWallNum(mRivalID);

    if (selfShortLength == 0)
        return 200;

    if (rivalShortLength == 0)
        return 0;

    int score = 100 - selfShortLength + rivalShortLength;
    //int score = 100 - selfShortLength + rivalShortLength - selfWallNum + rivalWallNum;

    return score;
}

long long GameAI::getSystemTime(void) const
{
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}
