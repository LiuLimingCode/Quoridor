#pragma once

#define NUM_SQUARE		7       // ���̵Ĵ�С
#define WALLNUM			8       // ÿ�����ӵ�е�ǽ��

#define CONDITION_PLAYER1_WIN(p)	( (p.y) == (NUM_SQUARE - 1) )   // ���1��ʤ������
#define CONDITION_PLAYER1_START(p)	{ (p.x) = ((NUM_SQUARE - 1) / 2); (p.y) = 0; }    //���1�Ŀ�ʼλ��
#define CONDITION_PLAYER2_WIN(p)	( (p.y) == 0 )
#define CONDITION_PLAYER2_START(p)	{ (p.x) = ((NUM_SQUARE - 1) / 2); (p.y) = (NUM_SQUARE - 1); }
#define CONDITION_PLAYER3_WIN(p)	( (p.x) == (NUM_SQUARE - 1) )
#define CONDITION_PLAYER3_START(p)	{ (p.x) = 0; (p.y) = ((NUM_SQUARE - 1) / 2); }
#define CONDITION_PLAYER4_WIN(p)	( (p.x) == 0 )
#define CONDITION_PLAYER4_START(p)	{ (p.x) = (NUM_SQUARE - 1); (p.y) = ((NUM_SQUARE - 1) / 2); }

enum OrderType { // ָ������
	WALLH, // ��ǽ
	WALLV, // ��ǽ
	MOVE,  // �ƶ�
	NONE,  // ��
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
	Order() { type = OrderType::NONE; point = Point(0, 0); };
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
