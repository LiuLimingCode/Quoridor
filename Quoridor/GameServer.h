/*
 * 该抽象类提供一个简单的游戏逻辑和相应接口供用户使用,用户也可以直接根据
 * GameAI类和GameData类提供的函数自行设计.
 * @author  刘力铭
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
     * 设置游戏AI
     * @param   id
     *          该AI控制的id
     * @param   depth
     *          AI的思考深度,即计算未来的多少步,见GameAI构造函数
     * @param   time
     *          AI计算的时间限制,见GameAI构造函数
     */
    void setGameAI(int id, int depth, long time);

    /*
     * 设置游戏玩家
     * @param   id
     *          玩家控制的id
     */
    void setGamePlayer(int id);

    /*
     * 重新开始游戏
     */
    void resetGame(void);

    /*
     * 决策当前游戏回合的玩家id
     */
    int getCurrentTurn(void);

    /*
     * 设置先手
     * @param   id
     *          先手玩家的id
     */
    void setWhoFirst(int id);

    /*
     * 判断当前回合是否为AI决策的回合
     */
    bool isCurrentAITurn(void);

    /*
     * @interface
     * Quoridor游戏的基础逻辑如下：
     * 
     * onGameStart(); // 游戏开始
     * while(){ // 游戏循环
     * onBeforeOption(); // 在玩家和AI计算决策之前
     * 如果是AI回合调用onAIOption(),玩家回合调用onPlayerOption();
     * onExecuteOption(); // 执行决策
     * onGameTurnEnd(); // 回合即将结束
     * 判断是否有玩家达到胜利条件,若有则调用onGameWin();
     * 下一回合 }
     * onGameStop(); //游戏结束
     */
    virtual int GameHandle(void);

    /*
     * @interface 
     * 游戏开始,当GameHandle函数被调用时会调用该虚函数,该函数调用结束后进入游戏循环
     * @default 无程序
     */
    virtual void onGameStart(void) {}

    /*
     * @interface
     * 游戏结束,当游戏循环结束后即将退出GameHandle函数时调用该虚函数
     * @default 无程序
     */
    virtual void onGameStop(void) {}

    /*
     * @interface 
     * 当前回合的玩家或者AI在做出决策前调用该虚函数
     * @param   turn
     *          决策当前游戏回合的玩家id
     * @default 无程序
     */
    virtual void onBeforeOption(int turn) {}

    /*
     * @interface 
     * 如果当前是AI决策的回合,则在AI决策时调用该函数
     * @param   turn
     *          决策当前游戏回合的玩家id
     * @return  AI计算后得出下一步的决策
     * @default return mGameAI[turn]->getNextMove(); //由AI计算下一步的操作
     */
    virtual Order onAIOption(int turn) { return mGameAI[turn]->getNextMove(); }

    /*
     * @interface
     * 如果当前是玩家决策的回合,则在玩家决策时调用该函数
     * @param   turn
     *          决策当前游戏回合的玩家id
     * @return  玩家的决策
     * @note    该函数必须重写实现对应的功能
     */
    virtual Order onPlayerOption(int turn) = 0;

    /*
     * @interface
     * 在AI或者玩家得出本回合的决策后执行该函数,用于将决策执行
     * @param   turn
     *          决策当前游戏回合的玩家id
     * @param   order
     *          当前游戏回合的玩家的决策
     * @default gotoOrder(turn, order); //执行决策
     */
    virtual void onExecuteOption(int turn, Order order) { gotoOrder(turn, order); }

    /*
     * @interface
     * 在决策执行后,本回合将要结束,该回合改变前调用该函数
     * @param   turn
     *          决策当前游戏回合的玩家id
     * @param   order
     *          当前游戏回合的玩家的决策
     * @default 无程序
     */
    virtual void onGameTurnEnd(int turn, Order order) {}

    /*
     * @interface
     * 在决策执行后,本回合将要结束,该回合改变前调用该函数
     * @param   player
     *          获胜玩家的id
     * @default 无程序
     */
    virtual void onGameWin(int player) {}

private:

    GameAI * mGameAI[PLAYER_NUM] = { nullptr };
    int mTurn = 0;
    volatile bool isGameStart = false;
};

