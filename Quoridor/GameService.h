#pragma once

#include "Global.h"
#include <iostream>
#include <vector>
#include "AI.h"
#include <cstdlib>
#include <ctime>


class GameService
{
public:
	GameService() = default;

	void cmpMove(class AI& _cmp_ai);

	int whoFirst(void);

	void init(class AI& _cmp_ai);

	void Cmd_Error(const char *ch) { std::cout << ch << std::endl; }

	int getShortPath(Vec2 start, int playerId);

	//判该坐标是否有墙
	bool isPoint(int x, int y) const;
	bool isWall(int x, int y);

	int isend(void);
	
	bool checkWall(int type, int x, int y);
	bool checkMove(int x, int y);
	std::vector<Vec2> getMoves(Vec2 from);
	void gotoMove(int playerId, int x, int y);
	void gotoWall(int playerId, int type, int x, int y);
	std::vector<std::pair<Vec2, int>> getWallMoves(int playerId);

	std::vector<int> _wallNumVt = std::vector<int>(PLAYER_NUM, 0);

	//棋子位置
	 std::vector<Vec2> _posVt = std::vector<Vec2>(PLAYER_NUM, Vec2(0, 0));
	 
	//储存棋盘信息
	int _wall[2][NUM_SQUARE][NUM_SQUARE] = { 0 };
	bool _board[NUM_SQUARE][NUM_SQUARE] = { 0 };

	std::vector<std::pair<char, Vec2>> CMD[PLAYER_NUM];

	std::pair<char, Vec2> Now_Cmd;
	int _cmpShortLength = NUM_SQUARE - 1;
	int _plaShortLength = NUM_SQUARE - 1;

	int cmp_random = 1;//电脑随机的步数
private:
	
};

