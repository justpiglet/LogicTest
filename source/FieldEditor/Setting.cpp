// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

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


// CSetting ��Ϣ�������


void CSetting::OnBnClickedApplyBtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
