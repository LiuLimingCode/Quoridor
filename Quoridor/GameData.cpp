#include "stdafx.h" // 如果不是MFC项目请删除该代码。 Please delete this code if it is not a MFC program
#include "GameData.h"
#include "GameGlobal.h"
#include <queue>

std::vector<Point> GameData::getNextMoveVaild(int pawn, bool isConsiderOtherPawn) const
{
	std::vector<Point> moves;
	int row = mPawnPosition[pawn].row;
	int col = mPawnPosition[pawn].col;
	Array2D<bool> board(mBoardSize, mBoardSize, false);

    if (isConsiderOtherPawn) {
        for (int pawn = 0; pawn < PAWN_NUM; ++pawn) {
            board[(int)mPawnPosition[pawn].row][(int)mPawnPosition[pawn].col] = true;
        }
    }

	//0, 1
	if ((!isWall(row, col) || mWall[0][row][col] == 0)//判断上面有没有墙 
		&& (!isWall(row - 1, col) || mWall[0][row - 1][col] == 0))
	{
		if (isPoint(row, col + 1) && !board[row][col + 1])
			moves.push_back(Point(row, col + 1));
		else
		{
			//0, 2
			if (isPoint(row, col + 2) && !board[row][col + 2]
				&& (!isWall(row, col + 1) || mWall[0][row][col + 1] == 0)
				&& (!isWall(row - 1, col + 1) || mWall[0][row - 1][col + 1] == 0))
				moves.push_back(Point(row, col + 2));
		}
	}
	//-1, 0
	if ((!isWall(row - 1, col) || mWall[1][row - 1][col] == 0)
		&& (!isWall(row - 1, col - 1) || mWall[1][row - 1][col - 1] == 0))
	{
		if (isPoint(row - 1, col) && !board[row - 1][col])
			moves.push_back(Point(row - 1, col));
		else
		{
			//-2, 0
			if (isPoint(row - 2, col) && !board[row - 2][col]
				&& (!isWall(row - 2, col) || mWall[1][row - 2][col] == 0)
				&& (!isWall(row - 2, col - 1) || mWall[1][row - 2][col - 1] == 0))
				moves.push_back(Point(row - 2, col));
		}
	}
	//1, 0
	if ((!isWall(row, col) || mWall[1][row][col] == 0)
		&& (!isWall(row, col - 1) || mWall[1][row][col - 1] == 0))
	{
		if (isPoint(row + 1, col) && !board[row + 1][col])
			moves.push_back(Point(row + 1, col));
		else
		{
			//2, 0
			if (isPoint(row + 2, col) && !board[row + 2][col]
				&& (!isWall(row + 1, col) || mWall[1][row + 1][col] == 0)
				&& (!isWall(row + 1, col - 1) || mWall[1][row + 1][col - 1] == 0))
				moves.push_back(Point(row + 2, col));
		}
	}
	//0, -1
	if ((!isWall(row, col - 1) || mWall[0][row][col - 1] == 0)
		&& (!isWall(row - 1, col - 1) || mWall[0][row - 1][col - 1] == 0))
	{
		if (isPoint(row, col - 1) && !board[row][col - 1])
			moves.push_back(Point(row, col - 1));
		else
		{
			//0, -2
			if (isPoint(row, col - 2) && !board[row][col - 2]
				&& (!isWall(row, col - 2) || mWall[0][row][col - 2] == 0)
				&& (!isWall(row - 1, col - 2) || mWall[0][row - 1][col - 2] == 0))
				moves.push_back(Point(row, col - 2));
		}
	}


	//0, 1
	if (isPoint(row, col + 1) && board[row][col + 1]
		&& (!isWall(row, col) || mWall[0][row][col] == 0)
		&& (!isWall(row - 1, col) || mWall[0][row - 1][col] == 0)
		&& (isWall(row, col + 1) && mWall[0][row][col + 1]
			|| isWall(row - 1, col + 1) && mWall[0][row - 1][col + 1]
			|| col + 1 >= mBoardSize - 1))
	{
		//1, 1
		if (isPoint(row + 1, col + 1) && !board[row + 1][col + 1]
			&& (!isWall(row, col + 1) || mWall[1][row][col + 1] == 0)
			&& (!isWall(row, col) || mWall[1][row][col] == 0))
			moves.push_back(Point(row + 1, col + 1));
		//-1, 1
		if (isPoint(row - 1, col + 1) && !board[row - 1][col + 1]
			&& (!isWall(row - 1, col + 1) || mWall[1][row - 1][col + 1] == 0)
			&& (!isWall(row - 1, col) || mWall[1][row - 1][col] == 0))
			moves.push_back(Point(row - 1, col + 1));
	}
	if (isPoint(row + 1, col) && board[row + 1][col]
		&& (!isWall(row, col) || mWall[1][row][col] == 0)
		&& (!isWall(row, col - 1) || mWall[1][row][col - 1] == 0)
		&& (isWall(row + 1, col) && mWall[1][row + 1][col]
			|| isWall(row + 1, col - 1) && mWall[1][row + 1][col - 1]
			|| row + 1 >= mBoardSize - 1))
	{
		//1, -1
		if (isPoint(row, col - 1) && !board[row][col - 1]
			&& (!isWall(row, col - 1) || mWall[0][row][col - 1] == 0)
			&& (!isWall(row - 1, col - 1) || mWall[0][row - 1][col - 1] == 0))
			moves.push_back(Point(row + 1, col - 1));
		//1, 1
		if (isPoint(row + 1, col + 1) && !board[row + 1][col + 1]
			&& (!isWall(row + 1, col) || mWall[1][row + 1][col] == 0)
			&& (!isWall(row, col) || mWall[1][row][col] == 0))
			moves.push_back(Point(row + 1, col + 1));

	}
	if (isPoint(row - 1, col) && board[row - 1][col]
		&& (!isWall(row - 1, col) || mWall[1][row - 1][col] == 0)
		&& (!isWall(row - 1, col - 1) || mWall[1][row - 1][col - 1] == 0)
		&& (isWall(row - 2, col) && mWall[1][row - 2][col]
			|| isWall(row - 2, col - 1) && mWall[1][row - 2][col - 1]
			|| row - 2 < 0))
	{
		//-1, -1
		if (isPoint(row - 1, col - 1) && !board[row - 1][col - 1]
			&& (!isWall(row - 1, col - 1) || mWall[0][row - 1][col - 1] == 0)
			&& (!isWall(row - 2, col - 1) || mWall[0][row - 2][col - 1] == 0))
			moves.push_back(Point(row - 1, col - 1));
		//-1, 1
		if (isPoint(row - 1, col + 1) && !board[row - 1][col + 1]
			&& (!isWall(row - 1, col) || mWall[0][row - 1][col] == 0)
			&& (!isWall(row - 2, col) || mWall[0][row - 2][col] == 0))
			moves.push_back(Point(row - 1, col + 1));
	}

	//0, -1
	if (isPoint(row, col - 1) && board[row][col - 1]
		&& (!isWall(row, col - 1) || mWall[0][row][col - 1] == 0)
		&& (!isWall(row - 1, col - 1) || mWall[0][row - 1][col - 1] == 0)
		&& (isWall(row, col - 2) && mWall[0][row][col - 2]
			|| isWall(row - 1, col - 2) && mWall[0][row - 1][col - 2]
			|| col - 2 < 0))
	{
		//1, -1
		if (isPoint(row + 1, col - 1) && !board[row + 1][col - 1]
			&& (!isWall(row, col - 1) || mWall[1][row][col - 1] == 0)
			&& (!isWall(row, col - 2) || mWall[1][row][col - 2] == 0))
			moves.push_back(Point(row + 1, col - 1));
		//-1, -1
		if (isPoint(row - 1, col - 1) && !board[row - 1][col - 1]
			&& (!isWall(row - 1, col - 1) || mWall[1][row - 1][col - 1] == 0)
			&& (!isWall(row - 1, col - 2) || mWall[1][row - 1][col - 2] == 0))
			moves.push_back(Point(row - 1, col - 1));
	}

	return moves;
}

