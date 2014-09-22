
// BallNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "BallNumDlg.h"
#include "afxdialogex.h"
#include <time.h>
#include "ManageDataBase.h"
#include<io.h>
#include<stdio.h>


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
	, m_cstrText(_T(""))
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	ON_BN_CLICKED(IDOK, &CBallNumDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_I, &CBallNumDlg::OnBnClickedInsert)
	ON_EN_CHANGE(IDC_RICHEDIT_MGS, &CBallNumDlg::OnEnChangeRicheditMgs)
	ON_BN_CLICKED(IDC_CLEAN_MSG, &CBallNumDlg::OnBnClickedCleanMsg)
	ON_BN_CLICKED(IDC_BTN_Q, &CBallNumDlg::OnBnClickedBtnQ)
	ON_BN_CLICKED(IDC_BTN_D, &CBallNumDlg::OnBnClickedBtnD)
	ON_BN_CLICKED(IDC_BTN_M, &CBallNumDlg::OnBnClickedBtnM)
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

	PARAFORMAT2 pf2;
	pf2.cbSize = sizeof(PARAFORMAT2);
	pf2.dwMask = PFM_LINESPACING | PFM_SPACEAFTER;
	pf2.dyLineSpacing = 230;
	pf2.bLineSpacingRule = 4;
	m_reShowMessage.SetParaFormat(pf2);

	ManageDataBase::Share()->InitDataBase(this);
	GroupBallNum mNumData = ManageDataBase::Share()->GetNearDataByIndex(1);
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

void CBallNumDlg::OnBnClickedOk()
{

	CDialogEx::OnOK();
}


void CBallNumDlg::OnBnClickedInsert()
{
	UpdateData(true);
	std::string strMsg("Insert Failed.");
	if (m_cstrText.IsEmpty())
		return;

	GroupBallNum data;
	data.Parsing(m_cstrText.GetBuffer());
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

	m_cstrText = "";
	UpdateData(FALSE);
	
	InsertMsg(strMsg);
}


void CBallNumDlg::OnEnChangeRicheditMgs()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
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
	GroupBallNum mData=ManageDataBase::Share()->QueryDatas(id);
	std::string strMsg("Query:\n");
	strMsg.append(mData.toStdstring());
	InsertMsg(strMsg);
}

void CBallNumDlg::OnBnClickedBtnQ()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_cstrText.IsEmpty())
		return;
	uint32 id(0);
#ifdef UNICODE
	id = _wtoi(m_cstrText.GetBuffer());
#else
	id = atoi(m_cstrText.GetBuffer());
#endif // UNICODE

	QueryData(id);
	m_cstrText = "";
	UpdateData(FALSE);
}


void CBallNumDlg::OnBnClickedBtnD()
{
	UpdateData(true);
	if (m_cstrText.IsEmpty())
		return;

	uint32 id(0);
#ifdef UNICODE
	id = _wtoi(m_cstrText.GetBuffer());
#else
	id = atoi(m_cstrText.GetBuffer());
#endif // UNICODE

	CString mes;
	mes.Format(_T("Are you sure delete data[%d])"), id);
	if (MessageBox(mes) != IDOK)
		return;

	std::string strMsg;
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

	m_cstrText = "";
	UpdateData(FALSE);

	InsertMsg(strMsg);
	InsertMsg(ManageDataBase::Share()->GetMissData());
}


void CBallNumDlg::OnBnClickedBtnM()
{
	ManageDataBase::Share()->CalculateNumCount();
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
	for (uint8 i = 0; i < len; ++i)
	{
		//memset(szTemp, 0, sizeof(szTemp));
		sprintf_s(szTemp, sizeof(szTemp), "%d:%d\n", i + 1, src[i]);
		strMgs.append(szTemp);
	}

	InsertMsg(strMgs);
}

// bool CBallNumDlg::InsertData(const char* szText)
// {
// 	GroupBallNum data;
// 	data.Parsing(szText);
// 	return ManageDataBase::Share()->InsertData(data);
// }
// 
// bool CBallNumDlg::InsertData(const wchar_t* szText)
// {
// 	GroupBallNum data;
// 	data.Parsing(szText);
// 	return ManageDataBase::Share()->InsertData(data);
// }


