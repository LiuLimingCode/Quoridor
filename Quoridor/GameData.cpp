#include "stdafx.h"
#include "GameData.h"
#include "Global.h"
#include <queue>

vector<CPoint> GameData::getMoveVaild(int player) const
{
	vector<CPoint> moves;
	int x = mPlayerPosition[player].x;
	int y = mPlayerPosition[player].y;

	//0, 1
	if ((!isWall(x, y) || mWall[0][x][y] == 0)//判断上面有没有墙 
		&& (!isWall(x - 1, y) || mWall[0][x - 1][y] == 0))
	{
		if (isPoint(x, y + 1) && !mBoard[x][y + 1])
			moves.push_back(CPoint(x, y + 1));
		else
		{
			//0, 2
			if (isPoint(x, y + 2) && !mBoard[x][y + 2]
				&& (!isWall(x, y + 1) || mWall[0][x][y + 1] == 0)
				&& (!isWall(x - 1, y + 1) || mWall[0][x - 1][y + 1] == 0))
				moves.push_back(CPoint(x, y + 2));
		}
	}
	//-1, 0
	if ((!isWall(x - 1, y) || mWall[1][x - 1][y] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[1][x - 1][y - 1] == 0))
	{
		if (isPoint(x - 1, y) && !mBoard[x - 1][y])
			moves.push_back(CPoint(x - 1, y));
		else
		{
			//-2, 0
			if (isPoint(x - 2, y) && !mBoard[x - 2][y]
				&& (!isWall(x - 2, y) || mWall[1][x - 2][y] == 0)
				&& (!isWall(x - 2, y - 1) || mWall[1][x - 2][y - 1] == 0))
				moves.push_back(CPoint(x - 2, y));
		}
	}
	//1, 0
	if ((!isWall(x, y) || mWall[1][x][y] == 0)
		&& (!isWall(x, y - 1) || mWall[1][x][y - 1] == 0))
	{
		if (isPoint(x + 1, y) && !mBoard[x + 1][y])
			moves.push_back(CPoint(x + 1, y));
		else
		{
			//2, 0
			if (isPoint(x + 2, y) && !mBoard[x + 2][y]
				&& (!isWall(x + 1, y) || mWall[1][x + 1][y] == 0)
				&& (!isWall(x + 1, y - 1) || mWall[1][x + 1][y - 1] == 0))
				moves.push_back(CPoint(x + 2, y));
		}
	}
	//0, -1
	if ((!isWall(x, y - 1) || mWall[0][x][y - 1] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[0][x - 1][y - 1] == 0))
	{
		if (isPoint(x, y - 1) && !mBoard[x][y - 1])
			moves.push_back(CPoint(x, y - 1));
		else
		{
			//0, -2
			if (isPoint(x, y - 2) && !mBoard[x][y - 2]
				&& (!isWall(x, y - 2) || mWall[0][x][y - 2] == 0)
				&& (!isWall(x - 1, y - 2) || mWall[0][x - 1][y - 2] == 0))
				moves.push_back(CPoint(x, y - 2));
		}
	}


	//0, 1
	if (isPoint(x, y + 1) && mBoard[x][y + 1]
		&& (!isWall(x, y) || mWall[0][x][y] == 0)
		&& (!isWall(x - 1, y) || mWall[0][x - 1][y] == 0)
		&& (isWall(x, y + 1) && mWall[0][x][y + 1]
			|| isWall(x - 1, y + 1) && mWall[0][x - 1][y + 1]
			|| y + 1 >= NUM_SQUARE - 1))
	{
		//1, 1
		if (isPoint(x + 1, y + 1) && !mBoard[x + 1][y + 1]
			&& (!isWall(x, y + 1) || mWall[1][x][y + 1] == 0)
			&& (!isWall(x, y) || mWall[1][x][y] == 0))
			moves.push_back(CPoint(x + 1, y + 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !mBoard[x - 1][y + 1]
			&& (!isWall(x - 1, y + 1) || mWall[1][x - 1][y + 1] == 0)
			&& (!isWall(x - 1, y) || mWall[1][x - 1][y] == 0))
			moves.push_back(CPoint(x - 1, y + 1));
	}
	if (isPoint(x + 1, y) && mBoard[x + 1][y]
		&& (!isWall(x, y) || mWall[1][x][y] == 0)
		&& (!isWall(x, y - 1) || mWall[1][x][y - 1] == 0)
		&& (isWall(x + 1, y) && mWall[1][x + 1][y]
			|| isWall(x + 1, y - 1) && mWall[1][x + 1][y - 1]
			|| x + 1 >= NUM_SQUARE - 1))
	{
		//1, -1
		if (isPoint(x, y - 1) && !mBoard[x][y - 1]
			&& (!isWall(x, y - 1) || mWall[0][x][y - 1] == 0)
			&& (!isWall(x - 1, y - 1) || mWall[0][x - 1][y - 1] == 0))
			moves.push_back(CPoint(x + 1, y - 1));
		//1, 1
		if (isPoint(x + 1, y + 1) && !mBoard[x + 1][y + 1]
			&& (!isWall(x + 1, y) || mWall[1][x + 1][y] == 0)
			&& (!isWall(x, y) || mWall[1][x][y] == 0))
			moves.push_back(CPoint(x + 1, y + 1));

	}
	if (isPoint(x - 1, y) && mBoard[x - 1][y]
		&& (!isWall(x - 1, y) || mWall[1][x - 1][y] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[1][x - 1][y - 1] == 0)
		&& (isWall(x - 2, y) && mWall[1][x - 2][y]
			|| isWall(x - 2, y - 1) && mWall[1][x - 2][y - 1]
			|| x - 2 < 0))
	{
		//-1, -1
		if (isPoint(x - 1, y - 1) && !mBoard[x - 1][y - 1]
			&& (!isWall(x - 1, y - 1) || mWall[0][x - 1][y - 1] == 0)
			&& (!isWall(x - 2, y - 1) || mWall[0][x - 2][y - 1] == 0))
			moves.push_back(CPoint(x - 1, y - 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !mBoard[x - 1][y + 1]
			&& (!isWall(x - 1, y) || mWall[0][x - 1][y] == 0)
			&& (!isWall(x - 2, y) || mWall[0][x - 2][y] == 0))
			moves.push_back(CPoint(x - 1, y + 1));
	}

	//0, -1
	if (isPoint(x, y - 1) && mBoard[x][y - 1]
		&& (!isWall(x, y - 1) || mWall[0][x][y - 1] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[0][x - 1][y - 1] == 0)
		&& (isWall(x, y - 2) && mWall[0][x][y - 2]
			|| isWall(x - 1, y - 2) && mWall[0][x - 1][y - 2]
			|| y - 2 < 0))
	{
		//1, -1
		if (isPoint(x + 1, y - 1) && !mBoard[x + 1][y - 1]
			&& (!isWall(x, y - 1) || mWall[1][x][y - 1] == 0)
			&& (!isWall(x, y - 2) || mWall[1][x][y - 2] == 0))
			moves.push_back(CPoint(x + 1, y - 1));
		//-1, -1
		if (isPoint(x - 1, y - 1) && !mBoard[x - 1][y - 1]
			&& (!isWall(x - 1, y - 1) || mWall[1][x - 1][y - 1] == 0)
			&& (!isWall(x - 1, y - 2) || mWall[1][x - 1][y - 2] == 0))
			moves.push_back(CPoint(x - 1, y - 1));
	}

	return moves;
}

GameData::GameData() {
	resetGame();
}

void GameData::resetGame(void)
{
	for (int i = 0; i < NUM_SQUARE; i++) {
		for (int j = 0; j < NUM_SQUARE; j++) {
			mBoard[i][j] = false;
			mWall[0][i][j] = 0;
			mWall[1][i][j] = 0;
		}
	}

	for (int player = 0; player < PLAYER_NUM; ++player) {
		mWallNum[player] = WALLNUM;
		(this->*setPlayerStart[player])();
		mOrderBuffer[player].clear();
		mBoard[mPlayerPosition[player].x][mPlayerPosition[player].y] = true;
		mOrderBuffer[player].push_back(Order(MOVE, mPlayerPosition[player]));
	}

	for (int player = 0; player < PLAYER_NUM; ++player) {
		mPlayerShortLength[player] = getShortPath(player, mPlayerPosition[player]);
	}
}

vector<pair<CPoint, int>> GameData::getWallVaild(int player)
{
	vector<pair<CPoint, int>> result;

	if (mWallNum[player] <= 0)
		return result;

	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < NUM_SQUARE - 1; i++)
		{
			for (int j = 0; j < NUM_SQUARE - 1; j++)
			{
				if (checkWall(player, type, i, j))
					result.push_back(make_pair(CPoint(i, j), type));
			}
		}
	}
	return result;
}

