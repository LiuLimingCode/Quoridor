
// QuoridorDlg.h: 头文件
//

#pragma once

#include "Quyu.h"
#include "AI.h"
#include <vector>
using namespace std;

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

public:
	bool over;
	int order = -1;
	int turn;
	bool start;
	vector<CQuyu> _qyboard;
	vector<CQuyu> _qywall[2];
	GameService Gameservice;
	AI ai;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonEnputboard();
	afx_msg void OnBnClickedButtonEnputwall();
	afx_msg void OnBnClickedButtonMeputboard();
	afx_msg void OnBnClickedButtonMeputwall();
	afx_msg void OnBnClickedButtonRegame();
	CComboBox m_whofirst;
	afx_msg void OnBnClickedButtonUndo();
	CString m_text = '\0';
};
