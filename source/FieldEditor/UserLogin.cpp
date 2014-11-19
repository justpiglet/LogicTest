// UserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "UserLogin.h"
#include "afxdialogex.h"

#include "Depend/cantools/tools.h"
// CUserLogin 对话框

IMPLEMENT_DYNAMIC(CUserLogin, CDialogEx)

CUserLogin::CUserLogin(ELOGOIN_MODE mMode, STDSTR strAccoun/*t = STDSTR()*/, CWnd* pParent /*=NULL*/)
: CDialogEx(CUserLogin::IDD, pParent), m_iStatus(ER_ERROR), m_mode(mMode), m_strAccount(strAccoun)
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

	m_vecAccount.clear();

	if (m_mode == ELOGOIN_MODE_NOR)
	{
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
	}
	else
	{
		SetWindowText(_T("Verify"));

		if (UserFieldManage::Share()->VerifyAccount(m_strAccount))
		{
#ifdef _UNICODE
			wchar_t* pWchar = _CANNP_NAME::code::AsciiToUnicode(m_strAccount.c_str(), m_strAccount.length());
			m_AccountList.InsertString(0, pWchar);
			delete pWchar;
#else
			m_AccountList.InsertString(i, m_strAccount.c_str());
#endif

			m_AccountList.SetCurSel(0);
			m_vecAccount.push_back(m_strAccount);
		}
			
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
		CString cstrPwd;
		GetDlgItem(IDC_LOGOIN_PWD)->GetWindowText(cstrPwd);
#ifdef _UNICODE
		STDSTR strPwd = _CANNP_NAME::code::UnicodeToAscii(cstrPwd.GetBuffer(), cstrPwd.GetLength());
#else
		STDSTR strPwd = cstrPwd.GetBuffer();
#endif
		m_iStatus = UserFieldManage::Share()->UserLogoin(m_vecAccount[iSel].c_str(), strPwd.c_str(),m_mode);

		if (m_iStatus == ER_ERROR_ACCOUNT || m_iStatus == ER_ERROR)
			MessageBox(_T("Account Error!"));
		else if (m_iStatus == ER_ERROR_PWD)
			MessageBox(_T("Password Error!"));
	}

	CDialogEx::OnOK();
}
