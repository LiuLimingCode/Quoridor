#include "GameServer.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void onDraw(void);
Order getOrder(int turn, std::istream& is);

class QuoridorServer : public GameServer
{

public:

	// 人输入指令,操作游戏
	Order onPlayerOption(int turn)
	{
		return ::getOrder(turn, std::cin);
	}

	// 每个回合开始,绘制游戏界面
	void onBeforeOption(int turn)
	{
		::onDraw();
	}

	// 胜者出现,游戏出现
	void onGameWin(int pawn)
	{
		::onDraw();
		std::cout << (pawn ? "\n电脑获胜\n" : "\n玩家获胜\n") << std::endl;
	}

} Quoridor;

int main(int argc, char *argv[])
{
	Quoridor.resetGame();
	Quoridor.setGameAI(PAWN2, new AlphaBeta(1, 5000));
	//Quoridor.setGamePlayer(PAWN1);
    Quoridor.setGameAI(PAWN1, new AlphaBeta(1, 5000));
	Quoridor.GameHandle();
	system("pause");
	return 0;
}

Order getOrder(int turn, std::istream& is)
{
    bool isCorrect = false;
    Order order;
    std::cout << "\n输入指令如下格式所示：“type row col”或者输入“u”表示悔棋\n“type” M：移动  V：放竖墙  H：放横墙\n“row col”：指令的坐标" << std::endl;
    std::cout << "比如“m 3 2”意思为移动到(3,2)坐标\n" << std::endl;
    while (!isCorrect)
    {
        std::cout << ">";
        char type = '\0';
        int row = 0;
        int col = 0;
        is >> type;
        type = toupper(type);
        if (type != 'U') is >> order.point.row >> order.point.col;
        if (type == 'M' || type == 'V' || type == 'H')
        {
            if (type == 'M') order.type = OrderType::MOVE;
            else if (type == 'V') order.type = OrderType::WALLV;
            else if (type == 'H') order.type = OrderType::WALLH;
            if (Quoridor.checkOrder(turn, order) == true) isCorrect = true;
        }
        else if (type == 'U')
        {
            Quoridor.undoGame();
            onDraw();
            std::cout << "\n输入指令如下格式所示：“type row col”或者输入“u”表示悔棋\n“type” M：移动  V：放竖墙  H：放横墙\n“row col”：指令的坐标" << std::endl;
            std::cout << "比如“m 3 2”意思为移动到(3,2)坐标\n" << std::endl;
        }
        if (!(isCorrect || type == 'U')) std::cout << "错误指令" << std::endl;
    }
    return order;
}

void onDraw(void)
{
	int temp_h, temp_s, wall_h = 0, wall_v[NUM_SQUARE - 1] = { 0 };
	system("cls");
	int _wall[2][NUM_SQUARE][NUM_SQUARE] = { 0 };

	std::vector<std::pair<Point, int>> CurrentWall[2];
	CurrentWall[0] = Quoridor.getCurrentWall(PAWN1);
	CurrentWall[1] = Quoridor.getCurrentWall(PAWN2);
	for (int type = 0; type < 2; ++type)
	{
		for (int index = 0; index != CurrentWall[type].size(); ++index)
		{
			int row = CurrentWall[type].at(index).first.row;
			int col = CurrentWall[type].at(index).first.col;
			int z = CurrentWall[type].at(index).second;
			_wall[z][row][col] = 1;
		}
	}

	for (temp_s = 0; temp_s < 2 * NUM_SQUARE + 1; ++temp_s)
	{
		for (temp_h = 0; temp_h < 2 * NUM_SQUARE + 1; ++temp_h)
		{
			if (temp_s == 0 || temp_s == 2 * NUM_SQUARE) std::cout << "█";
			else if (temp_s % 2 == 1)
			{
				if (temp_h == 0 || temp_h == 2 * NUM_SQUARE) std::cout << "█";
				else if (temp_h % 2 == 0)//根据gameService.Wall来显示墙
				{
					if (wall_v[temp_h / 2 - 1] == 0 && temp_s < 2 * NUM_SQUARE - 1)
					{
						if (_wall[1][temp_h / 2 - 1][(2 * NUM_SQUARE - 2 - temp_s) / 2] != 0)
						{
							wall_v[temp_h / 2 - 1] = 2;
						}
					}
					if (wall_v[temp_h / 2 - 1] > 0)
					{
						std::cout << "█";
						--wall_v[temp_h / 2 - 1];
					}
					else
						std::cout << "丨";
				}
				else//根据player和robot坐标来显示玩家
				{
					if (Quoridor.getCurrentPosition(PAWN1).row == (temp_h - 1) / 2 && Quoridor.getCurrentPosition(PAWN1).col == (2 * NUM_SQUARE - temp_s - 1) / 2)
						std::cout << "♂";
					else if (Quoridor.getCurrentPosition(PAWN2).row == (temp_h - 1) / 2 && Quoridor.getCurrentPosition(PAWN2).col == (2 * NUM_SQUARE - temp_s - 1) / 2)
						std::cout << "♀";
					else
						std::cout << "  ";
				}
			}
			else
			{
				if (temp_h == 0 || temp_h == 2 * NUM_SQUARE) std::cout << "█";
				else
				{
					if (wall_h == 0)//显示横墙
					{
						if (_wall[0][(temp_h - 1) / 2][(2 * NUM_SQUARE - 1 - temp_s) / 2] != 0)
							wall_h = 3;
					}
					if (wall_h > 0)
					{
						std::cout << "█";
						wall_h--;
					}
					else if (temp_h % 2 == 0 && wall_v[temp_h / 2 - 1] == 1)
						std::cout << "█";
					else std::cout << "--";
				}
			}
		}
		if (temp_s % 2) std::cout << (2 * NUM_SQUARE - temp_s - 1) / 2;//显示Y轴坐标
		std::cout << std::endl;
	}
	for (temp_h = 0; temp_h < 2 * NUM_SQUARE + 1; ++temp_h)
	{
		if (temp_h % 2) std::cout << " " << (temp_h - 1) / 2;//显示X轴坐标
		else std::cout << "  ";
	}
	std::cout << std::endl;
	std::cout << "玩家  墙数：" << Quoridor.getCurrentWallNum(PAWN1) << "    最近步数" << Quoridor.getShortPath(PAWN1) << std::endl;
	std::cout << "电脑  墙数：" << Quoridor.getCurrentWallNum(PAWN2) << "    最近步数" << Quoridor.getShortPath(PAWN2) << std::endl;
}