GameData::GameData(int boardSize) {
	resetGame(boardSize);
}

void GameData::resetGame(int boardSize)
{
	mBoardSize = boardSize;
	for (int temp = 0; temp < 2; ++temp) {
		mWall[temp] = Array2D<int>(mBoardSize, mBoardSize, 0);
	}

	for (int pawn = 0; pawn < PAWN_NUM; ++pawn) {
		mWallNum[pawn] = WALLNUM;
		(this->*setPawnStart[pawn])();
		mOrderBuffer[pawn].clear();
		mOrderBuffer[pawn].push_back(Order(OrderType::MOVE, mPawnPosition[pawn]));
	}

	for (int pawn = 0; pawn < PAWN_NUM; ++pawn) {
		mPawnShortLength[pawn] = getShortPath(pawn);
	}
}

std::vector<std::pair<Point, int>> GameData::getNextWallValid(int pawn) const
{
	std::vector<std::pair<Point, int>> result;

	if (mWallNum[pawn] <= 0)
		return result;

	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < mWall[type].row - 1; i++)
		{
			for (int j = 0; j < mWall[type].col - 1; j++)
			{
				if (checkWall(pawn, type, i, j))
					result.push_back(std::make_pair(Point(i, j), type));
			}
		}
	}
	return result;
}

