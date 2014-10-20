
// FeildEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FeildEditor.h"
#include "FeildEditorDlg.h"
#include "afxdialogex.h"
#include"cantools/jsoncpp/json/reader.h"
#include "Feild/UserFeildManage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeildEditorDlg 对话框



CFeildEditorDlg::CFeildEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFeildEditorDlg::IDD, pParent)
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFeildEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
}

BEGIN_MESSAGE_MAP(CFeildEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFeildEditorDlg::OnBnClickedOk)

	ON_NOTIFY(NM_RCLICK, IDC_LIST_INFO, &CFeildEditorDlg::OnNMRClickListInfo)
	ON_COMMAND(ID_FEILD_INFO_PEEP, &CFeildEditorDlg::OnMenuClickPeepFeildInfo)
	ON_COMMAND(ID_SINGLE_PEEP, &CFeildEditorDlg::OnMenuClickPeepPwd)
	ON_BN_CLICKED(IDC_BUTTON2, &CFeildEditorDlg::OnBnClickedLogoin)
	ON_BN_CLICKED(IDC_BUTTON3, &CFeildEditorDlg::OnBnClickedInsertInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CFeildEditorDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BUTTON1, &CFeildEditorDlg::OnBnClickedCreateUser)
END_MESSAGE_MAP()


// CFeildEditorDlg 消息处理程序

BOOL CFeildEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	for (int i(0); i < FeildColumn_Max;++i)
		m_ListInfo.InsertColumn(i, g_FeildName[i], LVCFMT_LEFT, g_FeildLen[i], -1);
	UpdateListControl();

	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("(&L)Change"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFeildEditorDlg::OnPaint()
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
HCURSOR CFeildEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFeildEditorDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




void CFeildEditorDlg::OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	bool isAll(true),isShow(false);
	if (pNMItemActivate->iItem != -1)
	{
		isShow = true;
	}
	else
	{
		if (pNMItemActivate->iSubItem >= FeildColumn_PwdLogin && pNMItemActivate->iSubItem <=FeildColumn_PwdLogin)
		{
			isShow = true;
			isAll = false;
		}
	}
		

	if (isShow)
	{
			DWORD dwpos = GetMessagePos();
			CPoint points(LOWORD(dwpos), HIWORD(dwpos));
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_USER_INFO));
			CMenu* popup = menu.GetSubMenu(isAll?1:0);
			if (popup)
				popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, points.x, points.y, this);
	}

	*pResult = 0;



}


void CFeildEditorDlg::OnMenuClickPeepFeildInfo()
{
	// TODO:  在此添加命令处理程序代码
	int a = 9;
	a = a;
}


void CFeildEditorDlg::OnMenuClickPeepPwd()
{
	// TODO:  在此添加命令处理程序代码
	int a = 9;
	a = a;
}

void CFeildEditorDlg::UpdateListControl()
{
	m_ListInfo.DeleteAllItems();
	uint16 iCount = UserFeildManage::Share()->GetFeildRow();
	for (int iRow(0), iColumn(0); iRow < iCount; ++iRow)
	{
		if (UserFeildManage::Share()->IsShowRow(iRow))
		{
			const void* pData = UserFeildManage::Share()->GetItem(iRow);
			if (pData)
			{
				m_ListInfo.SetItemData(iRow, (DWORD)pData);
				for (iColumn = 0; iColumn < FeildColumn_Max; ++iColumn)
				{
					if (iColumn == 0)
						m_ListInfo.InsertItem(iRow, UserFeildManage::Share()->GetFeildItemCS(iRow, iColumn));
					else
						m_ListInfo.SetItemText(iRow, iColumn, UserFeildManage::Share()->GetFeildItemCS(iRow, iColumn));

				}
			}// end if (pData)

		}//end if if (UserFeildManage::Share()->IsShowRow(iRow))

	}
}


void CFeildEditorDlg::OnBnClickedLogoin()
{
	// TODO:  在此添加控件通知处理程序代码
	
}


void CFeildEditorDlg::OnBnClickedInsertInfo()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CFeildEditorDlg::OnBnClickedSetting()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CFeildEditorDlg::OnBnClickedCreateUser()
{
	// TODO:  在此添加控件通知处理程序代码
}
