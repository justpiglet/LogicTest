// CreateUser.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "CreateUser.h"
#include "afxdialogex.h"
#include "Depend/cantools/tools.h"
#include "Field/UserFieldManage.h"

// CCreateUser 对话框

IMPLEMENT_DYNAMIC(CCreateUser, CDialogEx)

CCreateUser::CCreateUser(CWnd* pParent /*=NULL*/)
: CDialogEx(CCreateUser::IDD, pParent), m_iCStatus(0)
{
	
}

CCreateUser::~CCreateUser()
{
}

void CCreateUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreateUser, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCreateUser::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CCreateUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_EDIT_CREATE_ACCOUNT))->SetLimitText(16);
	((CEdit*)GetDlgItem(IDC_EDIT_CREATE_PWD))->SetLimitText(32);
	((CEdit*)GetDlgItem(IDC_EDIT_CREATE_PWD2))->SetLimitText(32);

	return TRUE;
}


bool CCreateUser::IsTextLegal(const CString& strSrc)
{
	uint32 iLen = strSrc.GetLength();
	for (uint32 i = 0; i < iLen; ++i)
	{
		if (strSrc[i] < 0 || strSrc[i]>128)
			return false;
	}

	return true;
}

// CCreateUser 消息处理程序


void CCreateUser::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	m_iCStatus = ER_ERROR;
	CString strAccount,strPwd,strOPwd, strError;
	uint32 iTemp(0);
	GetDlgItem(IDC_EDIT_CREATE_ACCOUNT)->GetWindowText(strAccount);

	if (strAccount.IsEmpty())
		strError = _T("Account Can not empty ,inout again!");
	else if (!IsTextLegal(strAccount))
		strError = _T("There is have illegal characters!");
	else
	{
		GetDlgItem(IDC_EDIT_CREATE_PWD)->GetWindowText(strPwd);
		if (strPwd.IsEmpty())
			strError = _T("Password Can not empty ,inout again!");
		else if (!IsTextLegal(strPwd))
			strError = _T("There is have illegal characters!");
		else
		{
			CString strPwd2;
			GetDlgItem(IDC_EDIT_CREATE_PWD2)->GetWindowText(strPwd2);
			if (strPwd2.IsEmpty())
				strError = _T("Password Can not empty ,inout again!");
			else if (strPwd2 != strPwd)
				strError = _T("Password Twice input are different!");
			else
			{
				GetDlgItem(IDC_EDIT_CREATE_PWD3)->GetWindowText(strOPwd);
				if (strOPwd.IsEmpty())
					strError = _T("Operate Password Can not empty ,inout again!");
				else if (!IsTextLegal(strOPwd))
					strError = _T("Operate Password There is have illegal characters!");
				else
				{
					CString strPwd4;
					GetDlgItem(IDC_EDIT_CREATE_PWD4)->GetWindowText(strPwd4);
					if (strPwd4.IsEmpty())
						strError = _T("Operate Password Can not empty ,inout again!");
					else if (strPwd4 != strOPwd)
						strError = _T("Operate password Twice input are different!");
				}
			}


		}
	}

	if (strError.IsEmpty())
	{
		Exchange(strAccount, m_strAccount);
		Exchange(strPwd, m_strPwd);
		Exchange(strOPwd, m_strOPwd);
		if (UserFieldManage::Share()->CreateAccount(m_strAccount, m_strPwd,m_strOPwd)>0)
		{
			m_iCStatus = UserFieldManage::Share()->UserLogoin(m_strAccount.c_str(), m_strPwd.c_str());
			CDialogEx::OnOK();
		}
		else
		{
			m_strAccount = "";
			MessageBox(_T("Account already exsist!"));
		}
	}
	else
		MessageBox(strError);
}

bool CCreateUser::GetCreateUersInfo(std::string& strA, std::string& strP, std::string& strOP)
{
	if (m_strAccount.empty() || m_strPwd.empty())
		return false;

	strA=m_strAccount;
	strP = m_strPwd;
	strOP = m_strOPwd;
	return true;
}

void CCreateUser::Exchange(CString& strSrc, std::string& strDest)
{
#ifdef _UNICODE
	uint16 iLen(strSrc.GetLength());
	char * pszTemp = _CANNP_NAME::code::UnicodeToAscii(strSrc.GetBuffer(), iLen);
	strDest.append(pszTemp, iLen);
	delete pszTemp;
#else
	strDest.append(strSrc.GetBuffer(), strSrc.GetLength());
#endif // _UNICODE
}

