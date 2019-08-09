#pragma once

using namespace std;

#define SIZE_SQUARE		40
#define SIZE_WALL		8
#define STARTAXIS_X		280
#define STARTAXIS_Y		100
#define NUM_SQUARE		7
#define WALLNUM			8
#define COLOR_ME		RGB(0, 0, 0)
#define COLOR_ENEMY		RGB(255, 0, 0)
#define COLOR_EMPTY		RGB(240, 240, 240)
#define ORDER_MOVE		2
#define ORDER_WALL0		0
#define ORDER_WALL1		1
#define ORDER_ENMOVE	(2|0x10)
#define ORDER_ENWALL0	(0|0x10)
#define ORDER_ENWALL1	(1|0x10)

class Vec2
{
public:
	Vec2() = default;
	Vec2(int init_x, int init_y) :
		x(init_x), y(init_y) {}
	int x;
	int y;
};

enum Players
{
	EMPTY = -1,
	PLAYER = 0,
	COMPUTER = 1,
	PLAYER_NUM,
};