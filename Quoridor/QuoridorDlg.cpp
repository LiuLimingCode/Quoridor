
// QuoridorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Quoridor.h"
#include "QuoridorDlg.h"
#include "afxdialogex.h"
#include "Quyu.h"
#include "AI.h"
#include "GameService.h"
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQuoridorDlg 对话框



CQuoridorDlg::CQuoridorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QUORIDOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuoridorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WHOFIRST, m_whofirst);
}

BEGIN_MESSAGE_MAP(CQuoridorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_ENPUTBOARD, &CQuoridorDlg::OnBnClickedButtonEnputboard)
	ON_BN_CLICKED(IDC_BUTTON_ENPUTWALL, &CQuoridorDlg::OnBnClickedButtonEnputwall)
	ON_BN_CLICKED(IDC_BUTTON_MEPUTBOARD, &CQuoridorDlg::OnBnClickedButtonMeputboard)
	ON_BN_CLICKED(IDC_BUTTON_MEPUTWALL, &CQuoridorDlg::OnBnClickedButtonMeputwall)
	ON_BN_CLICKED(IDC_BUTTON_REGAME, &CQuoridorDlg::OnBnClickedButtonRegame)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CQuoridorDlg::OnBnClickedButtonUndo)
END_MESSAGE_MAP()


// CQuoridorDlg 消息处理程序

