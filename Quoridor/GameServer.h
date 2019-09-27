/*
 * �ó������ṩһ���򵥵���Ϸ�߼�����Ӧ�ӿڹ��û�ʹ��,�û�Ҳ����ֱ�Ӹ���
 * GameAI���GameData���ṩ�ĺ����������.
 * @author  ������
 * @version v1.3
 * @Date    2019.9.27
 */

#pragma once

#include "GameAI.h"
#include "GameData.h"

class GameServer : public GameData
{
public:

    /*
     * ������ϷAI
     * @param   id
     *          ��AI���Ƶ�id
     * @param   depth
     *          AI��˼�����,������δ���Ķ��ٲ�,��GameAI���캯��
     * @param   time
     *          AI�����ʱ������,��GameAI���캯��
     */
    void setGameAI(int id, int depth, long time);

    /*
     * ������Ϸ���
     * @param   id
     *          ��ҿ��Ƶ�id
     */
    void setGamePlayer(int id);

    /*
     * ���¿�ʼ��Ϸ
     */
    void resetGame(void);

    /*
     * ���ߵ�ǰ��Ϸ�غϵ����id
     */
    int getCurrentTurn(void);

    /*
     * ��������
     * @param   id
     *          ������ҵ�id
     */
    void setWhoFirst(int id);

    /*
     * �жϵ�ǰ�غ��Ƿ�ΪAI���ߵĻغ�
     */
    bool isCurrentAITurn(void);

    /*
     * @interface
     * Quoridor��Ϸ�Ļ����߼����£�
     * 
     * onGameStart(); // ��Ϸ��ʼ
     * while(){ // ��Ϸѭ��
     * onBeforeOption(); // ����Һ�AI�������֮ǰ
     * �����AI�غϵ���onAIOption(),��һغϵ���onPlayerOption();
     * onExecuteOption(); // ִ�о���
     * onGameTurnEnd(); // �غϼ�������
     * �ж��Ƿ�����Ҵﵽʤ������,���������onGameWin();
     * ��һ�غ� }
     * onGameStop(); //��Ϸ����
     */
    virtual int GameHandle(void);

    /*
     * @interface 
     * ��Ϸ��ʼ,��GameHandle����������ʱ����ø��麯��,�ú������ý����������Ϸѭ��
     * @default �޳���
     */
    virtual void onGameStart(void) {}

    /*
     * @interface
     * ��Ϸ����,����Ϸѭ�������󼴽��˳�GameHandle����ʱ���ø��麯��
     * @default �޳���
     */
    virtual void onGameStop(void) {}

    /*
     * @interface 
     * ��ǰ�غϵ���һ���AI����������ǰ���ø��麯��
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ����id
     * @default �޳���
     */
    virtual void onBeforeOption(int turn) {}

    /*
     * @interface 
     * �����ǰ��AI���ߵĻغ�,����AI����ʱ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ����id
     * @return  AI�����ó���һ���ľ���
     * @default return mGameAI[turn]->getNextMove(); //��AI������һ���Ĳ���
     */
    virtual Order onAIOption(int turn) { return mGameAI[turn]->getNextMove(); }

    /*
     * @interface
     * �����ǰ����Ҿ��ߵĻغ�,������Ҿ���ʱ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ����id
     * @return  ��ҵľ���
     * @note    �ú���������дʵ�ֶ�Ӧ�Ĺ���
     */
    virtual Order onPlayerOption(int turn) = 0;

    /*
     * @interface
     * ��AI������ҵó����غϵľ��ߺ�ִ�иú���,���ڽ�����ִ��
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ����id
     * @param   order
     *          ��ǰ��Ϸ�غϵ���ҵľ���
     * @default gotoOrder(turn, order); //ִ�о���
     */
    virtual void onExecuteOption(int turn, Order order) { gotoOrder(turn, order); }

    /*
     * @interface
     * �ھ���ִ�к�,���غϽ�Ҫ����,�ûغϸı�ǰ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ����id
     * @param   order
     *          ��ǰ��Ϸ�غϵ���ҵľ���
     * @default �޳���
     */
    virtual void onGameTurnEnd(int turn, Order order) {}

    /*
     * @interface
     * �ھ���ִ�к�,���غϽ�Ҫ����,�ûغϸı�ǰ���øú���
     * @param   player
     *          ��ʤ��ҵ�id
     * @default �޳���
     */
    virtual void onGameWin(int player) {}

private:

    GameAI * mGameAI[PLAYER_NUM] = { nullptr };
    int mTurn = 0;
    volatile bool isGameStart = false;
};

