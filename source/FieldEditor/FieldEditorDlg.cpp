
// FieldEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "FieldEditorDlg.h"
#include "afxdialogex.h"
#include "depend/cantools/jsoncpp/json/reader.h"
#include "Depend/cantools/tools.h"

#include "Field/GobalConfig.h"
#include "Setting.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

TCHAR g_FieldName[FieldColumn_Max][16] = { _T("NickName"), _T("Account"), _T("LoginPwd"), _T("PayPwd"), _T("OtherPwd"), _T("Relation"), _T("Describe") };
uint8 g_FieldLen[FieldColumn_Max] = { 100, 160, 130, 130, 130, 200, 200 };

// CFieldEditorDlg 对话框

IMainDlgHandle* g_mainDlg=NULL;
CFieldEditorDlg::CFieldEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFieldEditorDlg::IDD, pParent), m_status(EOpSatus_NULL), m_curRow(-1), m_pCurField(NULL)
{
	AfxInitRichEdit2();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_fun[0][0] = &CFieldEditorDlg::Logoin;
	m_fun[0][1] = &CFieldEditorDlg::CreateNewUser;
	m_fun[0][2] = &CFieldEditorDlg::DoNothing;
	m_fun[0][3] = &CFieldEditorDlg::DoNothing;

	m_fun[1][0] = &CFieldEditorDlg::LogoinOut;
	m_fun[1][1] = &CFieldEditorDlg::CreateNewField;
	m_fun[1][2] = &CFieldEditorDlg::DeleteAccount;
	m_fun[1][3] = &CFieldEditorDlg::SettingUpdate;

	m_butName[0][0] = _T("(&L)Login");
	m_butName[0][1] = _T("(&N)New");
	m_butName[0][2] = _T("");
	m_butName[0][3] = _T("");

	m_butName[1][0] = _T("(&L)LogoinOut");
	m_butName[1][1] = _T("(&N)NewField");
	m_butName[1][2] = _T("(&D)Delete User");
	m_butName[1][3] = _T("(&S)Setting");

	g_mainDlg = this;
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

void TestWriteEncry()
{
	std::ofstream wFile("Dont_Delete/test.json", std::ios::binary | std::ios::out | std::ios::trunc);
	std::string strEnPwd(""), strValue("");
	CGobalConfig::Share()->CreateRandStr(78, strEnPwd);
	_CANNP_NAME::encrypt::EncryptBuffer(strEnPwd.c_str(), strEnPwd.length(), strEnPwd.c_str(), strValue);
	int iLen(strEnPwd.length() + strValue.length());
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strEnPwd.c_str(), strEnPwd.length());
	wFile.write(strValue.c_str(), strValue.length());
	wFile.close();

}

bool TestReadEncry()
{
	std::ifstream rFile("Dont_Delete/test.json", std::ios::binary | std::ios::in );
	if (!rFile)
		return false;

	char szBuffer[512] = "";
	int iLen(0);
	rFile.read((char*)&iLen, sizeof(iLen));
	rFile.read(szBuffer, iLen);
	 
	std::string strEnPwd(""), strValue(""),strDeValue("");
	strEnPwd.append(szBuffer, 78);
	strValue.append(szBuffer + 78, iLen - 78);
	_CANNP_NAME::encrypt::DecryptBuffer(strValue.c_str(), 78, strEnPwd.c_str(), strDeValue);
	if (strDeValue.compare(strEnPwd) == 0)
	{
		printf("ok");
		return true;
	}
	return false;
}

BOOL CFieldEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//while (!TestReadEncry())
		//TestWriteEncry();


	SetWindowText(_T("Please Login"));
	UserFieldManage::Share()->InitData();
	UpdateButton();

	// TODO:  在此添加额外的初始化代码
	for (int i(0); i < FieldColumn_Max;++i)
		m_ListInfo.InsertColumn(i, g_FieldName[i], LVCFMT_LEFT, g_FieldLen[i]);
	m_ListInfo.EnableWindow(false);

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
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

uint32 CFieldEditorDlg::GetClickRow(CPoint point)
{
	m_ListInfo.ScreenToClient(&point);

	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	return  m_ListInfo.SubItemHitTest(&lvinfo);
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

		m_curRow = GetClickRow(points);

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_USER_INFO));
		CMenu* popup = menu.GetSubMenu(isAll ? 1 : 0);
		if (popup)
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, points.x, points.y, this);
	}
	else
		m_curRow = -1;

	*pResult = 0;
}

void CFieldEditorDlg::OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem != -1 || pNMItemActivate->iSubItem > 0)
	{
		DWORD dwpos = GetMessagePos();
		CPoint points(LOWORD(dwpos), HIWORD(dwpos));

		m_curRow = GetClickRow(points);
		OnMenuClickPeepFieldInfo();
	}
	else
		m_curRow = -1;
	*pResult = 0;
}

