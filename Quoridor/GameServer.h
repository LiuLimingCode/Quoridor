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
     * ����AI���Ƶ�����id
     * @param   id
     *          AI����Ϸ�п��Ƶ�����
     * @param   ai
     *          ���õ�AI
     * @note    �˺������������û�������GameAI��
     */
    void setGameAI(int id, GameAI* ai);

    /*
     * �����˿��Ƶ�����id
     * @param   id
     *          �˿��Ƶ�����id
     */
    void setGamePlayer(int id);

    /*
     * ���¿�ʼ��Ϸ
     */
    void resetGame(void);

    /*
     * �õ���ǰ���ĸ����ӵĻغ�
     */
    int getCurrentTurn(void) const;

    /*
     * ��������
     * @param   id
     *          �������ӵ�id
     */
    void setWhoFirst(int id);

    /*
     * �жϵ�ǰ�غ��Ƿ�ΪAI���ߵĻغ�
     * @return  true = ��ǰΪAI���߻غ�;false = ��ǰΪ�˾��߻غ�
     */
    bool isCurrentAITurn(void) const;

    /*
     * ���ؾ���ĳ���غϵ���ϷAI
     * @param   turn
     *          ���ؾ��߸ûغϵ���ϷAI
     * @noto    �����ǰ�غ����˾���,����nullptr
     */
    GameAI* getGameAI(int turn) const;

    /*
     * @interface
     * Quoridor��Ϸ�Ļ����߼����£�
     * 
     * onGameStart(); // ��Ϸ��ʼ
     * while() { // ��Ϸѭ��
     * onBeforeOption(); // ���˻�AI�������֮ǰ
     * �����AI���߻غϵ���onAIOption(),�˾��߻غϵ���onPlayerOption();
     * onExecuteOption(); // ִ�о���
     * onGameTurnEnd(); // �غϼ�������
     * �ж��Ƿ������Ӵﵽʤ������,���������onGameWin();
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
    virtual void onGameOver(void) {}

    /*
     * @interface 
     * ��ǰ�غϵ��˻���AI����������ǰ���ø��麯��
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ�����id
     * @default �޳���
     */
    virtual void onBeforeOption(int turn) {}

    /*
     * @interface 
     * �����ǰ��AI���ߵĻغ�,����AI����ʱ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ�����id
     * @return  AI�����ó���һ���ľ���
     * @default return getGameAI(turn)->getNextMove(); //��AI������һ���Ĳ���
     */
    virtual Order onAIOption(int turn) { return getGameAI(turn)->getNextMove(turn, this); }

    /*
     * @interface
     * �����ǰ���˾��ߵĻغ�,������Ҿ���ʱ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ�����id
     * @return  �˵ľ���
     * @note    �ú���������дʵ�ֶ�Ӧ�Ĺ���
     */
    virtual Order onPlayerOption(int turn) = 0;

    /*
     * @interface
     * ��AI�����˵ó����غϵľ��ߺ�ִ�иú���,���ڽ�����ִ��
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ�����id
     * @param   order
     *          ��ǰ��Ϸ�غ��˻���AI�Ѿ������ľ���
     * @default setOrder(turn, order); //ִ�о���
     */
    virtual void onExecuteOption(int turn, Order order) { setOrder(turn, order); }

    /*
     * @interface
     * �ھ���ִ�к�,���غϽ�Ҫ����,�ûغϸı�ǰ���øú���
     * @param   turn
     *          ���ߵ�ǰ��Ϸ�غϵ�����id
     * @param   order
     *          ��ǰ��Ϸ�غ��˻���AI�Ѿ������ľ���
     * @default �޳���
     */
    virtual void onGameTurnEnd(int turn, Order order) {}

    /*
     * @interface
     * �ھ���ִ�к�,���غϽ�Ҫ����,�ûغϸı�ǰ���øú���
     * @param   pawn
     *          ��ʤ���ӵ�id
     * @default �޳���
     */
    virtual void onGameWin(int pawn) {}

protected:

    GameAI * mGameAI[PAWN_NUM] = { nullptr };
    int mTurn = 0;
    bool isGameStart = false;
};

