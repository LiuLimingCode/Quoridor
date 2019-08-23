#pragma once

#include "Global.h"
#include <iostream>
#include <vector>
#include "AI.h"
#include <cstdlib>
#include <ctime>

class GameData
{
public:
	GameData();

	/*
	 * ���¿�ʼ��Ϸ
	 */
	void resetGame(void);

	/*
	 * ����
	 */
	void undoGame(void);

	/*
	 * ������嵽ĳ����
	 * @param   player
	 *          ���ID
	 * @param   x
	 *          �������ĺ�����
	 * @param   y
	 *          ��������������
	 * @note    ע�⣺�����setMove��resetMove,gotoMove����ʽ�����庯��,��ִ��
	 *          �ú���ǰ,Ӧ����checkMove��������Ƿ�Ϻ�����.�ڸú���ִ�к�,
	 *          ���Զ�ִ��getShortPath�����õ���ǰ����̾���,���ҽ���ָ���¼.
	 */
	void gotoMove(int player, int x, int y);

	/*
	 * ��ҷ�ǽ��ĳ����
	 * @param   player
	 *          ���ID
	 * @param   type
	 *          ǽ������,0�����ǽ,1������ǽ,��Order_type
	 * @param   x
	 *          ���ǽ�ĺ�����
	 * @param   y
	 *          ���ǽ��������
	 * @note    ע�⣺�����setWall��resetMove,gotoWall����ʽ�ķ�ǽ����,��ִ��
	 *          �ú���ǰ,Ӧ����checkWall����ǽ�Ƿ�Ϻ�����.�ڸú���ִ�к�,
	 *          ���Զ�ִ��getShortPath�����õ���ǰ����̾���,���ҽ���ָ���¼.
	 */
	void gotoWall(int player, int type, int x, int y);

	/*
	 * ������嵽ĳ����
	 * @param   player
	 *          ���ID
	 * @param   x
	 *          �������ĺ�����
	 * @param   y
	 *          ��������������
	 * @note    ע�⣺�����gotoMove,setMove�Ƿ���ʽ�����庯��,�ú���ֻ��AI���
	 *          GameData���ڲ�����ʹ��,���������ʹ��.
	 */
	void setMove(int player, int x, int y);

    /*
     * �������������ϵ�����
     * @param   player
     *          ���ID
     * @note    ע�⣺�����gotoMove,resetMove�Ƿ���ʽ�����庯��,�ú���ֻ��AI���
     *          GameData���ڲ�����ʹ��,���������ʹ��.
     */
	void resetMove(int player);

    /*
     * ��ҷ�ǽ��ĳ����
     * @param   player
     *          ���ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   x
     *          ���ǽ�ĺ�����
     * @param   y
     *          ���ǽ��������
     * @note    ע�⣺�����gotoWall,setWall�Ƿ���ʽ�ķ�ǽ����,�ú���ֻ��AI���
     *          GameData���ڲ�����ʹ��,���������ʹ��.
     */
	void setWall(int player, int type, int x, int y);

    /*
     * �������������ϵ�ǽ
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   x
     *          ���ǽ�ĺ�����
     * @param   y
     *          ���ǽ��������
     * @note    ע�⣺�����gotoWall,resetWall�Ƿ���ʽ�ķ�ǽ����,�ú���ֻ��AI���
     *          GameData���ڲ�����ʹ��,���������ʹ��.
     */
	void resetWall(int type, int x, int y);

    /*
     * �õ�ĳ��ҵ��յ�����·��
     * @param   player
     *          ���ID
     * @return  ��̵ľ���
     * @note    ˽�б���mPlayerShortLength[]����ŵ�ǰ����ĸ�����ҵ����·��,��ÿ��
     *          ����gotoMove��gotoWall��,������Զ����øú�������mPlayerShortLength����,
     *          ����ҿ���ֱ�ӵ���getCurrentShortPath()�����õ���̾���.
     */
	int getShortPath(int player) const;

    /*
     * �ж��Ƿ�����ҵ��յ�
     * @return  ���յ���ҵ�ID,���û����ҵ��յ�,����-1,��PLAYERIDö����
     */
	int isEnd(void) const;

    /*
     * �ж�ָ���Ƿ�Ϻ�����
     * @param   player
     *          ���ID
     * @param   order
     *          ָ��
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     * @note    �ú�����checkWall()������checkMove()����������
     */
	bool checkOrder(int player, Order order) const;

