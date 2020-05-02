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

AlphaBeta::AlphaBeta(int depth, long time)
{
    mThinkDepth = depth;
    mTimeLimited = time;
    isAIRunning = false;
}

Order AlphaBeta::getNextMove(int id, const GameData* gameData)
{
    isAIRunning = true;
    mSelfID = id;
    mRivalID = 1 - id;
    mGameData = new GameData(*gameData);
    long long startTime = getSystemTime();

    std::vector<MoveNode> moveVt;

    std::vector<Point> moves = mGameData->getNextMoveVaild(mSelfID, true);
    std::vector<std::pair<Point, int>> wallMoves = mGameData->getNextWallValid(mSelfID);

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
            //break;
        }
        long val;
        long alpha = -1000000;
        long beta = 1000000;
        MoveNode moveNode;

        for (size_t i = 0; i < size; i++)
        {
            int row = moveVt[i].order.point.row;
            int col = moveVt[i].order.point.col;

            if (moveVt[i].order.type == OrderType::MOVE)//表示走子
            {
                auto tempPos = mGameData->getCurrentPosition(mSelfID);
                mGameData->setMove(mSelfID, row, col, false);
                val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
                mGameData->setMove(mSelfID, tempPos.row, tempPos.col, false);
            }
            else
            {
                mGameData->setWall(mSelfID, moveVt[i].order.type, row, col, false);
                val = -alphaBeta(i_depth, mRivalID, -beta, -alpha);
                mGameData->setWall(-1, moveVt[i].order.type, row, col, false);
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

long AlphaBeta::alphaBeta(int depth, int pawn, long alpha, long beta)
{
    if (depth == 0)
    {
        long score = evaluate();
        if (pawn == mRivalID)
            score = -score;

        return score;
    }

    std::vector<Point> moves = mGameData->getNextMoveVaild(pawn, true);

    long val;

    for (auto move : moves)
    {
        Point tempPos = mGameData->getCurrentPosition(pawn);
        mGameData->setMove(pawn, move.row, move.col, false);
        val = -alphaBeta(depth - 1, 1 - pawn, -beta, -alpha);
        mGameData->setMove(pawn, tempPos.row, tempPos.col, false);
        if (val >= beta)
            return beta;
        if (val > alpha)
            alpha = val;
    }

    std::vector<std::pair<Point, int>> wallMoves = mGameData->getNextWallValid(pawn);

    for (auto wallMove : wallMoves)
    {
        mGameData->setWall(pawn, wallMove.second, (int)wallMove.first.row, (int)wallMove.first.col, false);
        val = -alphaBeta(depth - 1, 1 - pawn, -beta, -alpha);
        mGameData->setWall(-1, wallMove.second, (int)wallMove.first.row, (int)wallMove.first.col, false);

        if (val >= beta)
            return beta;
        if (val > alpha)
            alpha = val;
    }

    return alpha;
}

int AlphaBeta::evaluate(void) const
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

long long AlphaBeta::getSystemTime(void) const
{
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}
