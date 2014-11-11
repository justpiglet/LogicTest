
// FieldEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "FieldEditorDlg.h"
#include "afxdialogex.h"
#include "depend/cantools/jsoncpp/json/reader.h"
#include "Field/UserFieldManage.h"
#include "Field/GobalConfig.h"

#include "CreateUser.h"
#include "UserLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TCHAR g_FieldName[FieldColumn_Max][16] = { _T("NickName"), _T("Account"), _T("LoginPwd"), _T("PayPwd"), _T("OtherPwd"), _T("Relation"), _T("Describe") };
uint8 g_FieldLen[FieldColumn_Max] = { 100, 160, 130, 130, 130, 200, 200 };

// CFieldEditorDlg 对话框


CFieldEditorDlg::CFieldEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldEditorDlg::IDD, pParent), m_status(EOpSatus_NULL), m_curRow(-1)
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_fun[0][0] = &CFieldEditorDlg::Logoin;
	m_fun[0][1] = &CFieldEditorDlg::CreateNewUser;
	m_fun[0][2] = &CFieldEditorDlg::DoNothing;
	m_fun[0][3] = &CFieldEditorDlg::Setting;

	m_fun[1][0] = &CFieldEditorDlg::LogoinOut;
	m_fun[1][1] = &CFieldEditorDlg::CreateNewField;
	m_fun[1][2] = &CFieldEditorDlg::TrashBasket;
	m_fun[1][3] = &CFieldEditorDlg::SettingUpdate;

	m_butName[0][0] = _T("(&L)Logoin");
	m_butName[0][1] = _T("(&N)New");
	m_butName[0][2] = _T("");
	m_butName[0][3] = _T("(&S)Setting");

	m_butName[1][0] = _T("(&L)LogoinOut");
	m_butName[1][1] = _T("(&N)NewField");
	m_butName[1][2] = _T("(&T)Trash");
	m_butName[1][3] = _T("(&S)Setting");

	g_pMainDlgHandle = this;
}

void CFieldEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
}

BEGIN_MESSAGE_MAP(CFieldEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFieldEditorDlg::OnBnClickedOk)

	ON_NOTIFY(NM_RCLICK, IDC_LIST_INFO, &CFieldEditorDlg::OnNMRClickListInfo)
	ON_COMMAND(ID_FEILD_INFO_PEEP, &CFieldEditorDlg::OnMenuClickPeepFieldInfo)
	ON_COMMAND(ID_SINGLE_PEEP, &CFieldEditorDlg::OnMenuClickPeepPwd)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_INFO, &CFieldEditorDlg::OnNMDblclkListInfo)
END_MESSAGE_MAP()


// CFieldEditorDlg 消息处理程序

BOOL CFieldEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	UserFieldManage::Share()->InitData();
	UpdateButton();

	// TODO:  在此添加额外的初始化代码
	for (int i(0); i < FieldColumn_Max;++i)
		m_ListInfo.InsertColumn(i, g_FieldName[i], LVCFMT_LEFT, g_FieldLen[i], -1);
	
	//GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("(&L)Change"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFieldEditorDlg::OnPaint()
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
HCURSOR CFieldEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFieldEditorDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




void CFieldEditorDlg::OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult)
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
		if (pNMItemActivate->iSubItem >= FieldColumn_PwdLogin && pNMItemActivate->iSubItem <=FieldColumn_PwdLogin)
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

void CFieldEditorDlg::OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1)
	{

	}
	*pResult = 0;
}



void CFieldEditorDlg::OnMenuClickPeepFieldInfo()
{
	// TODO:  在此添加命令处理程序代码
	int a = 9;
	a = a;
}


void CFieldEditorDlg::OnMenuClickPeepPwd()
{
	// TODO:  在此添加命令处理程序代码
	int a = 9;
	a = a;
}

void CFieldEditorDlg::UpdateListControl()
{
	m_ListInfo.DeleteAllItems();
	const CField* pField=UserFieldManage::Share()->GetCurUserFields();
	if (!pField)
		return;

	uint16 iCount = pField->GetFieldRow();
	for (int iRow(0), iColumn(0); iRow < iCount; ++iRow)
	{
		if (pField->IsShowRow(iRow))
		{
			const void* pData = pField->GetItem(iRow);
			if (pData)
			{
				m_ListInfo.SetItemData(iRow, (DWORD)pData);
				for (iColumn = 0; iColumn < FieldColumn_Max; ++iColumn)
				{
					if (iColumn == 0)
						m_ListInfo.InsertItem(iRow, pField->GetFieldItemCS(iRow, iColumn,true));
					else
						m_ListInfo.SetItemText(iRow, iColumn, pField->GetFieldItemCS(iRow, iColumn, true));

				}
			}// end if (pData)

		}//end if if (UserFieldManage::Share()->IsShowRow(iRow))

	}
}

BOOL CFieldEditorDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (wParam >= IDC_BUTTON1 && wParam <= IDC_BUTTON4)
	{
		(this->*(m_fun[m_status][wParam - IDC_BUTTON1]))();
		return TRUE;
	}
	else
		return CDialogEx::OnCommand(wParam, lParam);
}

void CFieldEditorDlg::Logoin()
{
	CUserLogin dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.IsLogoinSuccess())
		{
			LoginSuccessUpdate(UserFieldManage::Share()->GetCurAccount()->strName);
		}
	}
}

void CFieldEditorDlg::DoNothing()
{

}

void CFieldEditorDlg::Setting()
{

}

void CFieldEditorDlg::LogoinOut()
{

}

void CFieldEditorDlg::CreateNewUser()
{
	CCreateUser dlg;
	if (dlg.DoModal() == IDOK)
	{
		std::string strName, strPwd;
		if (dlg.GetCreateUersInfo(strName, strPwd))
		{
			uint8 iRet = UserFieldManage::Share()->UserLogoin(strName.c_str(), strPwd.c_str());
			if (iRet == 0)
			{
				LoginSuccessUpdate(strName);
			}
			else
			{
				UpdateButton();
				MessageBox(_T("Account or Password Error!"));
			}	
		}
	}

}

void CFieldEditorDlg::CreateNewField()
{

}

void CFieldEditorDlg::TrashBasket()
{

}

void CFieldEditorDlg::SettingUpdate()
{

}

void CFieldEditorDlg::UpdateButton()
{
	for (uint8 i = 0; i < 4; ++i)
	{
		bool isShow(false);
		if (m_butName[m_status][i] != _T(""))
		{
			isShow = true;
			GetDlgItem(IDC_BUTTON1 + i)->SetWindowText(m_butName[m_status][i]);
		}
		
		//if (isShow != GetDlgItem(IDC_BUTTON1 + i)->IsWindowVisible())
		GetDlgItem(IDC_BUTTON1 + i)->ShowWindow(isShow?SW_SHOW:SW_HIDE);
	}

	if (m_status == EOpSatus_NULL)
	{
		bool isEnable(false);
		if (UserFieldManage::Share()->GetUserCount() > 0)
			isEnable = true;

		GetDlgItem(IDC_BUTTON1)->EnableWindow(isEnable);
	}
	else
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
}

void CFieldEditorDlg::MainDlgLogoin()
{

}

void CFieldEditorDlg::LoginSuccessUpdate(const std::string& strName)
{
	m_status = EOpSatus_Logoin;
	SetWindowTextA(m_hWnd, strName.c_str());
	UpdateButton();
}
