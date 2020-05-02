#include "stdafx.h" // 如果不是MFC项目请删除该代码。 Please delete this code if it is not a MFC program
#include "GameServer.h"

int GameServer::GameHandle(void)
{
    isGameStart = true;

    onGameStart();

    while (isGameStart)
    {
        Order order;
        onBeforeOption(mTurn);

        if (mGameAI[mTurn] != nullptr) // 该回合由AI控制
        {
            order = onAIOption(mTurn);  // 由AI计算下一步
        }
        else // 否则该回合是由人控制
        {
            order = onPlayerOption(mTurn); // 由人决定下一步
        }

        onExecuteOption(mTurn, order);

        onGameTurnEnd(mTurn, order);

        if (isGameEnd() != -1) // 游戏是否结束
        {
            onGameWin(isGameEnd());
            isGameStart = false;
        }
        mTurn = (++mTurn) % PAWN_NUM; // 表示下一个回合
    }

    onGameOver();

    return 0;
}

int GameServer::getCurrentTurn(void) const
{
    return mTurn;
}

void GameServer::setWhoFirst(int id)
{ 
    mTurn = id; 
}

bool GameServer::isCurrentAITurn(void) const
{
    return ((mGameAI[mTurn] != nullptr) ? true : false);
}

GameAI* GameServer::getGameAI(int turn) const
{
    return mGameAI[turn];
}

void GameServer::setGameAI(int id, GameAI* ai)
{
    if (mGameAI[id] != nullptr) delete mGameAI[id];
    mGameAI[id] = ai;
}

void GameServer::setGamePlayer(int id)
{
    if (mGameAI[id] != nullptr) delete mGameAI[id];
    mGameAI[id] = nullptr;
}

void GameServer::resetGame(void)
{
    for (int index = 0; index < PAWN_NUM; ++index)
    {
        if (mGameAI[index] != nullptr)
        {
            delete mGameAI[index];
            mGameAI[index] = nullptr;
        }
    }
    GameData::resetGame(NUM_SQUARE);
    mTurn = 0;
    isGameStart = false;
}