void GameData::gotoMove(int player, int x, int y)
{
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = false;
	mPlayerPosition[player] = CPoint(x, y);
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = true;
	for (int index = 0; index < PLAYER_NUM; ++index) {
		mPlayerShortLength[index] = getShortPath(index, mPlayerPosition[index]);
	}
	mOrderBuffer[player].push_back(Order(MOVE, CPoint(x, y)));
}

void GameData::setMove(int player, int x, int y)
{
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = false;
	mPlayerPosition[player] = CPoint(x, y);
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = true;
}

void GameData::gotoWall(int player, int type, int x, int y) {
	mWall[type][x][y] = player + 1;
	mWallNum[player]--;
	for (int index = 0; index < PLAYER_NUM; ++index) {
		mPlayerShortLength[index] = getShortPath(index, mPlayerPosition[index]);
	}
	mOrderBuffer[player].push_back(Order(type, CPoint(x, y)));
}

void GameData::setWall(int player, int type, int x, int y) {
	mWall[type][x][y] = player + 1;
}

void GameData::resetWall(int type, int x, int y) {
	mWall[type][x][y] = 0;
}

int GameData::getShortPath(int player, CPoint start)
{
	bool flag[NUM_SQUARE][NUM_SQUARE];
	queue<pair<CPoint, int>> queue;
	int return_flag = -1;

	memset(flag, 0, sizeof(flag));
	flag[(int)start.x][(int)start.y] = true;
	queue.push(make_pair(start, 0));

	CPoint tempPos[PLAYER_NUM];
	for (int index = 0; index < PLAYER_NUM; ++index) {
		tempPos[index] = mPlayerPosition[index];// tempPos暂时保存棋子数据
		mBoard[(int)tempPos[index].x][(int)tempPos[index].y] = false;// 清空棋子
	}

	while (!queue.empty())
	{
		auto now = queue.front();
		queue.pop();

		mPlayerPosition[player] = now.first;
		mBoard[(int)now.first.x][(int)now.first.y] = true;
		auto moves = getMoveVaild(player);
		mBoard[(int)now.first.x][(int)now.first.y] = false;

		if ((this->*isPlayerWin[player])() == true)
		{
			return_flag = now.second;
			break;
		}
		
		for (auto move : moves)
		{
			if (!flag[(int)move.x][(int)move.y])
			{
				flag[(int)move.x][(int)move.y] = true;
				queue.push(make_pair(move, now.second + 1));
			}
		}
	}

	for (int index = 0; index < PLAYER_NUM; ++index) {
		mPlayerPosition[index] = tempPos[index];
		mBoard[(int)tempPos[index].x][(int)tempPos[index].y] = true;
	}

	return return_flag;
}

