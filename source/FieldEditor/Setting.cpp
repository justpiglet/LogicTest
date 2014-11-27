// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "FieldEditorDlg.h"

#define TIME_COUNT 5
uint32 g_iShowTime[TIME_COUNT] = { 2, 5, 10, 15, 30 };
CString g_strTime[TIME_COUNT] = { _T("2 s"), _T("5 s"), _T("10 s"), _T("15 s"), _T("30 s") };
// CSetting 对话框

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting( CWnd* pParent /*=NULL*/)
: CDialogEx(CSetting::IDD, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_TIME_LIST, m_TimeList);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
	ON_BN_CLICKED(IDC_APPLY_BTN, &CSetting::OnBnClickedApplyBtn)
END_MESSAGE_MAP()


// CSetting 消息处理程序


void CSetting::OnBnClickedApplyBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	const User_Set* pUSet = UserFieldManage::Share()->GetCurUserFields()->GetUserSetInfo();
	if (!pUSet)
		return;

	uint32 iHideVal = GetFieldCheckStatus();
	uint32 iLevelVal = GetLevelCheckStatus();
	
	uint32 index = m_TimeList.GetCurSel();
	if (index > m_TimeList.GetCount())
		index = 1;

	if (iHideVal != pUSet->iHideParts || iLevelVal != pUSet->iShowLevel || g_iShowTime[index] != pUSet->iShowItemTime)
	{
		UserFieldManage::Share()->SetUserSettingInfo(iHideVal, iLevelVal, g_iShowTime[index]);
		g_mainDlg->UpdateListControl();
	}
		
}

BOOL CSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strText(UserFieldManage::Share()->GetAccountName());
	strText.Append(_T("-Setting"));
	SetWindowText(strText);

	for (uint32 i(0); i < TIME_COUNT; ++i)
		m_TimeList.InsertString(i, g_strTime[i]);
	const User_Set* pUSet = UserFieldManage::Share()->GetCurUserFields()->GetUserSetInfo();
	if (pUSet)
	{
		SetFieldCheckStatus(pUSet->iHideParts);
		SetLevelCheckStatus(pUSet->iShowLevel);

		char szVal[10] = "";
		const char* pp = szVal;
		uint32 iLen(0);

		for (uint32 i(0); i < TIME_COUNT; ++i)
		{
			if (g_iShowTime[i] >= pUSet->iShowItemTime)
			{
				m_TimeList.SetCurSel(i);
				break;
			}
		}

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
		index = iId - iBeginID;
		if ((1 << index)&iVal)
			pItem->SetCheck(TRUE);
		else
			pItem->SetCheck(FALSE);
	}
}

uint32 CSetting::GetFieldCheckStatus()
{
	uint32 iBeginID(IDC_CHECK1), iEndID(IDC_CHECK6);
	uint32 index(0);
	CButton* pItem;
	uint32 iVal(0);
	for (uint32 iId(iBeginID); iId <= iEndID; ++iId)
	{
		index = iId - iBeginID + 1;
		pItem = (CButton*)GetDlgItem(iId);
		if (pItem->GetCheck() == FALSE )
			iVal = iVal | (1 << index);
	}

	return iVal;
}

uint32 CSetting::GetLevelCheckStatus()
{
	uint32 iBeginID(IDC_CHECK7), iEndID(IDC_CHECK10);
	uint32 index(0);
	CButton* pItem;
	uint32 iVal(0);
	for (uint32 iId(iBeginID); iId <= iEndID; ++iId)
	{
		index = iId - iBeginID ;
		pItem = (CButton*)GetDlgItem(iId);
		if (pItem->GetCheck() == TRUE)
			iVal = iVal | (1 << index);
	}

	return iVal;
}
