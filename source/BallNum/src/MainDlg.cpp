// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BallNum.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#define  ENTER_KEY _T("198821349")

// MainDlg �Ի���

IMPLEMENT_DYNAMIC(MainDlg, CDialogEx)

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(MainDlg::IDD, pParent)
{

}

MainDlg::~MainDlg()
{
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &MainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MainDlg ��Ϣ�������


void MainDlg::OnBnClickedOk()
{
	CString strText;
	GetDlgItemText(IDC_MIAN_TEXT, strText);
	if (strText == ENTER_KEY)
		CDialogEx::OnOK();
}

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
#ifdef DEBUG
	SetDlgItemText(IDC_MIAN_TEXT, ENTER_KEY);
#endif // DEBUG

	return TRUE;
}
