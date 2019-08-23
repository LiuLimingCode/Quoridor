#pragma once

#include "stdafx.h"

using namespace std;

#define SIZE_SQUARE		40
#define SIZE_WALL		8
#define STARTAXIS_X		280
#define STARTAXIS_Y		100
#define NUM_SQUARE		7       // ���̵Ĵ�С
#define WALLNUM			8       // ÿ�����ӵ�е�ǽ��

#define RGBA(r,g,b,a)	((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(a))<<24)))
#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_EMPTY		RGB(240, 240, 240)

#define CONDITION_PLAYER1_WIN(p)	( p.y == NUM_SQUARE - 1 )   // ���1��ʤ������
#define CONDITION_PLAYER1_START(p)	{ p.x = (NUM_SQUARE - 1) / 2; p.y = 0; }    //���1�Ŀ�ʼλ��
#define CONDITION_PLAYER2_WIN(p)	( p.y == 0 )
#define CONDITION_PLAYER2_START(p)	{ p.x = (NUM_SQUARE - 1) / 2; p.y = NUM_SQUARE - 1; }
#define CONDITION_PLAYER3_WIN(p)	( p.x == NUM_SQUARE - 1 )
#define CONDITION_PLAYER3_START(p)	{ p.x = 0; p.y = (NUM_SQUARE - 1) / 2; }
#define CONDITION_PLAYER4_WIN(p)	( p.x == 0 )
#define CONDITION_PLAYER4_START(p)	{ p.x = NUM_SQUARE - 1; p.y = (NUM_SQUARE - 1) / 2; }

enum OrderType { // ָ������
	WALLH, // ��ǽ
	WALLV, // ��ǽ
	MOVE,  // �ƶ�
	NONE,  // ��
};

struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) {
        x = _x; y = _y;
    }
};

struct Order {
	OrderType type;
	Point point;
	Order() { type = NONE; point = Point(0, 0); };
	Order(int t, Point p) : type((OrderType)t), point(p) {}
	Order(int t, int x, int y) : type((OrderType)t), point(Point(x, y)) {}
};

#define MAX_PLAYER_NUM  4
enum PLAYERID
{
	EMPTY = -1,
	PLAYER1 = 0,
	PLAYER2 = 1,
	PLAYER_NUM = 2,
};

#define TEXT_HELP \
"��ӭ������һ������ΪӪ��Ϸ\r\n\r\n\r\n\
ѡ�����ֺ�ʼ��Ϸ\r\n\r\n\r\n����\r\n\r\n\
--��Ϸ��ʼʱ����ɫ���ڱ߽磬��ʼ�������߽硣ÿ����Ҷ��� 8 ���ϰ���\
ÿ���غ������ѡ���ƶ��Լ���С��һ�񣬻���ѡ��ڷ�һ���ϰ��赲�Է���\
˭���ȵ������߽���Ϊʤ���ߡ�\r\n\r\n\r\n\
\r\n\r\n\r\n���ߣ�������\r\n\
ʱ�䣺2018.8.6\r\n"
