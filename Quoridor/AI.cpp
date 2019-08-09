#include "AI.h"
#include "GameService.h"
#include <sys/timeb.h>
#include <algorithm>

AI::AI(int depth, long time, GameService * game)
{
	_depth = depth;
	_time = time;
	_game = game;
	isRuning = false;
}

std::pair<Vec2, int> AI::getNextMove(void)
{
	isRuning = true;
	long long startTime = getSystemTime();

	std::vector<MoveNode> moveVt;

	std::vector<Vec2> moves = _game->getMoves(_game->_posVt[Players::COMPUTER]);
	std::vector<std::pair<Vec2, int>> wallMoves = _game->getWallMoves(COMPUTER);

//	log("%d %d", moves.size(), wallMoves.size());

	for (auto move : moves)
	{
		//2表示落子
		moveVt.push_back(MoveNode(0, 2, move));
	}


	for (auto wallMove : wallMoves)
	{
		moveVt.push_back(MoveNode(0, wallMove.second, wallMove.first));
	}

	auto size = moveVt.size();
	MoveNode ans;

	for (int i_depth = 1; i_depth <= _depth; i_depth++)
	{
		long long timeLen = getSystemTime() - startTime;

		if (timeLen >= _time)
		{
//			log("%fs %d层", timeLen / 1000.0, i_depth);
			break;
		}
		long val;
		long alpha = -1000000;
		long beta = 1000000;
		MoveNode moveNode;

		for (size_t i = 0; i < size; i++)
		{
			int x = moveVt[i].pos.x;
			int y = moveVt[i].pos.y;

			if (moveVt[i].moveType == 2)//表示走子
			{
				auto tempPos = _game->_posVt[COMPUTER];
				_game->_board[(int)tempPos.x][(int)tempPos.y] = false;

				_game->_posVt[COMPUTER] = Vec2(x, y);
				_game->_board[x][y] = true;

				val = -alphaBeta(i_depth, PLAYER, -beta, -alpha);

				_game->_board[x][y] = false;
				_game->_posVt[COMPUTER] = tempPos;
				_game->_board[(int)_game->_posVt[COMPUTER].x][(int)_game->_posVt[COMPUTER].y] = true;
			}
			else
			{
				_game->_wall[moveVt[i].moveType][x][y] = COMPUTER + 1;
				val = -alphaBeta(i_depth, PLAYER, -beta, -alpha);

				_game->_wall[moveVt[i].moveType][x][y] = 0;
			}

			if (val > alpha)
			{
				moveNode = moveVt[i];
				alpha = val;
			}
			moveVt[i].score = alpha;
		}

		ans = moveNode;
//		log("val %d  move type=%d x=%d y=%d", val, ans.moveType, (int)ans.pos.x, (int)ans.pos.y);

		std::sort(moveVt.begin(), moveVt.end());
	}

	isRuning = false;

	return std::make_pair(ans.pos, ans.moveType);
}

long AI::alphaBeta(int depth, int playerId, long alpha, long beta)
{
	if (depth == 0)
	{
		long score = evaluate();
		if (playerId == 0)
			score = -score;

		return score;
	}

	std::vector<Vec2> moves = _game->getMoves(_game->_posVt[playerId]);

	long val;

	for (auto move : moves)
	{
		Vec2 tpos = _game->_posVt[playerId];
		_game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = false;

		_game->_posVt[playerId] = move;
		_game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = true;

		val = -alphaBeta(depth - 1, 1 - playerId, -beta, -alpha);

		_game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = false;

		_game->_posVt[playerId] = tpos;
		_game->_board[(int)_game->_posVt[playerId].x][(int)_game->_posVt[playerId].y] = true;

		if (val >= beta)
			return beta;
		if (val > alpha)
			alpha = val;
	}

	std::vector<std::pair<Vec2, int>> wallMoves = _game->getWallMoves(playerId);

	for (auto wallMove : wallMoves)
	{
		_game->_wall[wallMove.second][(int)wallMove.first.x][(int)wallMove.first.y] = playerId + 1;

		val = -alphaBeta(depth - 1, 1 - playerId, -beta, -alpha);

		_game->_wall[wallMove.second][(int)wallMove.first.x][(int)wallMove.first.y] = 0;

		if (val >= beta)
			return beta;
		if (val > alpha)
			alpha = val;
	}

	return alpha;
}

int AI::evaluate(void)
{
	int cmpShortLength = _game->getShortPath(_game->_posVt[COMPUTER], COMPUTER);
	int meShortLength = _game->getShortPath(_game->_posVt[PLAYER], PLAYER);
	int cmpWallNum = _game->_wallNumVt[COMPUTER];
	int meWallNum = _game->_wallNumVt[PLAYER];

	if (cmpShortLength == 0)
		return 200;

	if (meShortLength == 0)
		return 0;

	int score = 100 - cmpShortLength + meShortLength;

	//    int score = 100 - cmpShortLength;
	return score;
}

long long AI::getSystemTime(void)
{
	struct timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
}
