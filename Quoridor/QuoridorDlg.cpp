
// QuoridorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Quoridor.h"
#include "QuoridorDlg.h"
#include "afxdialogex.h"
#include "AI.h"
#include "GameDisplay.h"
#include "GameData.h"
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
	DDX_Control(pDX, IDC_COMBO_WHOFIRST, mWhoFirst);
}

BEGIN_MESSAGE_MAP(CQuoridorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_REGAME, &CQuoridorDlg::OnBnClickedButtonRegame)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CQuoridorDlg::OnBnClickedButtonUndo)
END_MESSAGE_MAP()


// CQuoridorDlg 消息处理程序
// 界面的初始化程序
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	mText = TEXT_HELP;
	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(mText);

	CString str;
	for (int player = 0; player < PLAYER_NUM; ++player) {
		str.Format(_T(" X %d"), mGameData.getCurrentWallNum(player));
		GetDlgItem(IDC_STATIC_WALLNUM[player])->SetWindowText(str);
	}

	mWhoFirst.AddString(_T("玩家"));
	mWhoFirst.AddString(_T("电脑"));
    mWhoFirst.SelectString(0, _T("玩家"));
	mAI[1] = new AI(1, PLAYER2, 5000, &mGameData);

	UpdateData(FALSE);

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
// 界面的重绘函数，界面上所有的图像都在这里绘画
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
		CPaintDC paintDC(this);
		CBrush brush;

		brush.CreateSolidBrush(mColor[PLAYER2]);
		paintDC.FillRect(CRect(STARTAXIS_X, STARTAXIS_Y / 2 - SIZE_SQUARE / 2, STARTAXIS_X + SIZE_SQUARE, STARTAXIS_Y / 2 + SIZE_SQUARE / 2), &brush);
		brush.DeleteObject();

		brush.CreateSolidBrush(mColor[PLAYER1]);
		paintDC.FillRect(CRect(STARTAXIS_X, STARTAXIS_Y + SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y / 2 - SIZE_SQUARE / 2, STARTAXIS_X + SIZE_SQUARE, STARTAXIS_Y + SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y / 2 + SIZE_SQUARE / 2), &brush);
		brush.DeleteObject();

		if (isGameStart == true)
		{
			if (mAI[mTurn] == nullptr) GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(TRUE);
			else GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(FALSE); 
		}
		else GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(FALSE); 
		
		int i, j;// 画界面上棋盘的线
		for (i = STARTAXIS_X; i != SIZE_SQUARE * (NUM_SQUARE + 1) + STARTAXIS_X; i = i + SIZE_SQUARE)
		{
			paintDC.MoveTo(i, STARTAXIS_Y);
			paintDC.LineTo(i, SIZE_SQUARE * NUM_SQUARE + STARTAXIS_Y);
		}
        for (j = STARTAXIS_Y; j != SIZE_SQUARE * (NUM_SQUARE + 1) + STARTAXIS_Y; j = j + SIZE_SQUARE)
        {
            paintDC.MoveTo(STARTAXIS_X, j);
            paintDC.LineTo(SIZE_SQUARE * NUM_SQUARE + STARTAXIS_X, j);
        }

		for (int player = 0; player < PLAYER_NUM; ++player)
		{
			paintDC.BeginPath();//设置绘画区
			paintDC.Ellipse(mGameDisplay.getPlayerRegion(mGameData.getCurrentPosition(player)));//设置绘画区的大小为椭圆形,大小由括号内的参数设置
			paintDC.EndPath();// 画棋子
			brush.CreateSolidBrush(mColor[player]);
			CBrush* oldBrush = paintDC.SelectObject(&brush);
			paintDC.FillPath();//颜色填充绘画区

			std::vector<CRect> wallRect = mGameDisplay.getWallRegion(mGameData.getCurrentWall(player));
			for (auto index = 0; index != wallRect.size(); ++index)
			{
				paintDC.FillRect(wallRect[index], & brush);// 画墙
			}
			
			brush.DeleteObject();
			paintDC.SelectObject(oldBrush);
		}

        if (isGameStart == true && isGameOver == false)
        {
            BYTE nAlpha = 127;
            // 透明度，在0～254之间取值，越大越不透明 
            BLENDFUNCTION stBlend = { AC_SRC_OVER, 0, nAlpha, 0 };

            CDC dcAlphaRect;
            CBitmap bmpAlphaRect;

            dcAlphaRect.CreateCompatibleDC(&paintDC);

            if (mPlayerNextWall.type != NONE)
            {
                CRect rect = mGameDisplay.getWallRegion(std::make_pair(mPlayerNextWall.point, mPlayerNextWall.type));// 提示玩家放墙的位置
                bmpAlphaRect.CreateCompatibleBitmap(&paintDC, rect.Width(), rect.Height());
                CBitmap* pOld_Bitmap = dcAlphaRect.SelectObject(&bmpAlphaRect);

                dcAlphaRect.FillSolidRect(0, 0, rect.Width(), rect.Height(), mColorPlayer);

                AlphaBlend(paintDC.m_hDC, rect.left, rect.top, rect.Width(), rect.Height(),
                    dcAlphaRect.m_hDC, 0, 0, rect.Width(), rect.Height(), stBlend);

                dcAlphaRect.SelectObject(pOld_Bitmap);
            }

            for (auto index = 0; index != mPlayerNextStep.size(); ++index)
            {
                CRect rect = mGameDisplay.getPlayerRegion(mPlayerNextStep.at(index));// 提示玩家下一步可以走的位置
                bmpAlphaRect.CreateCompatibleBitmap(&paintDC, rect.Width(), rect.Height());
                CBitmap* pOld_Bitmap = dcAlphaRect.SelectObject(&bmpAlphaRect);

                dcAlphaRect.BeginPath();
                dcAlphaRect.Ellipse(rect);
                dcAlphaRect.EndPath();

                AlphaBlend(paintDC.m_hDC, rect.left, rect.top, rect.Width(), rect.Height(),
                    dcAlphaRect.m_hDC, 0, 0, rect.Width(), rect.Height(), stBlend);

                dcAlphaRect.SelectObject(pOld_Bitmap);
            }
            dcAlphaRect.DeleteDC();
            bmpAlphaRect.DeleteObject();
        }

		ResumeThread(mGameHandle); // 绘画完成,恢复游戏进程
        isHandleWaittingPaint = false;
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQuoridorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Quoridor游戏的主循环函数，该函数与UI不在一个线程，由mGameHandle控制
DWORD WINAPI CQuoridorDlg::QuoridorGame(LPVOID pParameter)
{
	CQuoridorDlg* Quoridor = (CQuoridorDlg*)pParameter;
	CString str;
	Order order;
	while (1)
	{
        if (Quoridor->mGameData.isEnd() != -1) // 游戏是否接受
        {
            CString str;
            str.Format(_T("玩家%d获胜"), Quoridor->mGameData.isEnd());
            Quoridor->MessageBox(str);
            Quoridor->isGameOver = true;
            TerminateThread(Quoridor->mGameHandle, 0); // 若游戏结束,则退出进程
        }

		if (Quoridor->mAI[Quoridor->mTurn] != nullptr) // 该回合由AI控制
		{
			order = Quoridor->mAI[Quoridor->mTurn]->getNextMove(); // 由AI计算下一步
		}
		else // 否则该回合是由玩家控制
		{
            Quoridor->mColorPlayer = Quoridor->mColor[Quoridor->mTurn];
            Quoridor->mPlayerNextStep = Quoridor->mGameData.getMoveVaild(Quoridor->mTurn); // UI界面显示玩家下一步可以走的位置,提示玩家
			Quoridor->isHandleWaittingOperate = true;
			while (Quoridor->isHandleWaittingOperate);// 等待玩家点击界面，做出决策
			order = Quoridor->mOrder;
		}

		const int type = order.type;
		const int x = order.point.x;
		const int y = order.point.y;
		switch (type) // 执行指令
		{
		case MOVE:
			Quoridor->mGameData.gotoMove(Quoridor->mTurn, x, y);
			str.Format(_T("玩家%d 移动    至(%d, %d)\r\n"), Quoridor->mTurn, x, y);
			break;
		case WALLH:
			Quoridor->mGameData.gotoWall(Quoridor->mTurn, type, x, y);
			str.Format(_T("玩家%d 放横墙 至(%d, %d)\r\n"), Quoridor->mTurn, x, y);
			break;
		case WALLV:
			Quoridor->mGameData.gotoWall(Quoridor->mTurn, type, x, y);
			str.Format(_T("玩家%d 放竖墙 至(%d, %d)\r\n"), Quoridor->mTurn, x, y);
			break;
		default:
			break;
		}
		Quoridor->mText += str;
		Quoridor->GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(Quoridor->mText);

		Quoridor->updateInformationText();
		Quoridor->mTurn = (++Quoridor->mTurn) % PLAYER_NUM; // 表示下一个回合

        Quoridor->isHandleWaittingPaint = true;
		Quoridor->InvalidateRect(&Quoridor->mGameBoundary);
        if (Quoridor->isHandleWaittingPaint) SuspendThread(Quoridor->mGameHandle); // 暂停该线程等待UI界面重新绘制
	}
}

