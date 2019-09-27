/*
 * Quoridor��ϷAI
 * @author  ������
 * @version v1.3
 * @Date    2019.9.27
 */

#pragma once

#include "GameData.h"
#include "GameGlobal.h"

class Order;

class GameAI
{
public:

    /*
     * GameAI���ʼ������
     * @param   depth
     *          AI��˼�����,������δ���Ķ��ٲ�
     * @param   id
     *          AI����Ϸ�п��Ƶ����
     * @param   time
     *          AI�����ʱ������,��AI��˼����ȴ�,�����ĵ�ʱ���,���Ѿ����ĵ�ʱ����ڸ�ʱ������,AIֹͣ����
     * @param   gameData
     *          ��Ϸ����
     */
    GameAI(int depth, int id, long time, const class GameData* gameData);

    /*
     * AI������һ���Ĳ���
     * @return  AI��һ����ָ��
     */
    Order getNextMove(void);
    
    /*
     * AI�Ƿ����ڼ���
     * @return  AI�Ƿ����ڼ���
     */
    bool isRunning() const{ return isAIRunning; }

protected:

    /*
     * alphaBeta�㷨����,AI��getNextMove�лῼ�����м�����һ�������п��ܵ��ж��ͶԷ�����Ӧ��ȡ�Ĵ�ʩ
     * ����alphaBeta�Ը��ж���������,����AI����������ж��ж����Լ���������һ����Ϊ��һ��.
     */
    long alphaBeta(int depth, int player, long alpha, long beta);

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
    
private:

    bool isAIRunning = false;
    int mSelfID = 0;
    int mRivalID = 0;
    int mThinkDepth = 0;
    long mTimeLimited = 0;

    class GameData* mGameData = nullptr;
    const class GameData* mGameDataBackup = nullptr;
    // ����AI�ڼ���Ĺ����л���ʱ�޸���Ϸ����,Ϊ��֤����ȫ��,mGameDataBackup�����洢����������Ϸ����
    // mGameDataΪ���ݵĿ���,���ж���Ϸ���ݵĸĶ�����mGameData�Ͻ���,���Բ�Ӱ��ԭ����.
};