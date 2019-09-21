#pragma once

#include <vector>
#include "GameGlobal.h"

class GameData
{
public:

	GameData();

	/*
	 * 重新开始游戏
	 */
	void resetGame(void);

	/*
	 * 悔棋
	 */
	void undoGame(void);

	/*
	 * 玩家走棋到某坐标
	 * @param   player
	 *          玩家ID
	 * @param   x
	 *          玩家走棋的横坐标
	 * @param   y
	 *          玩家走棋的纵坐标
	 * @note    注意：相较于setMove和resetMove,gotoMove是正式的走棋函数,在执行
	 *          该函数前,应该用checkMove检测走棋是否合乎规则.在该函数执行后,
	 *          会自动执行getShortPath函数得到当前的最短距离,并且将该指令记录.
	 */
	void gotoMove(int player, int x, int y);

	/*
	 * 玩家放墙到某坐标
	 * @param   player
	 *          玩家ID
	 * @param   type
	 *          墙的类型,0代表横墙,1代表竖墙,见Order_type
	 * @param   x
	 *          玩家墙的横坐标
	 * @param   y
	 *          玩家墙的纵坐标
	 * @note    注意：相较于setWall和resetMove,gotoWall是正式的放墙函数,在执行
	 *          该函数前,应该用checkWall检测放墙是否合乎规则.在该函数执行后,
	 *          会自动执行getShortPath函数得到当前的最短距离,并且将该指令记录.
	 */
	void gotoWall(int player, int type, int x, int y);

	/*
	 * 玩家走棋到某坐标
	 * @param   player
	 *          玩家ID
	 * @param   x
	 *          玩家走棋的横坐标
	 * @param   y
	 *          玩家走棋的纵坐标
	 * @note    注意：相较于gotoMove,setMove是非正式的走棋函数,该函数只在AI类和
	 *          GameData类内部计算使用,不建议玩家使用.
	 */
	void setMove(int player, int x, int y);

    /*
     * 清除玩家在棋盘上的坐标
     * @param   player
     *          玩家ID
     * @note    注意：相较于gotoMove,resetMove是非正式的走棋函数,该函数只在AI类和
     *          GameData类内部计算使用,不建议玩家使用.
     */
	void resetMove(int player);

    /*
     * 玩家放墙到某坐标
     * @param   player
     *          玩家ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   x
     *          玩家墙的横坐标
     * @param   y
     *          玩家墙的纵坐标
     * @note    注意：相较于gotoWall,setWall是非正式的放墙函数,该函数只在AI类和
     *          GameData类内部计算使用,不建议玩家使用.
     */
	void setWall(int player, int type, int x, int y);

    /*
     * 清除玩家在棋盘上的墙
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   x
     *          玩家墙的横坐标
     * @param   y
     *          玩家墙的纵坐标
     * @note    注意：相较于gotoWall,resetWall是非正式的放墙函数,该函数只在AI类和
     *          GameData类内部计算使用,不建议玩家使用.
     */
	void resetWall(int type, int x, int y);

    /*
     * 得到某玩家到终点的最短路径
     * @param   player
     *          玩家ID
     * @return  最短的距离
     * @note    私有变量mPlayerShortLength[]存放着当前保存的各个玩家的最短路径,在每次
     *          调用gotoMove和gotoWall后,程序会自动调用该函数更新mPlayerShortLength数据,
     *          故玩家可以直接调用getCurrentShortPath()函数得到最短距离.
     */
	int getShortPath(int player) const;

    /*
     * 判断是否有玩家到终点
     * @return  到终点玩家的ID,如果没有玩家到终点,返回-1,见PLAYERID枚举体
     */
	int isEnd(void) const;

    /*
     * 判断指令是否合乎规则
     * @param   player
     *          玩家ID
     * @param   order
     *          指令
     * @return  true为合乎规则,false为违反规则
     * @note    该函数是checkWall()函数和checkMove()函数的整合
     */
	bool checkOrder(int player, Order order) const;

    /*
     * 判断玩家在某坐标上放墙是否合乎规则
     * @param   player
     *          玩家ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   x
     *          玩家墙的横坐标
     * @param   y
     *          玩家墙的纵坐标
     * @return  true为合乎规则,false为违反规则
     */
	bool checkWall(int player, int type, int x, int y) const;

