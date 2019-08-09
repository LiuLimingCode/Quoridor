#pragma once

#include "Global.h"


class CQuyu
{
public:
	CQuyu(void);
	~CQuyu(void);

	CRect getRect(void);

	bool isBoardOn(CPoint point);

	bool isBoardEmpty(void);

	bool isBoardPlayer(void);

	bool isBoardComputer(void);

	bool isWallOn(int type, CPoint point);

	bool isWallEmpty(int type);

	bool isWallPlayer(void);

	bool isWallComputer(void);

	int x = 0;
	int y = 0;
	int numx = 0;
	int numy = 0;
	int flag = 0;
};

