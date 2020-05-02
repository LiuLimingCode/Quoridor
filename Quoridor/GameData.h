/*
 * Quoridor游戏数据和相应的操作函数
 * @author  刘力铭
 * @version v1.3
 * @Date    2019.9.27
 */

#pragma once

#include <vector>
#include "GameGlobal.h"

/*class WallArray {
public:
    Array2D<int> wallArray[2];

    Array2D<int>& vertical = wallArray[0];
    Array2D<int>& horizontal = wallArray[1];

    WallArray(int numOfRow = NUM_SQUARE, int numOfCol = NUM_SQUARE, int initValue = 0) {
        for (int temp = 0; temp < 2; ++temp) {
            wallArray[temp] = Array2D<int>(numOfRow, numOfCol, initValue);
        }
    }

    WallArray(const WallArray& copyArray) {
        *this = copyArray;
    }

    void operator=(const WallArray& copyArray) {
        for (int temp = 0; temp < 2; ++temp) {
            for (int temp = 0; temp < 2; ++temp) {
                wallArray[temp] = copyArray.wallArray[temp];
            }
        }
    }

    const Array2D<int>& operator[](int index) const {
        return wallArray[index];
    }

    Array2D<int>& operator[](int index) {
        return wallArray[index];
    }
};*/

class GameData
{
public:

    GameData() = default;
    GameData(int boardSize);
    //GameData(const GameData& copyData);

    /*
     * 重新开始游戏
     */
    void resetGame(int boardSize);

    /*
     * 悔棋
     */
    void undoGame(void);

    /*
     * 棋子执行某指令
     * @param   pawn
     *          棋子ID
     * @param   order
     *          需要执行的指令
     * @note    注意：gotoOrder函数相当于程序基于Order的类型,自动调用对于的
     *          gotoMove和gotoWall函数.其他注意请看gotoOrder和gotoWall函数.
     */
    void setOrder(int pawn, Order order);

    /*
     * 棋子走棋到某坐标
     * @param   pawn
     *          棋子ID
     * @param   row
     *          棋子走棋的横坐标
     * @param   col
     *          棋子走棋的纵坐标
     * @note    注意：相较于setMove和resetMove,gotoMove是正式的走棋函数,在执行
     *          该函数前,应该用checkMove检测走棋是否合乎规则.在该函数执行后,
     *          会自动执行getShortPath函数得到当前的最短距离,并且将该指令记录.
     */
    void setMove(int pawn, int row, int col, bool isOfficial);

    /*
     * 棋子放墙到某坐标
     * @param   pawn
     *          棋子ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   row
     *          棋子墙的横坐标
     * @param   col
     *          棋子墙的纵坐标
     * @note    注意：相较于setWall和resetMove,gotoWall是正式的放墙函数,在执行
     *          该函数前,应该用checkWall检测放墙是否合乎规则.在该函数执行后,
     *          会自动执行getShortPath函数得到当前的最短距离,并且将该指令记录.
     */
    void setWall(int pawn, int type, int row, int col, bool isOfficial);

    /*
     * 得到某棋子到终点的最短路径
     * @param   pawn
     *          棋子ID
     * @return  最短的距离
     * @note    私有变量mPlayerShortLength[]存放着当前保存的各个棋子的最短路径,在每次
     *          调用gotoMove和gotoWall后,程序会自动调用该函数更新mPlayerShortLength数据,
     *          故以直接调用getCurrentShortPath()函数得到最短距离.
     */
    int getShortPath(int pawn) const;

    /*
     * 判断是否有棋子到终点
     * @return  到终点棋子的ID,如果没有棋子到终点,返回-1,见PLAYERID枚举体
     */
    int isEnd(void) const;

    /*
     * 判断指令是否合乎规则
     * @param   pawn
     *          棋子ID
     * @param   order
     *          指令
     * @return  true为合乎规则,false为违反规则
     * @note    该函数是checkWall()函数和checkMove()函数的整合
     */
    bool checkOrder(int pawn, Order order) const;

    /*
     * 判断棋子在某坐标上放墙是否合乎规则
     * @param   pawn
     *          棋子ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   row
     *          墙的横坐标
     * @param   col
     *          墙的纵坐标
     * @return  true为合乎规则,false为违反规则
     */
    bool checkWall(int pawn, int type, int row, int col) const;

