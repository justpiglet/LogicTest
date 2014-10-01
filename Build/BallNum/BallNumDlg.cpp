
// BallNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "BallNumDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include "ManageDataBase.h"
#include "Analysis/BaseAnalysis.h"
#include<io.h>
#include<stdio.h>
#include "YearSetDlg.h"
#include "functionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBallNumDlg 对话框



CBallNumDlg::CBallNumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBallNumDlg::IDD, pParent)
	, m_cstrText(_T("")), m_operateTyped(Operate_NULL)
{
	m_pFunctionDlg = NULL;
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CBallNumDlg::~CBallNumDlg()
{
	if (m_pFunctionDlg)
		delete m_pFunctionDlg;
}

void CBallNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_MGS, m_reShowMessage);
	DDX_Text(pDX, IDC_EDIT1, m_cstrText);
}

BEGIN_MESSAGE_MAP(CBallNumDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_I, &CBallNumDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_CLEAN_MSG, &CBallNumDlg::OnBnClickedCleanMsg)
	ON_BN_CLICKED(IDC_BTN_Q, &CBallNumDlg::OnBnClickedBtnQ)
	ON_BN_CLICKED(IDC_BTN_D, &CBallNumDlg::OnBnClickedBtnD)
	ON_BN_CLICKED(IDC_BTN_M, &CBallNumDlg::OnBnClickedBtnM)
	ON_BN_CLICKED(IDC_COMFIRM, &CBallNumDlg::OnBnClickedComfirm)
	ON_BN_CLICKED(IDC_BALL_OPREATE, &CBallNumDlg::OnBnClickedBallOpreate)
END_MESSAGE_MAP()


// CBallNumDlg 消息处理程序

BOOL CBallNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码

// 	PARAFORMAT2 pf2;
// 	pf2.cbSize = sizeof(PARAFORMAT2);
// 	pf2.dwMask = PFM_LINESPACING | PFM_SPACEAFTER;
// 	pf2.dyLineSpacing = 23;
// 	pf2.bLineSpacingRule = 4;
// 	m_reShowMessage.SetParaFormat(pf2);

	ManageDataBase::Share()->InitDataBase();
	ShowMainMessage::share()->Init(this);

	GroupBallNum mNumData;
	ManageDataBase::Share()->GetNearDataByIndex(1, mNumData);
	std::string text("current\n");
	text.append(mNumData.toStdstring());
	InsertMsg(text);
	InsertMsg(ManageDataBase::Share()->GetMissData());
	
// 	m_reShowMessage.LineScroll(2);
// 	m_reShowMessage.SetSel(-1, -1);
// 	CString text("current\n");
// 	text.Append(aa.toCString());
// 	text.Append(_T("\n"));
// 	m_reShowMessage.ReplaceSel(text);
	//m_reShowMessage.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	
