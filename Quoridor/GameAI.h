#pragma once

#include "GameData.h"
#include "GameGlobal.h"

class Order;

class GameAI
{
public:

    /*
     * GameAI类初始化函数
     * @param   depth
     *          AI的思考深度,即计算未来的多少步
     * @param   id
     *          AI在游戏中控制的玩家
     * @param   time
     *          AI计算的时间限制,若AI的思考深度大,则消耗的时间大,若已经消耗的时间大于该时间限制,AI停止计算
     * @param   gameData
     *          游戏数据
     */
    GameAI(int depth, int id, long time, const class GameData* gameData);

    /*
     * AI计算下一步的策略
     * @return  AI下一步的指令
     */
    Order getNextMove(void);
    
    /*
     * AI是否正在计算
     * @return  AI是否正在计算
     */
    bool isRunning() const{ return isAIRunning; }

protected:

    /*
     * alphaBeta算法程序,AI在getNextMove中会考虑所有己方下一步的所有可能的行动和对方会相应采取的措施
     * 并用alphaBeta对该行动进行评价,最终AI会采用所有行动中对于自己最有利的一个作为下一步.
     */
    long alphaBeta(int depth, int player, long alpha, long beta);

    /*
     * 重要!
     * alphaBeta的评价函数,该函数会直接决定AI对某一行动的评价方式,改函数会直接决定AI的强度
     * 示例;
     * 1. 得分 = 100 - 我方距终点的最短距离 + 敌方距终点的最短距离
     *    该评价函数会导致AI的策略更具进攻性
     * 2. 得分 = 100  - 我方距终点的最短距离 + 敌方距终点的最短距离 - 我方墙的数量 + 敌方墙的数量
     *    该评价函数使得AI在兼具进攻性的同时,又不会过度的消耗墙的数量
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
    // 由于AI在计算的过程中会暂时修改游戏数据,为保证程序安全性,mGameDataBackup变量存储了真正的游戏数据
    // mGameData为数据的拷贝,所有对游戏数据的改动均在mGameData上进行,所以不影响原数据.
};