// InsertDailog.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "InsertDailog.h"
#include "afxdialogex.h"
#include "ManageDataBase.h"

// InsertDailog 对话框

IMPLEMENT_DYNAMIC(InsertDailog, CDialogEx)

InsertDailog::InsertDailog(CWnd* pParent /*=NULL*/)
	: CDialogEx(InsertDailog::IDD, pParent)
	, m_szData(_T(""))
{

}

InsertDailog::~InsertDailog()
{
}

void InsertDailog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szData);
	DDV_MaxChars(pDX, m_szData, 32);
}


BEGIN_MESSAGE_MAP(InsertDailog, CDialogEx)
	ON_BN_CLICKED(IDOK, &InsertDailog::OnBnClickedOk)
END_MESSAGE_MAP()


// InsertDailog 消息处理程序


void InsertDailog::OnBnClickedOk()
{
	UpdateData(true);
	//GetDlgItem(IDC_EDIT1)->GetWindow；Text();
	CString str("Insert Data fail!");
	if (InsertData(m_szData.GetBuffer()))
		str = CString("Insert Data success!");
	
	MessageBox(str);
	CDialogEx::OnOK();
}

bool InsertDailog::InsertData(const char* szText)
{
	GroupBallNum data(szText);
	return ManageDataBase::Share()->InsertData(data);
}

bool InsertDailog::InsertData(const wchar_t* szText)
{
	GroupBallNum data(szText);
	return ManageDataBase::Share()->InsertData(data);
}
