#pragma once

#define NUM_SQUARE		7       // 棋盘的大小
#define WALLNUM			8       // 每个玩家拥有的墙数

#define CONDITION_PLAYER1_WIN(p)	( p.y == NUM_SQUARE - 1 )   // 玩家1的胜利条件
#define CONDITION_PLAYER1_START(p)	{ p.x = (NUM_SQUARE - 1) / 2; p.y = 0; }    //玩家1的开始位置
#define CONDITION_PLAYER2_WIN(p)	( p.y == 0 )
#define CONDITION_PLAYER2_START(p)	{ p.x = (NUM_SQUARE - 1) / 2; p.y = NUM_SQUARE - 1; }
#define CONDITION_PLAYER3_WIN(p)	( p.x == NUM_SQUARE - 1 )
#define CONDITION_PLAYER3_START(p)	{ p.x = 0; p.y = (NUM_SQUARE - 1) / 2; }
#define CONDITION_PLAYER4_WIN(p)	( p.x == 0 )
#define CONDITION_PLAYER4_START(p)	{ p.x = NUM_SQUARE - 1; p.y = (NUM_SQUARE - 1) / 2; }

enum OrderType { // 指令类型
	WALLH, // 横墙
	WALLV, // 竖墙
	MOVE,  // 移动
	NONE,  // 无
};

class Point {
public:
	int x;
	int y;
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

class Order {
public:
	OrderType type;
	Point point;
	Order() { type = NONE; point = Point(0, 0); };
	Order(int t, Point p) : type((OrderType)t), point(p) {}
	Order(int t, int x, int y) : type((OrderType)t), point(Point(x, y)) {}
};

#define MAX_PLAYER_NUM  4
enum PlayerId
{
	EMPTY = -1,
	PLAYER1 = 0,
	PLAYER2 = 1,
	PLAYER_NUM = 2,
};