void GameData::setOrder(int pawn, Order order)
{
	const int type = order.type;
	const int row = order.point.row;
	const int col = order.point.col;
	switch (type) // 执行指令
	{
	case OrderType::MOVE:
		setMove(pawn, row, col);
		break;
	case OrderType::WALLH:
		if (mWallNum[pawn] > 0) {
			mWallNum[pawn] --;
			setWall(pawn, type, row, col);
		}
		break;
	case OrderType::WALLV:
		if (mWallNum[pawn] > 0) {
			mWallNum[pawn] --;
			setWall(pawn, type, row, col);
		}
		break;
	default:
		break;
	}

	mOrderBuffer[pawn].push_back(Order(OrderType::MOVE, Point(row, col)));
	for (int index = 0; index < PAWN_NUM; ++index) {
		mPawnShortLength[index] = getShortPath(index);
	}
}

void GameData::setMove(int pawn, int row, int col)
{
	mPawnPosition[pawn] = Point(row, col);
}

void GameData::setWall(int pawn, int type, int row, int col) {
    mWall[type][row][col] = pawn + 1;
}

void GameData::resetWall(int type, int row, int col) {
	mWall[type][row][col] = 0;
}

int GameData::getShortPath(int pawn) const
{
	GameData tempData = *this;// 用一个新拷贝数据来进行数据的修改操作,保证数据的安全
	Point start = mPawnPosition[pawn];
	Array2D<bool> board(mBoardSize, mBoardSize, false);
    std::queue<std::pair<Point, int>> queue;
	int return_flag = -1;

	board[(int)start.row][(int)start.col] = true;
	queue.push(std::make_pair(start, 0));

	while (!queue.empty())
	{
		auto now = queue.front();
		queue.pop();

		tempData.setMove(pawn, now.first.row, now.first.col);
		auto moves = tempData.getNextMoveVaild(pawn, false);

		if ((tempData.*isPawnWin[pawn])() == true)
		{
			return_flag = now.second;
			break;
		}
		
		for (auto move : moves)
		{
			if (!board[(int)move.row][(int)move.col])
			{
				board[(int)move.row][(int)move.col] = true;
				queue.push(std::make_pair(move, now.second + 1));
			}
		}
	}
	return return_flag;
}

bool GameData::isWall(int row, int col) const
{
	if (row >= 0 && row < mBoardSize - 1
		&& col >= 0 && col < mBoardSize - 1)
		return true;
	return false;
}

bool GameData::isPoint(int row, int col) const
{
	if (row >= 0 && row < mBoardSize && col >= 0 && col < mBoardSize)
		return true;
	return false;
}

int GameData::isGameEnd(void) const
{
	int temp = EMPTY;
	for (int pawn = 0; pawn < PAWN_NUM; ++pawn) {
		if ((this->*isPawnWin[pawn])() == true) {
			temp = pawn; break;
		}
	}
	return temp;
}