    /*
     * �ж������ĳ�����Ϸ�ǽ�Ƿ�Ϻ�����
     * @param   player
     *          ���ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   x
     *          ���ǽ�ĺ�����
     * @param   y
     *          ���ǽ��������
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     */
	bool checkWall(int player, int type, int x, int y) const;

    /*
     * �ж�����ƶ���ĳ���Ƿ�Ϻ�����
     * @param   player
     *          ���ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   x
     *          �������ĺ�����
     * @param   y
     *          ��������������
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     */
	bool checkMove(int player, int x, int y) const;

    /*
     * �õ���ҵ��յ����̾���
     * @param   player
     *          ���ID
     * @return  ��̾���
     * @note    �÷���ֵ�Ǵ洢��˽�б���mPlayerShortLength[]�е�����
     */
	int getCurrentShortPath(int player) const;

    /*
     * �õ����ʣ��ǽ������
     * @param   player
     *          ���ID
     * @return  ʣ��ǽ������
     */
	int getCurrentWallNum(int player) const;

    /*
     * �õ����Ŀǰ�������ϵ�����
     * @param   player
     *          ���ID
     * @return  ��ҵ�����
     */
	Point getCurrentPosition(int player) const;

    /*
     * �õ����Ŀǰ���������Ѿ��ŵ�ǽ
     * @param   player
     *          ���ID
     * @return  ������������Ϸŵ�ǽ,��������Ϊ<ǽ������,ǽ������>
     */
	std::vector<std::pair<Point, int>> getCurrentWall(int player) const;

    /*
     * �õ������Ŀǰ�ܹ��ߵ�λ��
     * @param   player
     *          ���ID
     * @return  �����Ŀǰ�ܹ��ߵ�����
     */
	std::vector<Point> getMoveVaild(int player) const;

    /*
     * �õ������Ŀǰ�ܹ���ǽ��λ��
     * @param   player
     *          ���ID
     * @return  ������ܹ���ǽ��λ��,��������Ϊ<ǽ������,ǽ������>
     */
	std::vector<std::pair<Point, int>> getWallVaild(int player) const;

private:

    /*
     * �жϸ������µ�ǽ�Ƿ�Խ��
     */
    bool isWall(int x, int y) const;

    /*
     * �жϸ������µĵ��Ƿ�Խ��
     */
    bool isPoint(int x, int y) const;

	int mWallNum[PLAYER_NUM];

	//����������Ϣ
	int mWall[2][NUM_SQUARE][NUM_SQUARE] = { 0 };
	bool mBoard[NUM_SQUARE][NUM_SQUARE] = { 0 };

	std::vector<Order> mOrderBuffer[PLAYER_NUM];

	int mPlayerShortLength[PLAYER_NUM];
	//����λ��
	Point mPlayerPosition[PLAYER_NUM];

	bool(GameData::* isPlayerWin[MAX_PLAYER_NUM])(void) const = { &GameData::isPlayer1Win, &GameData::isPlayer2Win, &GameData::isPlayer3Win, &GameData::isPlayer4Win };
	bool isPlayer1Win(void) const { return CONDITION_PLAYER1_WIN(mPlayerPosition[0]) ? true : false; }
	bool isPlayer2Win(void) const { return CONDITION_PLAYER2_WIN(mPlayerPosition[1]) ? true : false; }
	bool isPlayer3Win(void) const { return CONDITION_PLAYER3_WIN(mPlayerPosition[2]) ? true : false; }
	bool isPlayer4Win(void) const { return CONDITION_PLAYER4_WIN(mPlayerPosition[3]) ? true : false; }
	
	void (GameData::* setPlayerStart[MAX_PLAYER_NUM])(void) = { &GameData::setPlayer1Start, &GameData::setPlayer2Start, &GameData::setPlayer3Start, &GameData::setPlayer4Start };
	void setPlayer1Start(void) { CONDITION_PLAYER1_START(mPlayerPosition[0]); }
	void setPlayer2Start(void) { CONDITION_PLAYER2_START(mPlayerPosition[1]); }
	void setPlayer3Start(void) { CONDITION_PLAYER3_START(mPlayerPosition[2]); }
	void setPlayer4Start(void) { CONDITION_PLAYER4_START(mPlayerPosition[3]); }
};

