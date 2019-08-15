#pragma once

#include "Global.h"
#include <iostream>
#include <vector>
#include "AI.h"
#include <cstdlib>
#include <ctime>

class GameData
{
public:
	GameData();
	void resetGame(void);

	void gotoMove(int player, int x, int y);
	void gotoWall(int player, int type, int x, int y);
	void setMove(int player, int x, int y);
	void setWall(int player, int type, int x, int y);
	void resetWall(int type, int x, int y);

	int getShortPath(int player, CPoint start);

	bool isWall(int x, int y) const;
	bool isPoint(int x, int y) const;
	int isEnd(void);

	bool checkOrder(int player, Order order);
	bool checkWall(int player, int type, int x, int y);
	bool checkMove(int player, int x, int y) const;

	int getCurrentShortPath(int player) const;
	int getCurrentWallNum(int player) const;
	CPoint getCurrentPosition(int player) const;
	vector<pair<CPoint, int>> getCurrentWall(int player) const;

	vector<CPoint> getMoveVaild(int player) const;
	vector<pair<CPoint, int>> getWallVaild(int player);

	void undoGame(void);

private:

	int mWallNum[PLAYER_NUM];

	//储存棋盘信息
	int mWall[2][NUM_SQUARE][NUM_SQUARE] = { 0 };
	bool mBoard[NUM_SQUARE][NUM_SQUARE] = { 0 };

	vector<Order> mOrderBuffer[PLAYER_NUM];

	int mPlayerShortLength[PLAYER_NUM];
	//棋子位置
	CPoint mPlayerPosition[PLAYER_NUM];

	bool(GameData::* isPlayerWin[MAX_PLAYER_NUM])(void) = { &GameData::isPlayer1Win, &GameData::isPlayer2Win, &GameData::isPlayer3Win, &GameData::isPlayer4Win };
	bool isPlayer1Win(void) { return CONDITION_PLAYER1_WIN(mPlayerPosition[0]) ? true : false; }
	bool isPlayer2Win(void) { return CONDITION_PLAYER2_WIN(mPlayerPosition[1]) ? true : false; }
	bool isPlayer3Win(void) { return CONDITION_PLAYER3_WIN(mPlayerPosition[2]) ? true : false; }
	bool isPlayer4Win(void) { return CONDITION_PLAYER4_WIN(mPlayerPosition[3]) ? true : false; }
	
	void (GameData::* setPlayerStart[MAX_PLAYER_NUM])(void) = { &GameData::setPlayer1Start, &GameData::setPlayer2Start, &GameData::setPlayer3Start, &GameData::setPlayer4Start };
	void setPlayer1Start(void) { CONDITION_PLAYER1_START(mPlayerPosition[0]); }
	void setPlayer2Start(void) { CONDITION_PLAYER2_START(mPlayerPosition[1]); }
	void setPlayer3Start(void) { CONDITION_PLAYER3_START(mPlayerPosition[2]); }
	void setPlayer4Start(void) { CONDITION_PLAYER4_START(mPlayerPosition[3]); }
};