int GameData::getCurrentShortPath(int pawn) const
{
	return mPawnShortLength[pawn];
}

int GameData::getCurrentWallNum(int pawn) const
{
	return mWallNum[pawn];
}

Point GameData::getCurrentPosition(int pawn) const
{
	return mPawnPosition[pawn];
}

std::vector<std::pair<Point, int>> GameData::getCurrentWall(int pawn) const
{
	std::vector<std::pair<Point, int>> result;
	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i < mWall[type].row - 1; i++)
		{
			for (int j = 0; j < mWall[type].col - 1; j++)
			{
				if (mWall[type][i][j] == pawn + 1)
					result.push_back(std::make_pair(Point(i, j), type));
			}
		}
	}
	return result;
}

bool GameData::checkOrder(int pawn, Order order) const
{
	const int type = order.type;
	const int row = order.point.row;
	const int col = order.point.col;
	if (type == OrderType::MOVE && checkMove(pawn, row, col))
	{
		return true;
	}
	else if (type == OrderType::WALLH && checkWall(pawn, type, row, col))
	{
		return true;
	}
	else if (type == OrderType::WALLV && checkWall(pawn, type, row, col))
	{
		return true;
	}
	return false;
}

bool GameData::checkWall(int pawn, int type, int row, int col) const
{
	if (!isWall(row, col))
		return false;

	if (mWallNum[pawn] == 0)
		return false;
	GameData tempData = *this;

	//横墙
	if (type == 0)
	{
		if ((!isWall(row - 1, col) || mWall[0][row - 1][col] == 0)
			&& (!isWall(row, col) || mWall[0][row][col] == 0)
			&& (!isWall(row + 1, col) || mWall[0][row + 1][col] == 0)
			&& mWall[1][row][col] == 0)
		{
			tempData.setWall(0, type, row, col);
			bool isReachable = true;
			for (int index = 0; index < PAWN_NUM; ++index) {
				if (tempData.getShortPath(index) == -1) {
					isReachable = false; break;
				}
			}
			if (isReachable == true)
				return true;
		}
	}
	//竖墙
	else
	{
		if ((!isWall(row, col - 1) || mWall[1][row][col - 1] == 0)
			&& (!isWall(row, col) || mWall[1][row][col] == 0)
			&& (!isWall(row, col + 1) || mWall[1][row][col + 1] == 0)
			&& mWall[0][row][col] == 0)
		{
			tempData.setWall(0, type, row, col);
			bool isReachable = true;
			for (int index = 0; index < PAWN_NUM; ++index) {
				if (tempData.getShortPath(index) == -1) {
					isReachable = false; break;
				}
			}
			if (isReachable == true)
				return true;
		}
	}
	return false;
}

bool GameData::checkMove(int pawn, int row, int col) const
{
	auto moves = getNextMoveVaild(pawn, true);

	for (auto pos : moves)
	{
		if (pos.row == row && pos.col == col)
			return true;
	}
	return false;
}

void GameData::undoGame(void)
{
    for (int pawn = 0; pawn < PAWN_NUM; ++pawn)
    {
        if (mOrderBuffer[pawn].size() <= 1)
            return;
    }

    for (int pawn = 0; pawn < PAWN_NUM; ++pawn)
    {
        Order order = mOrderBuffer[pawn].back();
        mOrderBuffer[pawn].pop_back();
        if (order.type == OrderType::MOVE)
        {
            Point pOld;
            for (int index = mOrderBuffer[pawn].size() - 1; index >= 0; --index)
            {
                if (mOrderBuffer[pawn].at(index).type == OrderType::MOVE)
                {
                    pOld = mOrderBuffer[pawn].at(index).point;
                    break;
                }
            }
            setMove(pawn, pOld.row, pOld.col);
        }
        else
        {
            mWall[order.type][order.point.row][order.point.col] = 0;
            mWallNum[pawn]++;
        }

        for (int pawn = 0; pawn < PAWN_NUM; ++pawn) {
            mPawnShortLength[pawn] = getShortPath(pawn);
        }
    }
}
