#pragma once

#include <vector>
#include "GameGlobal.h"

#define SIZE_SQUARE		40
#define SIZE_WALL		8
#define STARTAXIS_X		280
#define STARTAXIS_Y		105

struct Region {
	int x = 0;
	int y = 0;
	int numx = 0;
	int numy = 0;
	bool isBoardOn(Point point) {
		bool flag = false;
		if (point.x < x + 15 && point.x > x - 15 && point.y < y + 15 && point.y > y - 15)
			flag = true;
		return flag;
	}
	bool isWallOn(int type, Point point) {
		bool flag = false;
		if (type == 0 && point.x < x + 15 && point.x > x - 15 && point.y < y + 4 && point.y > y - 4)
			flag = true;
		if (type == 1 && point.x < x + 4 && point.x > x - 4 && point.y < y + 15 && point.y > y - 15)
			flag = true;
		return flag;
	}
};

class GameDisplay
{
public:

	GameDisplay(void);
	~GameDisplay(void) = default;

	CRect getPlayerRegion(Point point) const;
    CRect getWallRegion(std::pair<Point, int> wall) const;
	std::vector<CRect> getWallRegion(std::vector<std::pair<Point, int>> wall) const;
	bool isBoardOn(Point point, Region region) const;
	bool isWallOn(int type, Point point, Region region) const;
	Order getPositionToOrder(Point point) const;

private:

	std::vector<Region> mRegionBoard;
	std::vector<Region> mRegionWall[2];
};