    /*
     * 判断棋子移动到某点是否合乎规则
     * @param   pawn
     *          棋子ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   row
     *          棋子走棋的横坐标
     * @param   col
     *          棋子走棋的纵坐标
     * @return  true为合乎规则,false为违反规则
     */
    bool checkMove(int pawn, int row, int col) const;

    /*
     * 得到棋子到终点的最短距离
     * @param   pawn
     *          棋子ID
     * @return  最短距离
     * @note    该返回值是存储在私有变量mPlayerShortLength[]中的数据
     */
    int getCurrentShortPath(int pawn) const;

    /*
     * 得到棋子剩余墙的数量
     * @param   pawn
     *          棋子ID
     * @return  剩余墙的数量
     */
    int getCurrentWallNum(int pawn) const;

    /*
     * 得到棋子目前在棋盘上的坐标
     * @param   pawn
     *          棋子ID
     * @return  棋子的坐标
     */
    Point getCurrentPosition(int pawn) const;

    /*
     * 得到棋子目前在棋盘上已经放的墙
     * @param   pawn
     *          棋子ID
     * @return  该棋子在棋盘上放的墙,返回类型为<墙的坐标,墙的类型>
     */
    std::vector<std::pair<Point, int>> getCurrentWall(int pawn) const;

    /*
     * 得到棋子在目前能够走的位置
     * @param   pawn
     *          棋子ID
     * @return  棋子在目前能够走的坐标
     */
    std::vector<Point> getNextMoveVaild(int pawn, bool isConsiderOtherPawn) const;

    /*
     * 得到棋子在目前能够放墙的位置
     * @param   pawn
     *          棋子ID
     * @return  棋子在能够放墙的位置,返回类型为<墙的坐标,墙的类型>
     */
    std::vector<std::pair<Point, int>> getNextWallValid(int pawn) const;

    /*
     * 判断该坐标下的墙是否越界

     */
    bool isWall(int row, int col) const;

    /*
     * 判断该坐标下的点是否越界
     * @param   row
     *          横坐标
     */
    bool isPoint(int row, int col) const;

protected:

    /*
     * 各个棋子的胜利条件
     * @note    注意：该这些函数不允许用户调用,用户可以使用isEnd()函数判断游戏是否结束
     *          但是可以通过重载该函数修改游戏的胜利条件
     */
    virtual bool isPawn1Win(void) const { return CONDITION_PAWN1_WIN(mPawnPosition[0]) ? true : false; }
    virtual bool isPawn2Win(void) const { return CONDITION_PAWN2_WIN(mPawnPosition[1]) ? true : false; }
    virtual bool isPawn3Win(void) const { return CONDITION_PAWN3_WIN(mPawnPosition[2]) ? true : false; }
    virtual bool isPawn4Win(void) const { return CONDITION_PAWN4_WIN(mPawnPosition[3]) ? true : false; }

    /*
     * 各个棋子的起始条件
     * @note    注意：该这些函数不允许用户调用,但是可以通过重载该函数修改游戏的起始条件
     */
    virtual void setPawn1Start(void) { CONDITION_PAWN1_START(mPawnPosition[0]); }
    virtual void setPawn2Start(void) { CONDITION_PAWN2_START(mPawnPosition[1]); }
    virtual void setPawn3Start(void) { CONDITION_PAWN3_START(mPawnPosition[2]); }
    virtual void setPawn4Start(void) { CONDITION_PAWN4_START(mPawnPosition[3]); }

protected:

    //_probableNextWalls
    //validNextWalls
    //_validNextPositions
    //_validNextPositionsUpdated

    int mWallNum[PAWN_NUM];

    //储存棋盘信息
    Array2D<int> mWall[2];

    int mBoardSize;

    std::vector<Order> mOrderBuffer[PAWN_NUM];

    int mPawnShortLength[PAWN_NUM];
    //棋子位置
    Point mPawnPosition[PAWN_NUM];

    bool(GameData::* isPawnWin[MAX_PAWN_NUM])(void) const = {
        &GameData::isPawn1Win, &GameData::isPawn2Win, &GameData::isPawn3Win, &GameData::isPawn4Win };
    
    void (GameData::* setPawnStart[MAX_PAWN_NUM])(void) = {
        &GameData::setPawn1Start, &GameData::setPawn2Start, &GameData::setPawn3Start, &GameData::setPawn4Start };
};

