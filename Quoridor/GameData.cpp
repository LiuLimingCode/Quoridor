#include "stdafx.h" // MFC的预编译头，如果不是MFC项目请删除该代码。 this is the head file of MFC projects. Please delete this code if you
#include "GameData.h"
#include "GameGlobal.h"
#include <queue>

std::vector<Point> GameData::getMoveVaild(int player) const
{
	std::vector<Point> moves;
	int x = mPlayerPosition[player].x;
	int y = mPlayerPosition[player].y;

	//0, 1
	if ((!isWall(x, y) || mWall[0][x][y] == 0)//判断上面有没有墙 
		&& (!isWall(x - 1, y) || mWall[0][x - 1][y] == 0))
	{
		if (isPoint(x, y + 1) && !mBoard[x][y + 1])
			moves.push_back(Point(x, y + 1));
		else
		{
			//0, 2
			if (isPoint(x, y + 2) && !mBoard[x][y + 2]
				&& (!isWall(x, y + 1) || mWall[0][x][y + 1] == 0)
				&& (!isWall(x - 1, y + 1) || mWall[0][x - 1][y + 1] == 0))
				moves.push_back(Point(x, y + 2));
		}
	}
	//-1, 0
	if ((!isWall(x - 1, y) || mWall[1][x - 1][y] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[1][x - 1][y - 1] == 0))
	{
		if (isPoint(x - 1, y) && !mBoard[x - 1][y])
			moves.push_back(Point(x - 1, y));
		else
		{
			//-2, 0
			if (isPoint(x - 2, y) && !mBoard[x - 2][y]
				&& (!isWall(x - 2, y) || mWall[1][x - 2][y] == 0)
				&& (!isWall(x - 2, y - 1) || mWall[1][x - 2][y - 1] == 0))
				moves.push_back(Point(x - 2, y));
		}
	}
	//1, 0
	if ((!isWall(x, y) || mWall[1][x][y] == 0)
		&& (!isWall(x, y - 1) || mWall[1][x][y - 1] == 0))
	{
		if (isPoint(x + 1, y) && !mBoard[x + 1][y])
			moves.push_back(Point(x + 1, y));
		else
		{
			//2, 0
			if (isPoint(x + 2, y) && !mBoard[x + 2][y]
				&& (!isWall(x + 1, y) || mWall[1][x + 1][y] == 0)
				&& (!isWall(x + 1, y - 1) || mWall[1][x + 1][y - 1] == 0))
				moves.push_back(Point(x + 2, y));
		}
	}
	//0, -1
	if ((!isWall(x, y - 1) || mWall[0][x][y - 1] == 0)
		&& (!isWall(x - 1, y - 1) || mWall[0][x - 1][y - 1] == 0))
	{
		if (isPoint(x, y - 1) && !mBoard[x][y - 1])
			moves.push_back(Point(x, y - 1));
		else
		{
			//0, -2
			if (isPoint(x, y - 2) && !mBoard[x][y - 2]
				&& (!isWall(x, y - 2) || mWall[0][x][y - 2] == 0)
				&& (!isWall(x - 1, y - 2) || mWall[0][x - 1][y - 2] == 0))
				moves.push_back(Point(x, y - 2));
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
			moves.push_back(Point(x + 1, y + 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !mBoard[x - 1][y + 1]
			&& (!isWall(x - 1, y + 1) || mWall[1][x - 1][y + 1] == 0)
			&& (!isWall(x - 1, y) || mWall[1][x - 1][y] == 0))
			moves.push_back(Point(x - 1, y + 1));
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
			moves.push_back(Point(x + 1, y - 1));
		//1, 1
		if (isPoint(x + 1, y + 1) && !mBoard[x + 1][y + 1]
			&& (!isWall(x + 1, y) || mWall[1][x + 1][y] == 0)
			&& (!isWall(x, y) || mWall[1][x][y] == 0))
			moves.push_back(Point(x + 1, y + 1));

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
			moves.push_back(Point(x - 1, y - 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !mBoard[x - 1][y + 1]
			&& (!isWall(x - 1, y) || mWall[0][x - 1][y] == 0)
			&& (!isWall(x - 2, y) || mWall[0][x - 2][y] == 0))
			moves.push_back(Point(x - 1, y + 1));
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
			moves.push_back(Point(x + 1, y - 1));
		//-1, -1
		if (isPoint(x - 1, y - 1) && !mBoard[x - 1][y - 1]
			&& (!isWall(x - 1, y - 1) || mWall[1][x - 1][y - 1] == 0)
			&& (!isWall(x - 1, y - 2) || mWall[1][x - 1][y - 2] == 0))
			moves.push_back(Point(x - 1, y - 1));
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
		mOrderBuffer[player].push_back(Order(OrderType::MOVE, mPlayerPosition[player]));
	}

	for (int player = 0; player < PLAYER_NUM; ++player) {
		mPlayerShortLength[player] = getShortPath(player);
	}
}

std::vector<std::pair<Point, int>> GameData::getWallValid(int player) const
{
	std::vector<std::pair<Point, int>> result;

	if (mWallNum[player] <= 0)
		return result;

	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < NUM_SQUARE - 1; i++)
		{
			for (int j = 0; j < NUM_SQUARE - 1; j++)
			{
				if (checkWall(player, type, i, j))
					result.push_back(std::make_pair(Point(i, j), type));
			}
		}
	}
	return result;
}

void GameData::gotoOrder(int player, Order order)
{
	const int type = order.type;
	const int x = order.point.x;
	const int y = order.point.y;
	switch (type) // 执行指令
	{
	case OrderType::MOVE:
		gotoMove(player, x, y);
		break;
	case OrderType::WALLH:
		gotoWall(player, type, x, y);
		break;
	case OrderType::WALLV:
		gotoWall(player, type, x, y);
		break;
	default:
		break;
	}
}

void GameData::gotoMove(int player, int x, int y)
{
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = false;
	mPlayerPosition[player] = Point(x, y);
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = true;
	for (int index = 0; index < PLAYER_NUM; ++index) {
		mPlayerShortLength[index] = getShortPath(index);
	}
	mOrderBuffer[player].push_back(Order(OrderType::MOVE, Point(x, y)));
}

void GameData::setMove(int player, int x, int y)
{
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = false;
	mPlayerPosition[player] = Point(x, y);
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = true;
}

void GameData::resetMove(int player)
{
	mBoard[(int)mPlayerPosition[player].x][(int)mPlayerPosition[player].y] = false;
}

void GameData::gotoWall(int player, int type, int x, int y) {
	mWall[type][x][y] = player + 1;
	mWallNum[player]--;
	for (int index = 0; index < PLAYER_NUM; ++index) {
		mPlayerShortLength[index] = getShortPath(index);
	}
	mOrderBuffer[player].push_back(Order(type, Point(x, y)));
}

void GameData::setWall(int player, int type, int x, int y) {
	mWall[type][x][y] = player + 1;
}

void GameData::resetWall(int type, int x, int y) {
	mWall[type][x][y] = 0;
}

int GameData::getShortPath(int player) const
{
	GameData tempData = *this;// 用一个新拷贝数据来进行数据的修改操作,保证数据的安全
	Point start = mPlayerPosition[player];
	bool flag[NUM_SQUARE][NUM_SQUARE];
    std::queue<std::pair<Point, int>> queue;
	int return_flag = -1;

    for (int i = 0; i < NUM_SQUARE; ++i)
    {
        for (int j = 0; j < NUM_SQUARE; ++j)
        {
            flag[i][j] = false;
        }
    }

	flag[(int)start.x][(int)start.y] = true;
	queue.push(std::make_pair(start, 0));

	for (int index = 0; index < PLAYER_NUM; ++index) // 先清除数据中其他玩家的位置,不允许在最短路程的搜索中出现连跳
	{
		tempData.resetMove(index);
	}

	while (!queue.empty())
	{
		auto now = queue.front();
		queue.pop();

		tempData.setMove(player, now.first.x, now.first.y);
		auto moves = tempData.getMoveVaild(player);

		if ((tempData.*isPlayerWin[player])() == true)
		{
			return_flag = now.second;
			break;
		}
		
		for (auto move : moves)
		{
			if (!flag[(int)move.x][(int)move.y])
			{
				flag[(int)move.x][(int)move.y] = true;
				queue.push(std::make_pair(move, now.second + 1));
			}
		}
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

int GameData::isEnd(void) const
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

Point GameData::getCurrentPosition(int player) const
{
	return mPlayerPosition[player];
}

std::vector<std::pair<Point, int>> GameData::getCurrentWall(int player) const
{
	std::vector<std::pair<Point, int>> result;
	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < NUM_SQUARE - 1; i++)
		{
			for (int j = 0; j < NUM_SQUARE - 1; j++)
			{
				if (mWall[type][i][j] == player + 1)
					result.push_back(std::make_pair(Point(i, j), type));
			}
		}
	}
	return result;
}

bool GameData::checkOrder(int player, Order order) const
{
	const int type = order.type;
	const int x = order.point.x;
	const int y = order.point.y;
	if (type == OrderType::MOVE && checkMove(player, x, y))
	{
		return true;
	}
	else if (type == OrderType::WALLH && checkWall(player, type, x, y))
	{
		return true;
	}
	else if (type == OrderType::WALLV && checkWall(player, type, x, y))
	{
		return true;
	}
	return false;
}

bool GameData::checkWall(int player, int type, int x, int y) const
{
	if (!isWall(x, y))
		return false;

	if (mWallNum[player] == 0)
		return false;
	GameData tempData = *this;

	//横墙
	if (type == 0)
	{
		if ((!isWall(x - 1, y) || mWall[0][x - 1][y] == 0)
			&& (!isWall(x, y) || mWall[0][x][y] == 0)
			&& (!isWall(x + 1, y) || mWall[0][x + 1][y] == 0)
			&& mWall[1][x][y] == 0)
		{
			tempData.setWall(0, type, x, y);
			bool isReachable = true;
			for (int index = 0; index < PLAYER_NUM; ++index) {
				if (tempData.getShortPath(index) == -1) {
					isReachable = false; break;
				}
			}
			tempData.resetWall(type, x, y);
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
			tempData.setWall(0, type, x, y);
			bool isReachable = true;
			for (int index = 0; index < PLAYER_NUM; ++index) {
				if (tempData.getShortPath(index) == -1) {
					isReachable = false; break;
				}
			}
			tempData.resetWall(type, x, y);
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
    for (int player = 0; player < PLAYER_NUM; ++player)
    {
        if (mOrderBuffer[player].size() <= 1)
            return;
    }

    for (int player = 0; player < PLAYER_NUM; ++player)
    {
        Order order = mOrderBuffer[player].back();
        mOrderBuffer[player].pop_back();
        if (order.type == OrderType::MOVE)
        {
            Point pOld;
            for (int index = mOrderBuffer[player].size() - 1; index >= 0; --index)
            {
                if (mOrderBuffer[player].at(index).type == OrderType::MOVE)
                {
                    pOld = mOrderBuffer[player].at(index).point;
                    break;
                }
            }
            setMove(player, pOld.x, pOld.y);
        }
        else
        {
            mWall[order.type][order.point.x][order.point.y] = 0;
            mWallNum[player]++;
        }

        for (int player = 0; player < PLAYER_NUM; ++player) {
            mPlayerShortLength[player] = getShortPath(player);
        }
    }
}