bool GameData::isWall(int x, int y) const
{
	if (x >= 0 && x < NUM_SQUARE - 1
		&& y >= 0 && y < NUM_SQUARE - 1)
		return true;
	return false;
}

bool GameData::isPoint(int x, int y) const
{
	if (x >= 0 && x < NUM_SQUARE && y >= 0 && y < NUM_SQUARE)
		return true;
	return false;
}

int GameData::isEnd(void)
{
	int temp = EMPTY;
	for (int player = 0; player < PLAYER_NUM; ++player) {
		if ((this->*isPlayerWin[player])() == true) {
			temp = player; break;
		}
	}
	return temp;
}

int GameData::getCurrentShortPath(int player) const
{
	return mPlayerShortLength[player];
}

int GameData::getCurrentWallNum(int player) const
{
	return mWallNum[player];
}

CPoint GameData::getCurrentPosition(int player) const
{
	return mPlayerPosition[player];
}

vector<pair<CPoint, int>> GameData::getCurrentWall(int player) const
{
	vector<pair<CPoint, int>> result;
	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < NUM_SQUARE - 1; i++)
		{
			for (int j = 0; j < NUM_SQUARE - 1; j++)
			{
				if (mWall[type][i][j] == player + 1)
					result.push_back(make_pair(CPoint(i, j), type));
			}
		}
	}
	return result;
}

bool GameData::checkOrder(int player, Order order)
{
	const int type = order.type;
	const int x = order.point.x;
	const int y = order.point.y;
	if (type == MOVE && checkMove(player, x, y))
	{
		return true;
	}
	else if (type == WALLH && checkWall(player, type, x, y))
	{
		return true;
	}
	else if (type == WALLV && checkWall(player, type, x, y))
	{
		return true;
	}
	return false;
}

bool GameData::checkWall(int player, int type, int x, int y)
{
	if (!isWall(x, y))
		return false;

	if (mWallNum[player] == 0)
		return false;

	//横墙
	if (type == 0)
	{
		if ((!isWall(x - 1, y) || mWall[0][x - 1][y] == 0)
			&& (!isWall(x, y) || mWall[0][x][y] == 0)
			&& (!isWall(x + 1, y) || mWall[0][x + 1][y] == 0)
			&& mWall[1][x][y] == 0)
		{
			setWall(0, type, x, y);
			bool isReachable = true;
			for (int index = 0; index < PLAYER_NUM; ++index) {
				if (getShortPath(index, mPlayerPosition[index]) == -1) {
					isReachable = false; break;
				}
			}
			resetWall(type, x, y);
			if (isReachable == true)
				return true;
		}
	}
	//竖墙
	else
	{
		if ((!isWall(x, y - 1) || mWall[1][x][y - 1] == 0)
			&& (!isWall(x, y) || mWall[1][x][y] == 0)
			&& (!isWall(x, y + 1) || mWall[1][x][y + 1] == 0)
			&& mWall[0][x][y] == 0)
		{
			setWall(0, type, x, y);
			bool isReachable = true;
			for (int index = 0; index < PLAYER_NUM; ++index) {
				if (getShortPath(index, mPlayerPosition[index]) == -1) {
					isReachable = false; break;
				}
			}
			resetWall(type, x, y);
			if (isReachable == true)
				return true;
		}
	}
	return false;
}

bool GameData::checkMove(int player, int x, int y) const
{
	auto moves = getMoveVaild(player);

	for (auto pos : moves)
	{
		if (pos.x == x && pos.y == y)
			return true;
	}
	return false;
}

void GameData::undoGame(void)
{

}
