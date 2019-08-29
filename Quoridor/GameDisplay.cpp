#include "stdafx.h"
#include "GameDisplay.h"
#include <vector>

GameDisplay::GameDisplay(void)
{
	Region region;
	int i, j, m, n;
	for (n = 0, j = STARTAXIS_Y + SIZE_SQUARE * (NUM_SQUARE - 1); j >= STARTAXIS_Y; j = j - SIZE_SQUARE, n++)
	{
		for (m = 0, i = STARTAXIS_X; i != STARTAXIS_X + SIZE_SQUARE * NUM_SQUARE; i = i + SIZE_SQUARE, m++)
		{
			region.x = i + SIZE_SQUARE / 2;
			region.y = j + SIZE_SQUARE / 2;
			region.numx = m;
			region.numy = n;
			mRegionBoard.push_back(region);
		}
	}

	for (m = 0, j = STARTAXIS_Y + SIZE_SQUARE * (NUM_SQUARE - 1); j >= STARTAXIS_Y; j = j - SIZE_SQUARE, m++)
	{
		for (n = 0, i = STARTAXIS_X; i != STARTAXIS_X + SIZE_SQUARE * NUM_SQUARE; i = i + SIZE_SQUARE, n++)
		{
			region.x = i + SIZE_SQUARE / 2;
			region.y = j;
			region.numx = n;
			region.numy = m;
			mRegionWall[0].push_back(region);
		}

		for (n = 0, i = STARTAXIS_X + SIZE_SQUARE; i != STARTAXIS_X + SIZE_SQUARE * (NUM_SQUARE + 1); i = i + SIZE_SQUARE, n++) {
			region.x = i;
			region.y = j + SIZE_SQUARE / 2;
			region.numx = n;
			region.numy = m;
			mRegionWall[1].push_back(region);
		}
	}
}

CRect GameDisplay::getPlayerRegion(Point point) const
{
	auto region = mRegionBoard[point.y * NUM_SQUARE + point.x];

	CRect rect;
	rect.left = region.x - 15;
	rect.right = region.x + 15;
	rect.top = region.y - 15;
	rect.bottom = region.y + 15;
	return rect;
}

CRect GameDisplay::getWallRegion(std::pair<Point, int> wall) const
{
    CRect rect;
    Point point = wall.first;
    int type = wall.second;
    if (type == 0)
    {
        auto region = mRegionWall[type][point.y * NUM_SQUARE + point.x];
        rect = CRect(region.x - SIZE_SQUARE / 2, region.y - 4, region.x + SIZE_SQUARE / 2 + SIZE_SQUARE, region.y + 4);
    }
    else if (type == 1)
    {
        auto region = mRegionWall[type][point.y * NUM_SQUARE + point.x];
        rect = CRect(region.x - 4, region.y - SIZE_SQUARE / 2 - SIZE_SQUARE, region.x + 4, region.y + SIZE_SQUARE / 2);
    }
    return rect;
}

std::vector<CRect> GameDisplay::getWallRegion(std::vector<std::pair<Point, int>> wall) const
{
    std::vector<CRect> rects;
	for (auto index = 0; index != wall.size(); ++index)
	{
        rects.push_back(getWallRegion(wall[index]));
	}
	return rects;
}

bool GameDisplay::isBoardOn(Point point, Region region) const
{
	bool flag = false;
	if (point.x < region.x + 15 && point.x > region.x - 15 && point.y < region.y + 15 && point.y > region.y - 15)
		flag = true;
	return flag;
}

bool GameDisplay::isWallOn(int type, Point point, Region region) const
{
	bool flag = false;
	if (type == 0 && point.x < region.x + 15 && point.x > region.x - 15 && point.y < region.y + 4 && point.y > region.y - 4)
		flag = true;
	if (type == 1 && point.x < region.x + 4 && point.x > region.x - 4 && point.y < region.y + 15 && point.y > region.y - 15)
		flag = true;
	return flag;
}

Order GameDisplay::getPositionToOrder(Point point) const
{
	Order order;
	for (auto index = 0; index != mRegionBoard.size(); ++index)
	{
		if (isBoardOn(point, mRegionBoard[index]))
		{
			order = Order(MOVE, mRegionBoard[index].numx, mRegionBoard[index].numy);
			return order;
		}
	}

	for (int type = 0; type <= 1; ++type)
	{
		for (auto index = 0; index != mRegionWall[type].size(); ++index)
		{
			if (isWallOn(type, point, mRegionWall[type][index]))
			{
				order = Order(type, mRegionWall[type][index].numx, mRegionWall[type][index].numy);
				return order;
			}
		}
	}
	return order;
}
