// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(const User_Set* puSet, CWnd* pParent /*=NULL*/)
: CDialogEx(CSetting::IDD, pParent), m_pUSet(puSet)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY_BTN, &CSetting::OnBnClickedApplyBtn)
END_MESSAGE_MAP()


// CSetting 消息处理程序


void CSetting::OnBnClickedApplyBtn()
{
	// TODO:  在此添加控件通知处理程序代码
}

BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strText(UserFieldManage::Share()->GetAccountName());
	strText.Append(_T("-Setting"));
	SetWindowText(strText);

	if (m_pUSet)
	{

	}

	return TRUE;
}

void CSetting::SetFieldCheckStatus(uint32 iVal)
{
	uint32 iBeginID(IDC_CHECK1), iEndID(IDC_CHECK6);
	uint32 index(0);
	CButton* pItem;
	for (uint32 iId(iBeginID); iId <= iEndID; ++iId)
	{
		pItem = (CButton*)GetDlgItem(iId);
		index = iId - iBeginID + 1;
		if ((1 << index)&iVal)
			pItem->SetCheck(FALSE);
		else
			pItem->SetCheck(TRUE);
	}
}

void CSetting::SetLevelCheckStatus(uint32 iVal)
{
	uint32 iBeginID(IDC_CHECK7), iEndID(IDC_CHECK10);
	uint32 index(0);
	CButton* pItem;
	for (uint32 iId(iBeginID); iId <= iEndID; ++iId)
	{
		pItem = (CButton*)GetDlgItem(iId);
		index = iId - iBeginID + 1;
		if ((1 << index)&iVal)
			pItem->SetCheck(TRUE);
		else
			pItem->SetCheck(FALSE);
	}
}
