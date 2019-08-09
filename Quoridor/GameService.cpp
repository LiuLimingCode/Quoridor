#include "GameService.h"
#include <queue>
#include "AI.h"

//获取可走位置
std::vector<Vec2> GameService::getMoves(Vec2 from)
{
	std::vector<Vec2> moves;
	int x = from.x;
	int y = from.y;

	//0, 1
	if ((!isWall(x, y) || _wall[0][x][y] == 0)//判断上面有没有墙 
		&& (!isWall(x - 1, y) || _wall[0][x - 1][y] == 0))
	{
		if (isPoint(x, y + 1) && !_board[x][y + 1])
			moves.push_back(Vec2(x, y + 1));
		else
		{
			//0, 2
			if (isPoint(x, y + 2) && !_board[x][y + 2]
				&& (!isWall(x, y + 1) || _wall[0][x][y + 1] == 0)
				&& (!isWall(x - 1, y + 1) || _wall[0][x - 1][y + 1] == 0))
				moves.push_back(Vec2(x, y + 2));
		}
	}
	//-1, 0
	if ((!isWall(x - 1, y) || _wall[1][x - 1][y] == 0)
		&& (!isWall(x - 1, y - 1) || _wall[1][x - 1][y - 1] == 0))
	{
		if (isPoint(x - 1, y) && !_board[x - 1][y])
			moves.push_back(Vec2(x - 1, y));
		else
		{
			//-2, 0
			if (isPoint(x - 2, y) && !_board[x - 2][y]
				&& (!isWall(x - 2, y) || _wall[1][x - 2][y] == 0)
				&& (!isWall(x - 2, y - 1) || _wall[1][x - 2][y - 1] == 0))
				moves.push_back(Vec2(x - 2, y));
		}
	}
	//1, 0
	if ((!isWall(x, y) || _wall[1][x][y] == 0)
		&& (!isWall(x, y - 1) || _wall[1][x][y - 1] == 0))
	{
		if (isPoint(x + 1, y) && !_board[x + 1][y])
			moves.push_back(Vec2(x + 1, y));
		else
		{
			//2, 0
			if (isPoint(x + 2, y) && !_board[x + 2][y]
				&& (!isWall(x + 1, y) || _wall[1][x + 1][y] == 0)
				&& (!isWall(x + 1, y - 1) || _wall[1][x + 1][y - 1] == 0))
				moves.push_back(Vec2(x + 2, y));
		}
	}
	//0, -1
	if ((!isWall(x, y - 1) || _wall[0][x][y - 1] == 0)
		&& (!isWall(x - 1, y - 1) || _wall[0][x - 1][y - 1] == 0))
	{
		if (isPoint(x, y - 1) && !_board[x][y - 1])
			moves.push_back(Vec2(x, y - 1));
		else
		{
			//0, -2
			if (isPoint(x, y - 2) && !_board[x][y - 2]
				&& (!isWall(x, y - 2) || _wall[0][x][y - 2] == 0)
				&& (!isWall(x - 1, y - 2) || _wall[0][x - 1][y - 2] == 0))
				moves.push_back(Vec2(x, y - 2));
		}
	}


	//0, 1
	if (isPoint(x, y + 1) && _board[x][y + 1]
		&& (!isWall(x, y) || _wall[0][x][y] == 0)
		&& (!isWall(x - 1, y) || _wall[0][x - 1][y] == 0)
		&& (isWall(x, y + 1) && _wall[0][x][y + 1]
			|| isWall(x - 1, y + 1) && _wall[0][x - 1][y + 1]
			|| y + 1 >= NUM_SQUARE - 1))
	{
		//1, 1
		if (isPoint(x + 1, y + 1) && !_board[x + 1][y + 1]
			&& (!isWall(x, y + 1) || _wall[1][x][y + 1] == 0)
			&& (!isWall(x, y) || _wall[1][x][y] == 0))
			moves.push_back(Vec2(x + 1, y + 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !_board[x - 1][y + 1]
			&& (!isWall(x - 1, y + 1) || _wall[1][x - 1][y + 1] == 0)
			&& (!isWall(x - 1, y) || _wall[1][x - 1][y] == 0))
			moves.push_back(Vec2(x - 1, y + 1));
	}
	if (isPoint(x + 1, y) && _board[x + 1][y]
		&& (!isWall(x, y) || _wall[1][x][y] == 0)
		&& (!isWall(x, y - 1) || _wall[1][x][y - 1] == 0)
		&& (isWall(x + 1, y) && _wall[1][x + 1][y]
			|| isWall(x + 1, y - 1) && _wall[1][x + 1][y - 1]
			|| x + 1 >= NUM_SQUARE - 1))
	{
		//1, -1
		if (isPoint(x, y - 1) && !_board[x][y - 1]
			&& (!isWall(x, y - 1) || _wall[0][x][y - 1] == 0)
			&& (!isWall(x - 1, y - 1) || _wall[0][x - 1][y - 1] == 0))
			moves.push_back(Vec2(x + 1, y - 1));
		//1, 1
		if (isPoint(x + 1, y + 1) && !_board[x + 1][y + 1]
			&& (!isWall(x + 1, y) || _wall[1][x + 1][y] == 0)
			&& (!isWall(x, y) || _wall[1][x][y] == 0))
			moves.push_back(Vec2(x + 1, y + 1));

	}
	if (isPoint(x - 1, y) && _board[x - 1][y]
		&& (!isWall(x - 1, y) || _wall[1][x - 1][y] == 0)
		&& (!isWall(x - 1, y - 1) || _wall[1][x - 1][y - 1] == 0)
		&& (isWall(x - 2, y) && _wall[1][x - 2][y]
			|| isWall(x - 2, y - 1) && _wall[1][x - 2][y - 1]
			|| x - 2 < 0))
	{
		//-1, -1
		if (isPoint(x - 1, y - 1) && !_board[x - 1][y - 1]
			&& (!isWall(x - 1, y - 1) || _wall[0][x - 1][y - 1] == 0)
			&& (!isWall(x - 2, y - 1) || _wall[0][x - 2][y - 1] == 0))
			moves.push_back(Vec2(x - 1, y - 1));
		//-1, 1
		if (isPoint(x - 1, y + 1) && !_board[x - 1][y + 1]
			&& (!isWall(x - 1, y) || _wall[0][x - 1][y] == 0)
			&& (!isWall(x - 2, y) || _wall[0][x - 2][y] == 0))
			moves.push_back(Vec2(x - 1, y + 1));
	}

	//0, -1
	if (isPoint(x, y - 1) && _board[x][y - 1]
		&& (!isWall(x, y - 1) || _wall[0][x][y - 1] == 0)
		&& (!isWall(x - 1, y - 1) || _wall[0][x - 1][y - 1] == 0)
		&& (isWall(x, y - 2) && _wall[0][x][y - 2]
			|| isWall(x - 1, y - 2) && _wall[0][x - 1][y - 2]
			|| y - 2 < 0))
	{
		//1, -1
		if (isPoint(x + 1, y - 1) && !_board[x + 1][y - 1]
			&& (!isWall(x, y - 1) || _wall[1][x][y - 1] == 0)
			&& (!isWall(x, y - 2) || _wall[1][x][y - 2] == 0))
			moves.push_back(Vec2(x + 1, y - 1));
		//-1, -1
		if (isPoint(x - 1, y - 1) && !_board[x - 1][y - 1]
			&& (!isWall(x - 1, y - 1) || _wall[1][x - 1][y - 1] == 0)
			&& (!isWall(x - 1, y - 2) || _wall[1][x - 1][y - 2] == 0))
			moves.push_back(Vec2(x - 1, y - 1));
	}

	return moves;
}

void GameService::gotoMove(int playerId, int x, int y)
{
	_board[(int)_posVt[playerId].x][(int)_posVt[playerId].y] = false;
	_posVt[playerId] = Vec2(x, y);
	_board[(int)_posVt[playerId].x][(int)_posVt[playerId].y] = true;
}

void GameService::gotoWall(int playerId, int type, int x, int y)
{
	_wall[type][x][y] = playerId + 1;
	_wallNumVt[playerId]--;
}

//返回最短路线长度，-1表示无法走到终点
int GameService::getShortPath(Vec2 start, int playerId)
{
	bool flag[NUM_SQUARE][NUM_SQUARE];
	std::queue<std::pair<Vec2, int>> queue;
	int return_flag = -1;

	memset(flag, 0, sizeof(flag));
	flag[(int)start.x][(int)start.y] = true;
	queue.push(std::make_pair(start, 0));

	auto tempPosC = _posVt[COMPUTER];
	_board[(int)tempPosC.x][(int)tempPosC.y] = false;
	auto tempPosP = _posVt[PLAYER];
	_board[(int)tempPosP.x][(int)tempPosP.y] = false;

	while (!queue.empty())
	{
		auto now = queue.front();
		queue.pop();

		if (playerId == PLAYER && (int)now.first.y == NUM_SQUARE - 1)
		{
			return_flag = now.second;
			break;
		}
		if (playerId == COMPUTER && (int)now.first.y == 0)
		{
			return_flag = now.second;
			break;
		}

		_posVt[playerId] = now.first;
		_board[(int)now.first.x][(int)now.first.y] = true;

		auto moves = getMoves(now.first);

		_board[(int)now.first.x][(int)now.first.y] = false;

		for (auto move : moves)
		{
			if (!flag[(int)move.x][(int)move.y])
			{
				flag[(int)move.x][(int)move.y] = true;
				queue.push(std::make_pair(move, now.second + 1));
			}

		}
	}

	_posVt[COMPUTER] = tempPosC;
	_board[(int)tempPosC.x][(int)tempPosC.y] = true;
	_posVt[PLAYER] = tempPosP;
	_board[(int)tempPosP.x][(int)tempPosP.y] = true;

	return return_flag;
}

bool GameService::isPoint(int x, int y) const
{
	if (x >= 0 && x < NUM_SQUARE && y >= 0 && y < NUM_SQUARE)
			return true;
	return false;
}

bool GameService::isWall(int x, int y)
{
	if (x >= 0 && x < NUM_SQUARE - 1
		&& y >= 0 && y < NUM_SQUARE - 1)
		return true;
	return false;
}

int GameService::isend(void)
{
	if (_posVt[PLAYER].y == NUM_SQUARE - 1)
	{
		return PLAYER;
	}
	else if (_posVt[COMPUTER].y == 0)
	{
		return COMPUTER;
	}
	else
		return EMPTY;		
}

//判断放墙是否合法
bool GameService::checkWall(int type, int x, int y)
{
	if (!isWall(x, y))
		return false;

	//横墙
	if (type == 0)
	{
		if ((!isWall(x - 1, y) || _wall[0][x - 1][y] == 0)
			&& (!isWall(x, y) || _wall[0][x][y] == 0)
			&& (!isWall(x + 1, y) || _wall[0][x + 1][y] == 0)
			&& _wall[1][x][y] == 0)
		{
			_wall[type][x][y] = 1;
			int a = getShortPath(_posVt[COMPUTER], COMPUTER);
			int b = getShortPath(_posVt[PLAYER], PLAYER);
			_wall[type][x][y] = 0;
			if (a != -1 && b != -1)
				return true;
		}
	}
	//竖墙
	else
	{
		if ((!isWall(x, y - 1) || _wall[1][x][y - 1] == 0)
			&& (!isWall(x, y) || _wall[1][x][y] == 0)
			&& (!isWall(x, y + 1) || _wall[1][x][y + 1] == 0)
			&& _wall[0][x][y] == 0)
		{
			_wall[type][x][y] = 1;
			int a = getShortPath(_posVt[COMPUTER], COMPUTER);
			int b = getShortPath(_posVt[PLAYER], PLAYER);
			_wall[type][x][y] = 0;
			if (a != -1 && b != -1)
				return true;
		}
	}
	return false;
}

bool GameService::checkMove(int x, int y)
{
	auto moves = getMoves(_posVt[PLAYER]);

	for (auto pos : moves)
	{
		if (pos.x == x && pos.y == y)
			return true;
	}
	return false;
}

std::vector<std::pair<Vec2, int>> GameService::getWallMoves(int playerId)
{
	std::vector<std::pair<Vec2, int>> result;

	if (_wallNumVt[playerId] <= 0)
		return result;

	for (int type = 0; type <= 1; type++)
	{
		for (int i = 0; i<NUM_SQUARE - 1; i++)
		{
			for (int j = 0; j<NUM_SQUARE - 1; j++)
			{
				if (checkWall(type, i, j))
					result.push_back(std::make_pair(Vec2(i, j), type));
			}
		}
	}
	return result;
}

void GameService::cmpMove(class AI& _cmp_ai)
{
	std::pair<Vec2, int> move;

	if (cmp_random > 0)
	{
		srand((unsigned int)time(0));
		std::vector<Vec2> moves = getMoves(_posVt[Players::COMPUTER]);
		move.second = 2;
		move.first = moves[rand()%moves.size()];
		//gotoMove(COMPUTER, move.first.x, move.first.y);
		cmp_random--;
	}
	else
	{
		move = _cmp_ai.getNextMove();

		/*switch (move.second) {
		case 2:
			gotoMove(COMPUTER, move.first.x, move.first.y);
			break;
		case 0:
			gotoWall(COMPUTER, 0, move.first.x, move.first.y);
			break;
		case 1:
			gotoWall(COMPUTER, 1, move.first.x, move.first.y);
			break;
		}*/
	}
	CMD[COMPUTER].push_back(std::make_pair(move.second, move.first));

	_plaShortLength = getShortPath(_posVt[PLAYER], PLAYER);
	_cmpShortLength = getShortPath(_posVt[COMPUTER], COMPUTER);
}

int GameService::whoFirst(void)
{
	int temp = 0;

	srand((unsigned int)time(0));
	temp = rand() % 2;

	if (temp == 1)
		return PLAYER;
	else
		return COMPUTER;
}

void GameService::init(class AI& _cmp_ai)
{
	int i, j;

	_wallNumVt[PLAYER] = WALLNUM;
	_wallNumVt[COMPUTER] = WALLNUM;

	_posVt[PLAYER].x = (NUM_SQUARE - 1) / 2;
	_posVt[PLAYER].y = 0;
	_posVt[COMPUTER].x = (NUM_SQUARE - 1) / 2;
	_posVt[COMPUTER].y = NUM_SQUARE - 1;

	for (i = 0; i < NUM_SQUARE; i++)
		for (j = 0; j < NUM_SQUARE; j++)
		{
			_board[i][j] = false;
			_wall[0][i][j] = 0;
			_wall[1][i][j] = 0;
		}
			
	CMD[PLAYER].clear();
	CMD[COMPUTER].clear();

	_board[(NUM_SQUARE - 1) / 2][0] = true;
	_board[(NUM_SQUARE - 1) / 2][NUM_SQUARE - 1] = true;

	CMD[PLAYER].push_back(std::make_pair(2, _posVt[PLAYER]));
	CMD[COMPUTER].push_back(std::make_pair(2, _posVt[COMPUTER]));

	cmp_random = 1;

	_cmp_ai = AI(1, 5000, this);
}