// 当在界面上按下鼠标时触发该函数
void CQuoridorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isGameStart == false || isGameOver == true) // 如果游戏正在进行中
		return;

	if (mAI[mTurn] != nullptr) // 如果这个回合是玩家的回合
		return;

	mOrder = mGameDisplay.getPositionToOrder(Point(point.x, point.y)); // 根据玩家鼠标点击的位置确定玩家的指令

    if (mOrder.type != NONE && mGameData.checkOrder(mTurn, mOrder)) // 检测该指令是否有效
    {
        mPlayerNextStep.clear();
        isHandleWaittingOperate = false; // 如果有效QuoridorGame函数不在死等，继续执行
    }
}

// 当在界面上移动鼠标时触发该函数
void CQuoridorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if (!(point.x >= mGameBoundary.left && point.x <= mGameBoundary.right && point.y >= mGameBoundary.top && point.y <= mGameBoundary.bottom))
        return;

    if (isGameStart == false || isGameOver == true) // 如果游戏正在进行中
        return;

    if (mAI[mTurn] != nullptr) // 如果这个回合是玩家的回合
        return;

    Order order = mGameDisplay.getPositionToOrder(Point(point.x, point.y));
    if ((order.type == WALLH || order.type == WALLV) && mGameData.checkOrder(mTurn, order)) mPlayerNextWall = order;
    else mPlayerNextWall = Order(); // 使UI界面显示放墙的位置,提示玩家

    InvalidateRect(&mGameBoundary);

	CDialogEx::OnMouseMove(nFlags, point);
}