BOOL CQuoridorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	int i, j, m, n;
	CQuyu qy;
	for (n = 0, j = STARTAXIS_Y + SIZE_SQUARE * (NUM_SQUARE - 1); j >= STARTAXIS_Y; j = j - SIZE_SQUARE, n++)
	{
		for (m = 0, i = STARTAXIS_X; i != STARTAXIS_X + SIZE_SQUARE * NUM_SQUARE; i = i + SIZE_SQUARE, m++)
		{
			qy.x = i + SIZE_SQUARE / 2;
			qy.y = j + SIZE_SQUARE / 2;
			qy.numx = m;
			qy.numy = n;
			qy.flag = EMPTY;
			_qyboard.push_back(qy);
		}
	}

	for (m = 0 ,j = STARTAXIS_Y + SIZE_SQUARE * (NUM_SQUARE - 1); j >= STARTAXIS_Y ; j = j - SIZE_SQUARE, m++)
	{
		for (n = 0, i = STARTAXIS_X; i != STARTAXIS_X + SIZE_SQUARE * NUM_SQUARE; i = i + SIZE_SQUARE, n++)
		{
			qy.x = i + SIZE_SQUARE / 2;
			qy.y = j;
			qy.numx = n;
			qy.numy = m;
			qy.flag = EMPTY;
			_qywall[0].push_back(qy);
		}

		for (n = 0, i = STARTAXIS_X + SIZE_SQUARE; i != STARTAXIS_X + SIZE_SQUARE * (NUM_SQUARE + 1); i = i + SIZE_SQUARE, n++)
		{
			qy.x = i;
			qy.y = j + SIZE_SQUARE / 2;
			qy.numx = n;
			qy.numy = m;
			qy.flag = EMPTY;
			_qywall[1].push_back(qy);
		}
	}

	Gameservice.init(ai);

	GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_HIDE);

	m_text = _T("欢迎，这是一个步步为营游戏\r\n\r\n\r\n");
	m_text += _T("选择先手后开始游戏\r\n\r\n\r\n");
	m_text += _T("规则：\r\n\r\n");
	m_text += _T("--游戏开始时，角色放在边界，开始走向对面边界。每个玩家都有 8 块障碍，每个回合你可以选择移动自己的小人一格，或者选择摆放一块障碍阻挡对方，谁最先到达对面边界则为胜利者。\r\n\r\n\r\n");

	m_text += _T("\r\n\r\n\r\n作者：刘力铭\r\n");
	m_text += _T("时间：2018.8.6\r\n");

	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
	
	CString str;
	str.Format(_T(" X %d"), Gameservice._wallNumVt[PLAYER]);
	GetDlgItem(IDC_STATIC_MEWALLNUM)->SetWindowText(str);
	str.Format(_T(" X %d"), Gameservice._wallNumVt[COMPUTER]);
	GetDlgItem(IDC_STATIC_ENWALLNUM)->SetWindowText(str);

	_qyboard[Gameservice._posVt[PLAYER].y * NUM_SQUARE + Gameservice._posVt[PLAYER].x].flag = PLAYER;
	_qyboard[Gameservice._posVt[COMPUTER].y * NUM_SQUARE + Gameservice._posVt[COMPUTER].x].flag = COMPUTER;

	m_whofirst.AddString(_T("玩家"));
	m_whofirst.AddString(_T("电脑"));

	UpdateData(FALSE);

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQuoridorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQuoridorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CBrush myBrush;

		myBrush.CreateSolidBrush(COLOR_ENEMY);
		dc.FillRect(CRect(STARTAXIS_X, STARTAXIS_Y / 2 - SIZE_SQUARE / 2, STARTAXIS_X + SIZE_SQUARE, STARTAXIS_Y / 2 + SIZE_SQUARE / 2), &myBrush);
		myBrush.DeleteObject();

		myBrush.CreateSolidBrush(COLOR_ME);
		dc.FillRect(CRect(STARTAXIS_X, STARTAXIS_Y + SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y / 2 - SIZE_SQUARE / 2, STARTAXIS_X + SIZE_SQUARE, STARTAXIS_Y + SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y / 2 + SIZE_SQUARE / 2), &myBrush);
		myBrush.DeleteObject();

		if (start == true)
		{
			if (turn == PLAYER)
			{
				GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_MENOTE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(TRUE);
			}
			else if (turn == COMPUTER)
			{
				GetDlgItem(IDC_STATIC_MENOTE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(FALSE);
			}
			GetDlgItem(IDC_BUTTON_MEPUTBOARD)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_MEPUTWALL)->EnableWindow(TRUE);
			
		}
		else
		{
			GetDlgItem(IDC_BUTTON_MEPUTBOARD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_MEPUTWALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ENPUTBOARD)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_ENPUTWALL)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(FALSE);
		}

		switch (order)
		{
		case ORDER_MOVE:
			GetDlgItem(IDC_BUTTON_MEPUTBOARD)->EnableWindow(FALSE); break;
		case ORDER_WALL0:
			GetDlgItem(IDC_BUTTON_MEPUTWALL)->EnableWindow(FALSE); break;
		case ORDER_ENMOVE:
			GetDlgItem(IDC_BUTTON_ENPUTBOARD)->EnableWindow(FALSE); break;
		case ORDER_ENWALL0:
			GetDlgItem(IDC_BUTTON_ENPUTWALL)->EnableWindow(FALSE); break;
		default:
			break;
		}
		
		int i, j;
		
		for (i = STARTAXIS_X; i != SIZE_SQUARE * (NUM_SQUARE + 1) + STARTAXIS_X; i = i + SIZE_SQUARE)
		{
			dc.MoveTo(i, STARTAXIS_Y);
			dc.LineTo(i, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y);
		}
		for (j = STARTAXIS_Y; j != SIZE_SQUARE * (NUM_SQUARE + 1) + STARTAXIS_Y; j = j + SIZE_SQUARE)
		{
			dc.MoveTo(STARTAXIS_X, j);
			dc.LineTo(SIZE_SQUARE * NUM_SQUARE + STARTAXIS_X, j);
		}
		for (i = 0; i != _qyboard.size(); i++)
		{
			if (!_qyboard[i].isBoardEmpty())//下棋子
			{
				dc.BeginPath();//设置绘画区
				dc.Ellipse(&_qyboard[i].getRect());//设置绘画区的大小为椭圆形,大小由括号内的参数设置
				dc.EndPath();
				CBrush myBrush;
				if (_qyboard[i].isBoardPlayer())
					myBrush.CreateSolidBrush(COLOR_ME);//颜色
				else if (_qyboard[i].isBoardComputer())
					myBrush.CreateSolidBrush(COLOR_ENEMY);
				CBrush *oldBrush = dc.SelectObject(&myBrush);
				dc.FillPath();//颜色填充绘画区
				myBrush.DeleteObject();
				dc.SelectObject(oldBrush);
			}
		}
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i != _qywall[j].size(); i++)
			{
				if (_qywall[j][i].isWallPlayer() || _qywall[j][i].isWallComputer())
				{
					if (_qywall[j][i].isWallPlayer())
						myBrush.CreateSolidBrush(COLOR_ME);
					if(_qywall[j][i].isWallComputer())
						myBrush.CreateSolidBrush(COLOR_ENEMY);
					if(j == 0)
						dc.FillRect(CRect(_qywall[j][i].x - SIZE_SQUARE / 2 , _qywall[j][i].y - 4, _qywall[j][i].x + SIZE_SQUARE / 2, _qywall[j][i].y + 4), &myBrush);
					else if(j == 1)
						dc.FillRect(CRect(_qywall[j][i].x - 4, _qywall[j][i].y - SIZE_SQUARE / 2, _qywall[j][i].x + 4, _qywall[j][i].y + SIZE_SQUARE / 2), &myBrush);
					myBrush.DeleteObject();
					dc.SelectStockObject(BLACK_PEN);
				}
			}
		}
		switch (Gameservice.isend())
		{
		case PLAYER:
			MessageBox(_T("恭喜！你赢了！再接再厉！"));
			over = true;
			break;
		case COMPUTER:
			MessageBox(_T("电脑获胜！继续努力！"));
			over = true;
			break;
		default:
			break;
		}

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQuoridorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQuoridorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CQuyu qy;
	int temp_falg = 0;
	int i;
	CString str;

	if (start == false)
		return;

	if (turn != PLAYER)
		return;



	if ((order & 0x0f) == ORDER_MOVE)
	{
		for (i = 0; i != _qyboard.size(); i++)
		{
			if (_qyboard[i].isBoardOn(point) && !over && _qyboard[i].isBoardEmpty())
			{
				if (Gameservice.checkMove(_qyboard[i].numx, _qyboard[i].numy))
				{
					if (order == ORDER_MOVE)
					{
						_qyboard[i].flag = PLAYER;
						_qyboard[Gameservice._posVt[PLAYER].y * NUM_SQUARE + Gameservice._posVt[PLAYER].x].flag = EMPTY;
						Gameservice.gotoMove(PLAYER, _qyboard[i].numx, _qyboard[i].numy);
						turn = COMPUTER;
						Gameservice.CMD[PLAYER].push_back(std::make_pair(ORDER_MOVE, Vec2(_qyboard[i].numx, _qyboard[i].numy)));
						str.Format(_T("玩家 移动    至(%d, %d)\r\n"), Gameservice.CMD[PLAYER].back().second.x, Gameservice.CMD[PLAYER].back().second.y);
						m_text += str;
						GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
					}
				}
				
				break;
			}
		}
	}
	else if ((order & 0x0f) == ORDER_WALL0)
	{
		for (i = 0; i != _qywall[0].size(); i++)
		{
			if (_qywall[0][i].isWallOn(0, point) && !over && _qywall[0][i].isWallEmpty(0))
			{
				if (_qywall[0][_qywall[0][i].numy * NUM_SQUARE + _qywall[0][i].numx + 1].flag == EMPTY)
				{
					if (Gameservice.checkWall(0, _qywall[0][i].numx, _qywall[0][i].numy) && Gameservice._wallNumVt[PLAYER] > 0)
					{
						if (order == ORDER_WALL0)
						{
							_qywall[0][i].flag = PLAYER;
							_qywall[0][i + 1].flag = PLAYER;
							Gameservice.gotoWall(PLAYER, 0, _qywall[0][i].numx, _qywall[0][i].numy);
							turn = COMPUTER;
							Gameservice.CMD[PLAYER].push_back(std::make_pair(ORDER_WALL0, Vec2(_qyboard[i].numx, _qyboard[i].numy)));
							str.Format(_T("玩家 放横墙 至(%d, %d)\r\n"), Gameservice.CMD[PLAYER].back().second.x, Gameservice.CMD[PLAYER].back().second.y);
							m_text += str;
							GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
						}
					}
					break;
				}
			}
		}
		for (i = 0; i != _qywall[1].size(); i++)
		{
			if (_qywall[1][i].isWallOn(1, point) && !over && _qywall[1][i].isWallEmpty(1))
			{
				if (_qywall[1][(_qywall[1][i].numy + 1) * NUM_SQUARE + _qywall[1][i].numx].flag == EMPTY)
				{
					if (Gameservice.checkWall(1, _qywall[1][i].numx, _qywall[1][i].numy) && Gameservice._wallNumVt[PLAYER] > 0)
					{
						if (order == ORDER_WALL0)
						{
							_qywall[1][i].flag = PLAYER;
							_qywall[1][i + NUM_SQUARE].flag = PLAYER;
							Gameservice.gotoWall(PLAYER, 1, _qywall[1][i].numx, _qywall[1][i].numy);
							turn = COMPUTER;
							Gameservice.CMD[PLAYER].push_back(std::make_pair(ORDER_WALL1, Vec2(_qyboard[i].numx, _qyboard[i].numy)));
							str.Format(_T("玩家 放竖墙 至(%d, %d)\r\n"), Gameservice.CMD[PLAYER].back().second.x, Gameservice.CMD[PLAYER].back().second.y);
							m_text += str;
							GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
						}
					}
					break;
				}

			}
		}
	}

	Gameservice._plaShortLength = Gameservice.getShortPath(Gameservice._posVt[PLAYER], PLAYER);
	Gameservice._cmpShortLength = Gameservice.getShortPath(Gameservice._posVt[COMPUTER], COMPUTER);

	str.Format(_T(" X %d"), Gameservice._wallNumVt[PLAYER]);
	GetDlgItem(IDC_STATIC_MEWALLNUM)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), Gameservice._cmpShortLength);
	GetDlgItem(IDC_STATIC_ENWAY)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), Gameservice._plaShortLength);
	GetDlgItem(IDC_STATIC_MEWAY)->SetWindowText(str);

	Invalidate();
}

void CQuoridorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int temp_x = 0, temp_y = 0, temp;
	CString str;

	if (start == false)
		return;
	if (turn != COMPUTER)
		return;

	Gameservice.cmpMove(ai);

	temp_x = Gameservice.CMD[COMPUTER].back().second.x;
	temp_y = Gameservice.CMD[COMPUTER].back().second.y;
	temp = temp_y * NUM_SQUARE + temp_x;

	switch (Gameservice.CMD[COMPUTER].back().first)
	{
	case ORDER_MOVE:
		str.Format(_T("电脑 移动    至(%d, %d)\r\n"), temp_x, temp_y);
		m_text += str;
		GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
		_qyboard[temp].flag = COMPUTER;
		_qyboard[Gameservice._posVt[COMPUTER].y * NUM_SQUARE + Gameservice._posVt[COMPUTER].x].flag = EMPTY;
		Gameservice.gotoMove(COMPUTER, temp_x, temp_y);
		break;
	case ORDER_WALL0:
		str.Format(_T("电脑 放横墙 至(%d, %d)\r\n"), temp_x, temp_y);
		m_text += str;
		_qywall[0][temp].flag = COMPUTER;
		_qywall[0][temp + 1].flag = COMPUTER;
		Gameservice.gotoWall(COMPUTER, 0, temp_x, temp_y);
		break;
	case ORDER_WALL1:
		str.Format(_T("电脑 放竖墙 至(%d, %d)\r\n"), temp_x, temp_y);
		m_text += str;
		_qywall[1][temp].flag = COMPUTER;
		_qywall[1][temp + NUM_SQUARE].flag = COMPUTER;
		Gameservice.gotoWall(COMPUTER, 1, temp_x, temp_y);
		break;
	}

	Gameservice._plaShortLength = Gameservice.getShortPath(Gameservice._posVt[PLAYER], PLAYER);
	Gameservice._cmpShortLength = Gameservice.getShortPath(Gameservice._posVt[COMPUTER], COMPUTER);

	turn = PLAYER;

	str.Format(_T(" X %d"), Gameservice._wallNumVt[COMPUTER]);
	GetDlgItem(IDC_STATIC_ENWALLNUM)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), Gameservice._cmpShortLength);
	GetDlgItem(IDC_STATIC_ENWAY)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), Gameservice._plaShortLength);
	GetDlgItem(IDC_STATIC_MEWAY)->SetWindowText(str);

	GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_HIDE);

	Invalidate();

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CQuoridorDlg::OnBnClickedButtonEnputboard()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start == false)
		return;
	order = ORDER_ENMOVE;
	Invalidate();
}


