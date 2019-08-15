#pragma once

#include "Global.h"
#include <vector>

struct Region {
	int x = 0;
	int y = 0;
	int numx = 0;
	int numy = 0;
	bool isBoardOn(CPoint point) {
		bool flag = false;
		if (point.x < x + 15 && point.x > x - 15 && point.y < y + 15 && point.y > y - 15)
			flag = true;
		return flag;
	}
	bool isWallOn(int type, CPoint point) {
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

	CRect getPlayerRegion(CPoint point) const;
	vector<CRect> getWallRegion(vector<pair<CPoint, int>> wall) const;
	bool isBoardOn(CPoint point, Region region) const;
	bool isWallOn(int type, CPoint point, Region region) const;
	Order getPositionToOrder(CPoint point) const;

private:
	std::vector<Region> mRegionBoard;
	std::vector<Region> mRegionWall[2];
};

