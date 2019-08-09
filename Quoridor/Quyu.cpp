#include "stdafx.h"
#include "Quyu.h"


CQuyu::CQuyu(void)
{
	x = 0;
	y = 0;
	flag = 0;
}

CQuyu::~CQuyu(void)
{
}

CRect CQuyu::getRect(void)
{
	CRect rect;
	rect.left = x - 15;
	rect.right = x + 15;
	rect.top = y - 15;
	rect.bottom = y + 15;
	return rect;
}

bool CQuyu::isBoardOn(CPoint point)
{
	bool flag = false;
	if (point.x<x + 15 && point.x>x - 15 && point.y<y + 15 && point.y>y - 15)
		flag = true;
	return flag;
}

bool CQuyu::isBoardEmpty(void)
{
	if (flag == EMPTY)
		return true;
	else
		return false;
}

bool CQuyu::isBoardPlayer(void)
{
	if (flag == PLAYER)
		return true;
	else
		return false;
}

bool CQuyu::isBoardComputer(void)
{
	if (flag == COMPUTER)
		return true;
	else
		return false;
}

bool CQuyu::isWallOn(int type, CPoint point)
{
	bool flag = false;
	if (type == 0 && point.x<x + 15 && point.x>x - 15 && point.y<y + 4 && point.y>y - 4)
		flag = true;
	if (type == 1 && point.x<x + 4 && point.x>x - 4 && point.y<y + 15 && point.y>y - 15)
		flag = true;
	return flag;
}

bool CQuyu::isWallEmpty(int type)
{
	if(type == 0 && flag == EMPTY && numx < 6 && numy < 6)
		return true;
	if(type == 1 && flag == EMPTY && numy < 6 && numy < 6)
		return true;
	else
		return false;
}

bool CQuyu::isWallPlayer(void)
{
	if (flag == PLAYER)
		return true;
	else
		return false;
}

bool CQuyu::isWallComputer(void)
{
	if (flag == COMPUTER)
		return true;
	else
		return false;
}
