#include "stdafx.h"
#include "GameServer.h"

int GameServer::GameHandle(void)
{
    isGameStart = true;

    onGameStart();

    while (isGameStart)
    {
        Order order;
        onBeforeOption(mTurn);

        if (mGameAI[mTurn] != nullptr) // �ûغ���AI����
        {
            order = onAIOption(mTurn);  // ��AI������һ��
        }
        else // ����ûغ�������ҿ���
        {
            order = onPlayerOption(mTurn); // ����Ҿ�����һ��
        }

        onExecuteOption(mTurn, order);

        onGameTurnEnd(mTurn, order);

        if (isEnd() != -1) // ��Ϸ�Ƿ����
        {
            onGameWin(isEnd());
            isGameStart = false;
        }
        mTurn = (++mTurn) % PLAYER_NUM; // ��ʾ��һ���غ�
    }

    onGameStop();

    return 0;
}

int GameServer::getCurrentTurn(void)
{
    return mTurn;
}

void GameServer::setWhoFirst(int id)
{ 
    mTurn = id; 
}

bool GameServer::isCurrentAITurn(void)
{
    return ((mGameAI[mTurn] != nullptr) ? true : false);
}

void GameServer::setGameAI(int id, int depth, long time)
{
    if (mGameAI[id] != nullptr) delete mGameAI[id];
    mGameAI[id] = new GameAI(depth, id, time, this);
}

void GameServer::setGamePlayer(int id)
{
    mGameAI[id] = nullptr;
}

void GameServer::resetGame(void)
{
    for (int index = 0; index < PLAYER_NUM; ++index)
    {
        if (mGameAI[index] != nullptr)
        {
            delete mGameAI[index];
            mGameAI[index] = nullptr;
        }
    }
    GameData::resetGame();
    mTurn = 0;
    isGameStart = false;
}
