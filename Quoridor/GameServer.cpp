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
        else // ����ûغ������˿���
        {
            order = onPlayerOption(mTurn); // ���˾�����һ��
        }

        onExecuteOption(mTurn, order);

        onGameTurnEnd(mTurn, order);

        if (isGameEnd() != -1) // ��Ϸ�Ƿ����
        {
            onGameWin(isGameEnd());
            isGameStart = false;
        }
        mTurn = (++mTurn) % PAWN_NUM; // ��ʾ��һ���غ�
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
