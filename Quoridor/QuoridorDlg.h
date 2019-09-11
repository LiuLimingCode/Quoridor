
// QuoridorDlg.h: 头文件
//

#pragma once

#include "GameDisplay.h"
#include "GameData.h"
#include "GameGlobal.h"
#include "AI.h"
#include <vector>
using namespace std;

#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_EMPTY		RGB(240, 240, 240)

// CQuoridorDlg 对话框
class CQuoridorDlg : public CDialogEx
{
// 构造
public:
	CQuoridorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUORIDOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	static DWORD WINAPI QuoridorGame(LPVOID pParameter);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonRegame();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnClose();
	void updateInformationText();
	
private:
	CComboBox mWhoFirst;
	HANDLE mGameHandle;

	bool isGameOver = false;
	bool isGameStart = false;
	volatile bool isHandleWaittingOperate = false;
	volatile bool isHandleWaittingPaint = false;

    Order mPlayerNextWall;
    int mColorPlayer;
    vector<Point> mPlayerNextStep;

	Order mOrder;
	int mTurn;
    CRect mGameBoundary = CRect(STARTAXIS_X, STARTAXIS_Y, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_X, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y);
	GameData mGameData;
	GameDisplay mGameDisplay;
	CString mText = '\0';
	AI * mAI[PLAYER_NUM];
	int IDC_STATIC_WALLNUM[PLAYER_NUM] = { IDC_STATIC_WALLNUM_PLAYER1, IDC_STATIC_WALLNUM_PLAYER2 };
	int IDC_STATIC_SHORTPATH[PLAYER_NUM] = { IDC_STATIC_SHORTPATH_PLAYER1, IDC_STATIC_SHORTPATH_PLAYER2 };
	COLORREF mColor[PLAYER_NUM] = { COLOR_RED, COLOR_BLACK };
	const CString TEXT_HELP = _T(
"欢迎，这是一个步步为营游戏\r\n\r\n\r\n\
选择先手后开始游戏\r\n\r\n\r\n规则：\r\n\r\n\
--游戏开始时，角色放在边界，开始走向对面边界。每个玩家都有 8 块障碍，\
每个回合你可以选择移动自己的小人一格，或者选择摆放一块障碍阻挡对方，\
谁最先到达对面边界则为胜利者。\r\n\r\n\r\n\
\r\n\r\n\r\n作者：刘力铭\r\n\
时间：2018.8.6\r\n");
};