void CFieldEditorDlg::OpenFieldInfoDlg(EDlg_Mode mMode, uint32 iRow)
{
	CUserLogin lDlg(ELOGOIN_MODE_OPERATE, UserFieldManage::Share()->GetAccountName());
	if (lDlg.DoModal() == IDOK)
	{
		if (lDlg.IsLogoinSuccess() == true)
		{
			const FIELD_ITEM* pItem = NULL;
			CCreateNewField dlg(mMode);
			if (mMode == EDlg_Mode_Read)
				pItem = GetCurFieldItem();
			dlg.SetDataInfo(iRow, pItem);
			dlg.DoModal();
		}
	}
}

void CFieldEditorDlg::OnMenuClickPeepFieldInfo()
{
	// TODO:  在此添加命令处理程序代码
	OpenFieldInfoDlg(EDlg_Mode_Read, m_curRow);
	m_curRow = -1;
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
	if (!m_pCurField)
		return;

	uint16 iCount = m_pCurField->GetFieldRow();
	for (int iRow(0), iColumn(0), index(0); index < iCount; ++index)
	{
		if (UpdateListControlOneRow(iRow, m_pCurField->GetItem(index)))
			++iRow;
	}
}

bool CFieldEditorDlg::UpdateListControlOneRow(uint32 iRow, const FIELD_ITEM* pData)
{
	uint32 iListCount = m_ListInfo.GetItemCount();
	if (!m_pCurField || !pData || iRow>iListCount || !m_pCurField->IsShowRow(pData))
		return false;
	
	for (uint32 iColumn = 0; iColumn < FieldColumn_Max; ++iColumn)
	{
		if (iColumn == 0)
		{
			if (iRow == iListCount)
				m_ListInfo.InsertItem(iRow, CString(m_pCurField->GetFieldHideParts((FIELD_ITEM*)pData, iColumn, true).c_str()));
		}
		else
			m_ListInfo.SetItemText(iRow, iColumn, CString(m_pCurField->GetFieldHideParts((FIELD_ITEM*)pData, iColumn, true).c_str()));
	}

	m_ListInfo.SetItemData(iRow, (DWORD_PTR)pData);

	return true;
}

bool CFieldEditorDlg::DeleteListControlOneRow(uint32 iRow)
{
	uint32 iListCount = m_ListInfo.GetItemCount();
	if (!m_pCurField || iRow > iListCount )
		return false;

	m_ListInfo.DeleteItem(iRow);
	return true;
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
	CUserLogin dlg(ELOGOIN_MODE_NOR);
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
	UserFieldManage::Share()->UserLoginOut();
	m_ListInfo.DeleteAllItems();
	m_status = EOpSatus_NULL;
	UpdateButton();
	SetWindowText(_T("Please Login"));
}

void CFieldEditorDlg::CreateNewUser()
{
	CCreateUser dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.GetLogoinStatus() == ER_SUCCESS)
			LoginSuccessUpdate(dlg.GetLogoinName());
		else
			UpdateButton();
	}
}

void CFieldEditorDlg::CreateNewField()
{
	OpenFieldInfoDlg(EDlg_Mode_New, m_ListInfo.GetItemCount());
}

void CFieldEditorDlg::DeleteAccount()
{

}

void CFieldEditorDlg::SettingUpdate()
{
	CUserLogin lDlg(ELOGOIN_MODE_OPERATE, UserFieldManage::Share()->GetAccountName());
	if (lDlg.DoModal() == IDOK)
	{
		if (lDlg.IsLogoinSuccess() == true)
		{
			CSetting sDlg;
			if (sDlg.DoModal() == IDOK)
			{

			}
		}
	}
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

	uint32 ifoucsId = IDC_BUTTON2;
	if (m_status == EOpSatus_NULL)
	{
		bool isEnable(false);
		if (UserFieldManage::Share()->GetUserCount() > 0)
			isEnable = true;

		GetDlgItem(IDC_BUTTON1)->EnableWindow(isEnable);
		if (isEnable)
			ifoucsId = IDC_BUTTON1;
	}
	else
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);

	GetDlgItem(ifoucsId)->SetFocus();
}

void CFieldEditorDlg::MainDlgLogoin()
{

}

void CFieldEditorDlg::LoginSuccessUpdate(const std::string& strName)
{
	m_pCurField = UserFieldManage::Share()->GetCurUserFields();
	m_status = EOpSatus_Logoin;
	SetWindowTextA(m_hWnd, strName.c_str());
	UpdateButton();
	m_ListInfo.EnableWindow(true);
	UpdateListControl();
}

const FIELD_ITEM* CFieldEditorDlg::GetCurFieldItem()
{
	const FIELD_ITEM* pData = NULL;
	if (m_curRow < m_ListInfo.GetItemCount())
	{

		pData = (FIELD_ITEM*)m_ListInfo.GetItemData(m_curRow);
	}

	return pData;
}
