/*
 * Quoridor��Ϸ���ݺ���Ӧ�Ĳ�������
 * @author  ������
 * @version v1.3
 * @Date    2019.9.27
 */

#pragma once

#include <vector>
#include "GameGlobal.h"

class GameData
{
public:

    GameData() = default;
    GameData(int boardSize);

    /*
     * ���¿�ʼ��Ϸ
     */
    void resetGame(int boardSize);

    /*
     * ����
     */
    void undoGame(void);

    /*
     * ����ִ��ĳָ��
     * @param   pawn
     *          ����ID
     * @param   order
     *          ��Ҫִ�е�ָ��
     * @note    ע�⣺setOrder�����൱�ڳ������Order������,�Զ����ö��ڵ�
     *          setMove��setWall����.
     */
    void setOrder(int pawn, Order order);

    /*
     * �������嵽ĳ����
     * @param   pawn
     *          ����ID
     * @param   row
     *          ��������ĺ�����
     * @param   col
     *          ���������������
     */
    void setMove(int pawn, int row, int col);

    /*
     * ȡ��ĳλ�õ�ǽ
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   row
     *          ����ǽ�ĺ�����
     * @param   col
     *          ����ǽ��������
     */
    void setWall(int pawn, int type, int row, int col);

    /*
     * ���ӷ�ǽ��ĳ����
     * @param   pawn
     *          ����ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   row
     *          ����ǽ�ĺ�����
     * @param   col
     *          ����ǽ��������
     */
    void resetWall(int type, int row, int col);

    /*
     * �õ�ĳ���ӵ��յ�����·��
     * @param   pawn
     *          ����ID
     * @return  ��̵ľ���
     * @note    ˽�б���mPlayerShortLength[]����ŵ�ǰ����ĸ������ӵ����·��,��ÿ��
     *          ����gotoMove��gotoWall��,������Զ����øú�������mPlayerShortLength����,
     *          ����ֱ�ӵ���getCurrentShortPath()�����õ���̾���.
     */
    int getShortPath(int pawn) const;

    /*
     * �ж��Ƿ������ӵ��յ�
     * @return  ���յ����ӵ�ID,���û�����ӵ��յ�,����-1,��PLAYERIDö����
     */
    int isGameEnd(void) const;

    /*
     * �ж�ָ���Ƿ�Ϻ�����
     * @param   pawn
     *          ����ID
     * @param   order
     *          ָ��
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     * @note    �ú�����checkWall()������checkMove()����������
     */
    bool checkOrder(int pawn, Order order) const;

    /*
     * �ж�������ĳ�����Ϸ�ǽ�Ƿ�Ϻ�����
     * @param   pawn
     *          ����ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   row
     *          ǽ�ĺ�����
     * @param   col
     *          ǽ��������
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     */
    bool checkWall(int pawn, int type, int row, int col) const;

    /*
     * �ж������ƶ���ĳ���Ƿ�Ϻ�����
     * @param   pawn
     *          ����ID
     * @param   type
     *          ǽ������,0�����ǽ,1������ǽ,��Order_type
     * @param   row
     *          ��������ĺ�����
     * @param   col
     *          ���������������
     * @return  trueΪ�Ϻ�����,falseΪΥ������
     */
    bool checkMove(int pawn, int row, int col) const;

    /*
     * �õ����ӵ��յ����̾���
     * @param   pawn
     *          ����ID
     * @return  ��̾���
     * @note    �÷���ֵ�Ǵ洢��˽�б���mPlayerShortLength[]�е�����
     */
    int getCurrentShortPath(int pawn) const;

    /*
     * �õ�����ʣ��ǽ������
     * @param   pawn
     *          ����ID
     * @return  ʣ��ǽ������
     */
    int getCurrentWallNum(int pawn) const;

    /*
     * �õ�����Ŀǰ�������ϵ�����
     * @param   pawn
     *          ����ID
     * @return  ���ӵ�����
     */
    Point getCurrentPosition(int pawn) const;

    /*
     * �õ�����Ŀǰ���������Ѿ��ŵ�ǽ
     * @param   pawn
     *          ����ID
     * @return  �������������Ϸŵ�ǽ,��������Ϊ<ǽ������,ǽ������>
     */
    std::vector<std::pair<Point, int>> getCurrentWall(int pawn) const;

    /*
     * �õ�������Ŀǰ�ܹ��ߵ�λ��
     * @param   pawn
     *          ����ID
     * @return  ������Ŀǰ�ܹ��ߵ�����
     */
    std::vector<Point> getNextMoveVaild(int pawn, bool isConsiderOtherPawn) const;

    /*
     * �õ�������Ŀǰ�ܹ���ǽ��λ��
     * @param   pawn
     *          ����ID
     * @return  �������ܹ���ǽ��λ��,��������Ϊ<ǽ������,ǽ������>
     */
    std::vector<std::pair<Point, int>> getNextWallValid(int pawn) const;

    /*
     * �жϸ������µ�ǽ�Ƿ�Խ��

     */
    bool isWall(int row, int col) const;

    /*
     * �жϸ������µĵ��Ƿ�Խ��
     * @param   row
     *          ������
     */
    bool isPoint(int row, int col) const;

protected:

    /*
     * �������ӵ�ʤ������
     * @note    ע�⣺����Щ�����������û�����,�û�����ʹ��isEnd()�����ж���Ϸ�Ƿ����
     *          ���ǿ���ͨ�����ظú����޸���Ϸ��ʤ������
     */
    virtual bool isPawn1Win(void) const { return CONDITION_PAWN1_WIN(mPawnPosition[0]) ? true : false; }
    virtual bool isPawn2Win(void) const { return CONDITION_PAWN2_WIN(mPawnPosition[1]) ? true : false; }

    /*
     * �������ӵ���ʼ����
     * @note    ע�⣺����Щ�����������û�����,���ǿ���ͨ�����ظú����޸���Ϸ����ʼ����
     */
    virtual void setPawn1Start(void) { CONDITION_PAWN1_START(mPawnPosition[0]); }
    virtual void setPawn2Start(void) { CONDITION_PAWN2_START(mPawnPosition[1]); }

protected:

    //_probableNextWalls
    //validNextWalls
    //_validNextPositions
    //_validNextPositionsUpdated

    int mTurn;

    int mWallNum[PAWN_NUM];

    //����������Ϣ
    Array2D<int> mWall[2];

    int mBoardSize;

    std::vector<Order> mOrderBuffer[PAWN_NUM];

    int mPawnShortLength[PAWN_NUM];
    //����λ��
    Point mPawnPosition[PAWN_NUM];

    bool(GameData::* isPawnWin[MAX_PAWN_NUM])(void) const = {
        &GameData::isPawn1Win, &GameData::isPawn2Win };
    
    void (GameData::* setPawnStart[MAX_PAWN_NUM])(void) = {
        &GameData::setPawn1Start, &GameData::setPawn2Start };
};