// 点击重新开始按键触发该函数
void CQuoridorDlg::OnBnClickedButtonRegame()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON_REGAME)->SetWindowText(_T("重新开始"));
	
	if (mGameHandle != nullptr)
	{
		DWORD code;
		GetExitCodeThread(mGameHandle, &code);
		if (code == STILL_ACTIVE) TerminateThread(mGameHandle, 0);
	}

	mText = "游戏开始\r\n";

	mGameData.resetGame();
	updateInformationText();

    mPlayerNextStep.clear();
    mPlayerNextWall = Order();

	isGameOver = false;
	isGameStart = true;
	mTurn = mWhoFirst.GetCurSel();

	CString str;
	str.Format(_T("玩家%d 先手\r\n"), mTurn);
	mText += str;

	GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(mText);

	mGameHandle = CreateThread(NULL, 0, QuoridorGame, this, 0, NULL);
    InvalidateRect(&mGameBoundary);
}

// 点击悔棋按键触发该函数
void CQuoridorDlg::OnBnClickedButtonUndo()
{
	// TODO: 在此添加控件通知处理程序代码
    if (isGameStart == false || isGameOver == true) // 如果游戏正在进行中
        return;

	mText += _T("玩家悔棋\r\n");
    GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(mText);
	mGameData.undoGame();

    mPlayerNextStep = mGameData.getMoveVaild(mTurn);

	updateInformationText();

    InvalidateRect(&mGameBoundary);
}

void CQuoridorDlg::updateInformationText()
{
	CString str;
	for (int player = 0; player < PLAYER_NUM; ++player)
	{
		str.Format(_T(" X %d"), mGameData.getCurrentWallNum(player));
		GetDlgItem(IDC_STATIC_WALLNUM[player])->SetWindowText(str);
		str.Format(_T("最短路径：%d"), mGameData.getCurrentShortPath(player));
		GetDlgItem(IDC_STATIC_SHORTPATH[player])->SetWindowText(str);
	}
}

// UI界面退出时触发该函数
void CQuoridorDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mGameHandle != nullptr)
	{
		DWORD code;
		GetExitCodeThread(mGameHandle, &code);
		if (code == STILL_ACTIVE) TerminateThread(mGameHandle, 0);
	}

	CDialogEx::OnClose();
}
