#pragma once
#include "Global.h"
#include "GameData.h"

class AI
{
public:
	/*
	 * AI���ʼ������
	 * @param	depth
	 *			AI��˼�����,������δ���Ķ��ٲ�
	 * @param	id
	 *			AI����Ϸ�п��Ƶ����
	 * @param	time
	 *			AI�����ʱ������,��AI��˼����ȴ�,�����ĵ�ʱ���,���Ѿ����ĵ�ʱ����ڸ�ʱ������,AIֹͣ����
	 * @param	gameData
	 *			��Ϸ����
	 */
	AI(int depth, int id, long time, const class GameData* gameData);

	/*
	 * AI������һ���Ĳ���
	 * @return	AI��һ����ָ��
	 */
	Order getNextMove(void);
	
	/*
	 * AI�Ƿ����ڼ���
	 * @return	AI�Ƿ����ڼ���
	 */
	bool isRunning() const{ return isAIRunning; }
	
private:
	bool isAIRunning;
	int mSelfID;
	int mRivalID;
	int mThinkDepth;
	long mTimeLimited;

	class GameData* mGameData;
	const class GameData* mGameDataBackup;
	// ����AI�ڼ���Ĺ����л���ʱ�޸���Ϸ����,Ϊ��֤����ȫ��,mGameDataBackup�����洢����������Ϸ����
	// mGameDataΪ���ݵĿ���,���ж���Ϸ���ݵĸĶ�����mGameData�Ͻ���,���Բ�Ӱ��ԭ����.

	/*
	 * alphaBeta�㷨����,AI��getNextMove�лῼ�����м�����һ�������п��ܵ��ж��ͶԷ�����Ӧ��ȡ�Ĵ�ʩ
	 * ����alphaBeta�Ը��ж���������,����AI����������ж��ж����Լ���������һ����Ϊ��һ��.
	 */
	long alphaBeta(int depth, int player, long alpha, long beta);

	/*
	 * ��Ҫ!
	 * alphaBeta�����ۺ���,�ú�����ֱ�Ӿ���AI��ĳһ�ж������۷�ʽ,�ĺ�����ֱ�Ӿ���AI��ǿ��
	 * ʾ��;
	 * 1. �÷� = 100 - �ҷ����յ����̾��� + �з����յ����̾���
	 *    �����ۺ����ᵼ��AI�Ĳ��Ը��߽�����
	 * 2. �÷� = 100  - �ҷ����յ����̾��� + �з����յ����̾��� - �ҷ�ǽ������ + �з�ǽ������
	 *	  �����ۺ���ʹ��AI�ڼ�߽����Ե�ͬʱ,�ֲ�����ȵ�����ǽ������
	 */
	int evaluate(void) const;

	long long getSystemTime(void) const;
};