void CQuoridorDlg::OnBnClickedButtonEnputwall()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start == false)
		return;
	order = ORDER_ENWALL0;
	Invalidate();
}


void CQuoridorDlg::OnBnClickedButtonMeputboard()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start == false)
		return;
	order = ORDER_MOVE;
	Invalidate();
}


void CQuoridorDlg::OnBnClickedButtonMeputwall()
{
	// TODO: 在此添加控件通知处理程序代码
	if (start == false)
		return;
	order = ORDER_WALL0;
	Invalidate();
}


void CQuoridorDlg::OnBnClickedButtonRegame()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON_REGAME)->SetWindowText(_T("重新开始"));

	m_text = "游戏开始 ";

	GetDlgItem(IDC_STATIC_NOTE)->ShowWindow(SW_HIDE);

	int i;
	for (i = 0; i != _qyboard.size(); i++)
	{
		_qyboard[i].flag = EMPTY;
	}
	for (i = 0; i != _qywall[0].size(); i++)
	{
		_qywall[0][i].flag = EMPTY;
	}
	for (i = 0; i != _qywall[1].size(); i++)
	{
		_qywall[1][i].flag = EMPTY;
	}

	Gameservice.init(ai);

	_qyboard[Gameservice._posVt[PLAYER].y * NUM_SQUARE + Gameservice._posVt[PLAYER].x].flag = PLAYER;
	_qyboard[Gameservice._posVt[COMPUTER].y * NUM_SQUARE + Gameservice._posVt[COMPUTER].x].flag = COMPUTER;

	CString str;
	str.Format(_T(" X %d"), Gameservice._wallNumVt[PLAYER]);
	GetDlgItem(IDC_STATIC_MEWALLNUM)->SetWindowText(str);
	str.Format(_T(" X %d"), Gameservice._wallNumVt[COMPUTER]);
	GetDlgItem(IDC_STATIC_ENWALLNUM)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), NUM_SQUARE - 1);
	GetDlgItem(IDC_STATIC_ENWAY)->SetWindowText(str);
	str.Format(_T("最短路径：%d"), NUM_SQUARE - 1);
	GetDlgItem(IDC_STATIC_MEWAY)->SetWindowText(str);

	over = false;
	start = true;
	order = ORDER_MOVE;
	turn = m_whofirst.GetCurSel();

	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);

	if (turn == COMPUTER)
	{
		m_text += "电脑 先手\r\n";
		OnLButtonUp(0, 0);
	}
	else
	{
		m_text += "玩家 先手\r\n";
	}
		
	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);
	Invalidate();
}

