// UserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "UserLogin.h"
#include "afxdialogex.h"

#include "Depend/cantools/tools.h"
// CUserLogin 对话框

IMPLEMENT_DYNAMIC(CUserLogin, CDialogEx)

CUserLogin::CUserLogin(CWnd* pParent /*=NULL*/)
: CDialogEx(CUserLogin::IDD, pParent), m_iStatus(0)
{

}

CUserLogin::~CUserLogin()
{
}

void CUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGOIN_ACCOUNTS, m_AccountList);
}


BEGIN_MESSAGE_MAP(CUserLogin, CDialogEx)
	ON_BN_CLICKED(IDC_LOGOIN_BT, &CUserLogin::OnBnClickedLogoinBt)
END_MESSAGE_MAP()

BOOL CUserLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	uint32 iCount = UserFieldManage::Share()->GetUserCount(m_vecAccount);
	if (iCount > 0)
	{
		
#ifdef _UNICODE
		for (int i = 0; i < iCount; ++i)
		{
			wchar_t* pWchar = _CANNP_NAME::code::AsciiToUnicode(m_vecAccount[i].c_str(), m_vecAccount[i].length());
			m_AccountList.InsertString(i, pWchar);
			delete pWchar;
		}
#else
		for (int i = 0; i < iCount; ++i)
		{
			m_AccountList.InsertString(i, vecOut[i].c_str());
		}
#endif
		
		m_AccountList.SetCurSel(0);
	}

	return TRUE;
}


// CUserLogin 消息处理程序


void CUserLogin::OnBnClickedLogoinBt()
{
	uint32 iSel=m_AccountList.GetCurSel();
	if (iSel == -1)
		MessageBox(_T("Please Select Account!"));
	else
	{
		CString strPwd;
		GetDlgItem(IDC_LOGOIN_PWD)->GetWindowText(strPwd);

		char* pAscii = _CANNP_NAME::code::UnicodeToAscii(strPwd.GetBuffer(), strPwd.GetLength());
		m_iStatus = UserFieldManage::Share()->UserLogoin(m_vecAccount[iSel].c_str(), pAscii);
		delete pAscii;
		if (m_iStatus == 1)
			MessageBox(_T("Account Error!"));
		else if (m_iStatus == 2)
			MessageBox(_T("Password Error!"));
	}

	CDialogEx::OnOK();
}
