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
     * 设置AI控制的棋子id
     * @param   id
     *          AI在游戏中控制的棋子
     * @param   ai
     *          设置的AI
     * @note    此函数用于设置用户派生的GameAI类
     */
    void setGameAI(int id, GameAI* ai);

    /*
     * 设置人控制的棋子id
     * @param   id
     *          人控制的棋子id
     */
    void setGamePlayer(int id);

    /*
     * 重新开始游戏
     */
    void resetGame(void);

    /*
     * 得到当前是哪个棋子的回合
     */
    int getCurrentTurn(void) const;

    /*
     * 设置先手
     * @param   id
     *          先手棋子的id
     */
    void setWhoFirst(int id);

    /*
     * 判断当前回合是否为AI决策的回合
     * @return  true = 当前为AI决策回合;false = 当前为人决策回合
     */
    bool isCurrentAITurn(void) const;

    /*
     * 返回决策某个回合的游戏AI
     * @param   turn
     *          返回决策该回合的游戏AI
     * @noto    如果当前回合由人决策,返回nullptr
     */
    GameAI* getGameAI(int turn) const;

    /*
     * @interface
     * Quoridor游戏的基础逻辑如下：
     * 
     * onGameStart(); // 游戏开始
     * while() { // 游戏循环
     * onBeforeOption(); // 在人或AI计算决策之前
     * 如果是AI决策回合调用onAIOption(),人决策回合调用onPlayerOption();
     * onExecuteOption(); // 执行决策
     * onGameTurnEnd(); // 回合即将结束
     * 判断是否有棋子达到胜利条件,若有则调用onGameWin();
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
    virtual void onGameOver(void) {}

    /*
     * @interface 
     * 当前回合的人或者AI在做出决策前调用该虚函数
     * @param   turn
     *          决策当前游戏回合的棋子id
     * @default 无程序
     */
    virtual void onBeforeOption(int turn) {}

    /*
     * @interface 
     * 如果当前是AI决策的回合,则在AI决策时调用该函数
     * @param   turn
     *          决策当前游戏回合的棋子id
     * @return  AI计算后得出下一步的决策
     * @default return getGameAI(turn)->getNextMove(); //由AI计算下一步的操作
     */
    virtual Order onAIOption(int turn) { return getGameAI(turn)->getNextMove(turn, this); }

    /*
     * @interface
     * 如果当前是人决策的回合,则在玩家决策时调用该函数
     * @param   turn
     *          决策当前游戏回合的棋子id
     * @return  人的决策
     * @note    该函数必须重写实现对应的功能
     */
    virtual Order onPlayerOption(int turn) = 0;

    /*
     * @interface
     * 在AI或者人得出本回合的决策后执行该函数,用于将决策执行
     * @param   turn
     *          决策当前游戏回合的棋子id
     * @param   order
     *          当前游戏回合人或者AI已经做出的决策
     * @default setOrder(turn, order); //执行决策
     */
    virtual void onExecuteOption(int turn, Order order) { setOrder(turn, order); }

    /*
     * @interface
     * 在决策执行后,本回合将要结束,该回合改变前调用该函数
     * @param   turn
     *          决策当前游戏回合的棋子id
     * @param   order
     *          当前游戏回合人或者AI已经做出的决策
     * @default 无程序
     */
    virtual void onGameTurnEnd(int turn, Order order) {}

    /*
     * @interface
     * 在决策执行后,本回合将要结束,该回合改变前调用该函数
     * @param   pawn
     *          获胜棋子的id
     * @default 无程序
     */
    virtual void onGameWin(int pawn) {}

protected:

    GameAI * mGameAI[PAWN_NUM] = { nullptr };
    int mTurn = 0;
    bool isGameStart = false;
};

