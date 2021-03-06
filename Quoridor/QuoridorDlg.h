
// QuoridorDlg.h: 头文件
//

#pragma once

#include "GameDisplay.h"
#include "GameServer.h"
#include "GameGlobal.h"
#include <vector>
using namespace std;

#define COLOR_BLACK		RGB(0, 0, 0)
#define COLOR_RED		RGB(255, 0, 0)
#define COLOR_EMPTY		RGB(240, 240, 240)

// CQuoridorDlg 对话框
class CQuoridorDlg : public CDialogEx, GameServer
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

	void onGameStart(void);
	void onGameWin(int player);
	Order onPlayerOption(int turn);
	void onGameTurnEnd(int turn, Order order);
	void onBeforeOption(int turn);
	
private:
	HANDLE mGameHandle = nullptr;

	bool isGameOver = false;
	bool isGameStart = false;
	volatile bool isHandleWaittingOperate = false;
	volatile bool isHandleWaittingPaint = false;

    Order mPlayerNextWall;
    vector<Point> mPlayerNextStep;

	Order mOrder;
    CRect mGameBoundary = CRect(STARTAXIS_X, STARTAXIS_Y, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_X, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y);
	GameDisplay mGameDisplay;
	CString mText = '\0';
	int IDC_STATIC_WALLNUM[PAWN_NUM] = { IDC_STATIC_WALLNUM_PLAYER1, IDC_STATIC_WALLNUM_PLAYER2 };
	int IDC_STATIC_SHORTPATH[PAWN_NUM] = { IDC_STATIC_SHORTPATH_PLAYER1, IDC_STATIC_SHORTPATH_PLAYER2 };
    int IDC_RADIO_TURN[PAWN_NUM] = { IDC_RADIO_TURN1, IDC_RADIO_TURN2 };
    int IDC_COMBO_CONTROL[PAWN_NUM] = { IDC_COMBO_CONTROL1, IDC_COMBO_CONTROL2 };
    int IDC_RADIO_FIRST[PAWN_NUM] = { IDC_RADIO_FIRST1, IDC_RADIO_FIRST2 };
	COLORREF mColor[PAWN_NUM] = { COLOR_RED, COLOR_BLACK };
	const CString mRoleName[PAWN_NUM] = { _T("红色"), _T("黑色") };
};