void CQuoridorDlg::OnBnClickedButtonUndo()
{
	int temp, i, j;
	// TODO: 在此添加控件通知处理程序代码
	if (turn == COMPUTER)
		return;
	if (Gameservice.CMD[PLAYER].size() >= 2)
	{
		m_text += _T("玩家悔棋\r\n");
		GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_text);

		auto cmdme = Gameservice.CMD[PLAYER].back();
		Gameservice.CMD[PLAYER].pop_back();
		auto cmden = Gameservice.CMD[COMPUTER].back();
		Gameservice.CMD[COMPUTER].pop_back();
		temp = cmdme.second.y * NUM_SQUARE + cmdme.second.x;

		switch (cmdme.first)
		{
		case ORDER_MOVE:
			Gameservice._board[(int)Gameservice._posVt[PLAYER].x][(int)Gameservice._posVt[PLAYER].y] = false;
			for (i = Gameservice.CMD[PLAYER].size() - 1; i > 0 && Gameservice.CMD[PLAYER][i].first != ORDER_MOVE; i--);
			Gameservice._posVt[PLAYER] = Gameservice.CMD[PLAYER][i].second;
			Gameservice._board[(int)Gameservice._posVt[PLAYER].x][(int)Gameservice._posVt[PLAYER].y] = true;
			for (j = 0; j != _qyboard.size(); j++)
				if (_qyboard[j].flag == PLAYER)_qyboard[j].flag = EMPTY;
			_qyboard[Gameservice.CMD[PLAYER][i].second.y * NUM_SQUARE + Gameservice.CMD[PLAYER][i].second.x].flag = PLAYER;
			break;
		case ORDER_WALL0:
			Gameservice._wallNumVt[PLAYER]++;
			Gameservice._wall[0][cmdme.second.x][cmdme.second.y] = false;
			_qywall[0][temp].flag = EMPTY;
			_qywall[0][temp + 1].flag = EMPTY;
			break;
		case ORDER_WALL1:
			Gameservice._wallNumVt[PLAYER]++;
			Gameservice._wall[1][cmdme.second.x][cmdme.second.y] = false;
			_qywall[1][temp].flag = EMPTY;
			_qywall[1][temp + NUM_SQUARE].flag = EMPTY;
			break;
		}
		temp = cmden.second.y * NUM_SQUARE + cmden.second.x;

		switch (cmden.first | 0x10)
		{
		case ORDER_ENMOVE:
			Gameservice._board[(int)Gameservice._posVt[COMPUTER].x][(int)Gameservice._posVt[COMPUTER].y] = false;
			for (i = Gameservice.CMD[COMPUTER].size() - 1; i > 0 && Gameservice.CMD[COMPUTER][i].first != ORDER_MOVE; i--);
			Gameservice._posVt[COMPUTER] = Gameservice.CMD[COMPUTER][i].second;
			Gameservice._board[(int)Gameservice._posVt[COMPUTER].x][(int)Gameservice._posVt[COMPUTER].y] = true;
			Gameservice._board[(int)Gameservice._posVt[PLAYER].x][(int)Gameservice._posVt[PLAYER].y] = true;
			for (j = 0; j != _qyboard.size(); j++)
				if (_qyboard[j].flag == COMPUTER)_qyboard[j].flag = EMPTY;
			_qyboard[Gameservice.CMD[COMPUTER][i].second.y * NUM_SQUARE + Gameservice.CMD[COMPUTER][i].second.x].flag = COMPUTER;
			break;
		case ORDER_ENWALL0:
			Gameservice._wallNumVt[COMPUTER]++;
			Gameservice._wall[0][cmden.second.x][cmden.second.y] = false;
			_qywall[0][temp].flag = EMPTY;
			_qywall[0][temp + 1].flag = EMPTY;
			break;
		case ORDER_ENWALL1:
			Gameservice._wallNumVt[COMPUTER]++;
			Gameservice._wall[1][cmden.second.x][cmden.second.y] = false;
			_qywall[1][temp].flag = EMPTY;
			_qywall[1][temp + NUM_SQUARE].flag = EMPTY;
			break;
		default:
			break;
		}

		if (over == true)
			over = false;

		Gameservice._plaShortLength = Gameservice.getShortPath(Gameservice._posVt[PLAYER], PLAYER);
		Gameservice._cmpShortLength = Gameservice.getShortPath(Gameservice._posVt[COMPUTER], COMPUTER);

		CString str;
		str.Format(_T(" X %d"), Gameservice._wallNumVt[PLAYER]);
		GetDlgItem(IDC_STATIC_MEWALLNUM)->SetWindowText(str);
		str.Format(_T(" X %d"), Gameservice._wallNumVt[COMPUTER]);
		GetDlgItem(IDC_STATIC_ENWALLNUM)->SetWindowText(str);
		str.Format(_T("最短路径：%d"), NUM_SQUARE - 1);
		GetDlgItem(IDC_STATIC_ENWAY)->SetWindowText(str);
		str.Format(_T("最短路径：%d"), NUM_SQUARE - 1);
		GetDlgItem(IDC_STATIC_MEWAY)->SetWindowText(str);

		Invalidate();
	}
}