    /*
     * 判断玩家移动到某点是否合乎规则
     * @param   player
     *          玩家ID
     * @param   type
     *          墙的类型,0代表横墙,1代表竖墙,见Order_type
     * @param   x
     *          玩家走棋的横坐标
     * @param   y
     *          玩家走棋的纵坐标
     * @return  true为合乎规则,false为违反规则
     */
	bool checkMove(int player, int x, int y) const;

    /*
     * 得到玩家到终点的最短距离
     * @param   player
     *          玩家ID
     * @return  最短距离
     * @note    该返回值是存储在私有变量mPlayerShortLength[]中的数据
     */
	int getCurrentShortPath(int player) const;

    /*
     * 得到玩家剩余墙的数量
     * @param   player
     *          玩家ID
     * @return  剩余墙的数量
     */
	int getCurrentWallNum(int player) const;

    /*
     * 得到玩家目前在棋盘上的坐标
     * @param   player
     *          玩家ID
     * @return  玩家的坐标
     */
	Point getCurrentPosition(int player) const;

    /*
     * 得到玩家目前在棋盘上已经放的墙
     * @param   player
     *          玩家ID
     * @return  该玩家在棋盘上放的墙,返回类型为<墙的坐标,墙的类型>
     */
	std::vector<std::pair<Point, int>> getCurrentWall(int player) const;

    /*
     * 得到玩家在目前能够走的位置
     * @param   player
     *          玩家ID
     * @return  玩家在目前能够走的坐标
     */
	std::vector<Point> getMoveVaild(int player) const;

    /*
     * 得到玩家在目前能够放墙的位置
     * @param   player
     *          玩家ID
     * @return  玩家在能够放墙的位置,返回类型为<墙的坐标,墙的类型>
     */
	std::vector<std::pair<Point, int>> getWallVaild(int player) const;

	/*
	 * 判断该坐标下的墙是否越界

	 */
	bool isWall(int x, int y) const;

	/*
	 * 判断该坐标下的点是否越界
	 * @param	x
	 *			横坐标
	 */
	bool isPoint(int x, int y) const;

protected:

	/*
	 * 各个玩家的胜利条件
	 * @note	注意：该这些函数不允许用户调用,用户可以使用isEnd()函数判断游戏是否结束
	 *          但是可以通过重载该函数修改游戏的胜利条件
	 */
	bool isPlayer1Win(void) const { return CONDITION_PLAYER1_WIN(mPlayerPosition[0]) ? true : false; }
	bool isPlayer2Win(void) const { return CONDITION_PLAYER2_WIN(mPlayerPosition[1]) ? true : false; }
	bool isPlayer3Win(void) const { return CONDITION_PLAYER3_WIN(mPlayerPosition[2]) ? true : false; }
	bool isPlayer4Win(void) const { return CONDITION_PLAYER4_WIN(mPlayerPosition[3]) ? true : false; }

	/*
	 * 各个玩家的起始条件
	 * @note	注意：该这些函数不允许用户调用,但是可以通过重载该函数修改游戏的起始条件
	 */
	void setPlayer1Start(void) { CONDITION_PLAYER1_START(mPlayerPosition[0]); }
	void setPlayer2Start(void) { CONDITION_PLAYER2_START(mPlayerPosition[1]); }
	void setPlayer3Start(void) { CONDITION_PLAYER3_START(mPlayerPosition[2]); }
	void setPlayer4Start(void) { CONDITION_PLAYER4_START(mPlayerPosition[3]); }

private:

	int mWallNum[PLAYER_NUM];

	//储存棋盘信息
	int mWall[2][NUM_SQUARE][NUM_SQUARE] = { 0 };
	bool mBoard[NUM_SQUARE][NUM_SQUARE] = { 0 };

	std::vector<Order> mOrderBuffer[PLAYER_NUM];

	int mPlayerShortLength[PLAYER_NUM];
	//棋子位置
	Point mPlayerPosition[PLAYER_NUM];

	bool(GameData::* isPlayerWin[MAX_PLAYER_NUM])(void) const = { 
		&GameData::isPlayer1Win, &GameData::isPlayer2Win, &GameData::isPlayer3Win, &GameData::isPlayer4Win };
	
	void (GameData::* setPlayerStart[MAX_PLAYER_NUM])(void) = { 
		&GameData::setPlayer1Start, &GameData::setPlayer2Start, &GameData::setPlayer3Start, &GameData::setPlayer4Start };
};

