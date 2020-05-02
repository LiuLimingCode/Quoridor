/*
 * Quoridor��ϷAI
 * @author  ������
 * @version v1.3
 * @Date    2019.9.27
 */

#pragma once

#include "GameData.h"
#include "GameGlobal.h"

class GameAI
{
public:
    virtual Order getNextMove(int id, const GameData* gameData) = 0;
};

class AlphaBeta : public GameAI
{
public:

    /*
     * ���ʼ������
     * @param   depth
     *          AI��˼�����,������δ���Ķ��ٲ�
     * @param   time
     *          AI�����ʱ������,��AI��˼����ȴ�,�����ĵ�ʱ���,���Ѿ����ĵ�ʱ����ڸ�ʱ������,AIֹͣ����
     */
    AlphaBeta(int depth, long time);

    /*
     * AI������һ���Ĳ���
     * @param   id
     *          AI����Ϸ�п��Ƶ�����
     * @param   gameData
     *          ��Ϸ����
     * @return  AI��һ����ָ��
     */
    virtual Order getNextMove(int id, const GameData* gameData);

    /*
     * AI�Ƿ����ڼ���
     * @return  AI�Ƿ����ڼ���
     */
    bool isRunning() const { return isAIRunning; }

protected:

    /*
     * alphaBeta�㷨����,AI��getNextMove�лῼ�����м�����һ�������п��ܵ��ж��ͶԷ�����Ӧ��ȡ�Ĵ�ʩ
     * ����alphaBeta�Ը��ж���������,����AI����������ж��ж����Լ���������һ����Ϊ��һ��.
     */
    virtual long alphaBeta(int depth, int pawn, long alpha, long beta);

    /*
     * ��Ҫ!
     * alphaBeta�����ۺ���,�ú�����ֱ�Ӿ���AI��ĳһ�ж������۷�ʽ,�ĺ�����ֱ�Ӿ���AI��ǿ��
     * ʾ��;
     * 1. �÷� = 100 - �ҷ����յ����̾��� + �з����յ����̾���
     *    �����ۺ����ᵼ��AI�Ĳ��Ը��߽�����
     * 2. �÷� = 100  - �ҷ����յ����̾��� + �з����յ����̾��� - �ҷ�ǽ������ + �з�ǽ������
     *    �����ۺ���ʹ��AI�ڼ�߽����Ե�ͬʱ,�ֲ�����ȵ�����ǽ������
     */
    virtual int evaluate(void) const;

    long long getSystemTime(void) const;

protected:

    bool isAIRunning = false;
    int mSelfID = 0;
    int mRivalID = 0;
    int mThinkDepth = 0;
    long mTimeLimited = 0;
    GameData* mGameData = nullptr;
};