// 	m_pMainDlg = new MainDlg;
// 	m_pMainDlg->SetRelationWnd(this);
// 	m_pMainDlg->Create(IDD_MAIN_DLG, NULL);
// 	m_pMainDlg->ShowWindow(SW_SHOW);

	ChangeDlg(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBallNumDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBallNumDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBallNumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CBallNumDlg::CalculateIdByTime()
{
	time_t nowtime = time(NULL);
	tm timeData;
	localtime_s(&timeData, &nowtime);
	tm timeModify = timeData;
	timeModify.tm_mon = 0;
	timeModify.tm_mday = 1;
	
	time_t modifyTime = mktime(&timeModify);
	tm TimeNew;
	localtime_s(&TimeNew, &modifyTime);
	return 0;
}

void CBallNumDlg::OnBnClickedBtnQ()
{
	m_operateTyped == Operate_Q;
	ChangeDlg(true);
}

void CBallNumDlg::OnBnClickedInsert()
{
	m_operateTyped = Operate_I;
	ChangeDlg(true);
}


void CBallNumDlg::OnBnClickedBtnD()
{
	m_operateTyped = Operate_D;
	ChangeDlg(true);
}

void CBallNumDlg::OnBnClickedBtnM()
{
	m_operateTyped = Operate_M;
	ChangeDlg(true);
}

void CBallNumDlg::OnBnClickedCleanMsg()
{
	// TODO:  在此添加控件通知处理程序代码
	CleanUpMsg();
}

void CBallNumDlg::InsertMsg(const std::string& text)
{
	CString cstrText(text.c_str());
	cstrText.Append(_T("\n"));
	m_reShowMessage.SetSel(-1, -1);
	m_reShowMessage.ReplaceSel(cstrText);
	m_reShowMessage.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void CBallNumDlg::CleanUpMsg()
{
	m_reShowMessage.SetSel(0, -1);
	m_reShowMessage.Clear();
	m_reShowMessage.SetWindowTextW(_T(""));
	//m_reShowMessage.UpdateData(true);
}

void CBallNumDlg::QueryData(uint32 id)
{
	GroupBallNum mData;
	ManageDataBase::Share()->QueryDatas(id, mData);
	std::string strMsg("Query:\n");
	strMsg.append(mData.toStdstring());
	InsertMsg(strMsg);
}

void CBallNumDlg::OnBnClickedComfirm()
{
	ChangeDlg(false);

	UpdateData(true);
	std::string strMsg("Insert Failed.");
	if (m_cstrText.IsEmpty())
		return;
	GroupBallNum data;
	uint32 id(0);
	switch (m_operateTyped)
	{
	case Operate_D:
	{
		CString mes;
		mes.Format(_T("Are you sure delete data[%d])"), id);
		if (MessageBox(mes) != IDOK)
			return;
	}
	case Operate_Q:
	{
#ifdef UNICODE
		id = _wtoi(m_cstrText.GetBuffer());
#else
		id = atoi(m_cstrText.GetBuffer());
#endif // UNICODE
		break;
	}
	case Operate_I:
	case Operate_M:
	{
		data.Parsing(m_cstrText.GetBuffer());
		break;
	}
	}
	

	switch (m_operateTyped)
	{
	case Operate_Q:
	{
		QueryData(id);
		break;
	}
	case Operate_I:
	{
		if (ManageDataBase::Share()->InsertData(data))
		{
			strMsg = "Insert success.\n";
			strMsg.append(data.toStdstring());
			strMsg.append("\n");
			strMsg.append(ManageDataBase::Share()->GetMissData());
		}
		else
		{
			strMsg.append("\n");
			strMsg.append(ManageDataBase::Share()->GetLastError());
		}
		break;
	}
	case Operate_D:
	{
		if (!ManageDataBase::Share()->DeleteData(id))
		{
			strMsg.append("Delete Failed : \n");
			strMsg.append(ManageDataBase::Share()->GetLastError());
		}
		else
		{
			char szText[128] = "";
			sprintf_s(szText, sizeof(szText), "Delete success.[%d]", id);
			strMsg.append(szText);
		}
		break;
	}
	case Operate_M:
		break;
	default:
		break;
	}
	

	m_cstrText = "";
	UpdateData(FALSE);
	InsertMsg(strMsg);
}


void CBallNumDlg::OnBnClickedBallOpreate()
{
	OpenAnalysisDlg();
	// TODO:  在此添加控件通知处理程序代码
}


void CBallNumDlg::InsertNumMgs(const char* szTitle, uint32 src[], uint8 len)
{
	std::string strMgs;
	if (szTitle)
	{
		strMgs.append(szTitle);
		strMgs.append("\n");
	}
	
	char szTemp[32] = "";
	for (uint8 i = 1; i <= len; ++i)
	{
		sprintf_s(szTemp, sizeof(szTemp), "%003d ", src[i-1]);
		strMgs.append(szTemp);
		if (i % 4 == 0)
		{
			if (i % 16 == 0)
				strMgs.append("\n");
			else
				strMgs.append("  ");
		}
			
	}

	InsertMsg(strMgs);
}

void CBallNumDlg::OpenAnalysisDlg()
{
	if (!m_pFunctionDlg)
	{
		YearSetDlg yearSet;
		if (yearSet.DoModal() != IDOK)
			return;

		m_pFunctionDlg = new functionDlg;
		YearInfo mInfo = yearSet.GetYearIfo();
		m_pFunctionDlg->SetYearInfo(mInfo);
		m_pFunctionDlg->Create(IDD_FUNCTION_DLG, NULL);
		m_pFunctionDlg->UpdateTitle();
	}
	CRect rc;
	GetWindowRect(&rc);
	//ClientToScreen(rc);

	CRect dlgRc;
	m_pFunctionDlg->GetWindowRect(&dlgRc);
	m_pFunctionDlg->SetWindowPos(this, rc.right + 10, rc.top, dlgRc.Width(), dlgRc.Height(), SWP_SHOWWINDOW);
	m_pFunctionDlg->ShowWindow(SW_SHOW);
}

BOOL CBallNumDlg::PreTranslateMessage(MSG* pMsg)
{
	if (VK_LBUTTON == pMsg->wParam)
	{
		int a = 3;
		a = a;
	}
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP)
	{
		int aa = pMsg->wParam;
		TRACE("key value 0x%02x\n",aa);
		int laa = pMsg->lParam;
		laa = laa;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CBallNumDlg::ChangeDlg(bool isOpreate)
{
	CSize msgRc(480, 270);
	CSize exSize(8,34);
	uint32 uFlg = SW_HIDE;
	if (isOpreate)
	{
		exSize.cy += 60;
		uFlg = SW_SHOW;
	}
		
	CRect srcRc;
	GetWindowRect(srcRc);

	uint32 dlgFlg = SWP_NOZORDER;
	if (srcRc.left == 0 && srcRc.top == 0)
	{
		int nWidth = GetSystemMetrics(SM_CXSCREEN);  //屏幕宽度    
		int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
		srcRc.left = (nWidth - msgRc.cx - exSize.cx) / 2;
		srcRc.top = (nHeight - msgRc.cy - exSize.cy) / 2;
	}
	else
		dlgFlg = dlgFlg | SWP_NOMOVE;
	srcRc.right = srcRc.left + msgRc.cx + exSize.cx;
	srcRc.bottom = srcRc.top + msgRc.cy + exSize.cy;
	SetWindowPos(NULL, srcRc.left, srcRc.top, srcRc.Width(), srcRc.Height(), dlgFlg);

	m_reShowMessage.SetWindowPos(NULL, 0, 0, msgRc.cx, msgRc.cy, SWP_NOZORDER | SWP_NOMOVE);
	
	GetDlgItem(IDC_STATIC_OPRETAE)->ShowWindow(uFlg);
	GetDlgItem(IDC_EDIT_OPREATE)->ShowWindow(uFlg);
	GetDlgItem(IDC_COMFIRM)->ShowWindow(uFlg);

	//this->SetFocus();
}