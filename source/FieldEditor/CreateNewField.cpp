// CreateNewField.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "CreateNewField.h"
#include "afxdialogex.h"

TCHAR* g_ItemLvName[4] = { _T("Nomal"), _T("Email"), _T("Web"), _T("Secrect") };
uint32 g_ItemLvValue[4] = { 0, 1, 2, 4 };

// CCreateNewField �Ի���

IMPLEMENT_DYNAMIC(CCreateNewField, CDialogEx)

CCreateNewField::CCreateNewField(EDlg_Mode mMode, CWnd* pParent /*=NULL*/)
: CDialogEx(CCreateNewField::IDD, pParent), m_mode(mMode)
{

}

CCreateNewField::~CCreateNewField()
{
}

void CCreateNewField::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreateNewField, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCreateNewField::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateNewField ��Ϣ�������


void CCreateNewField::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

BOOL CCreateNewField::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CEdit*)GetDlgItem(IDC_FIELD_NICKNAME))->SetLimitText(MAX_LEN_NAME);
	((CEdit*)GetDlgItem(IDC_FIELD_ACCOUNT))->SetLimitText(MAX_LEN_NAME);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD1))->SetLimitText(MAX_LEN_PWD);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD2))->SetLimitText(MAX_LEN_PWD);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD3))->SetLimitText(MAX_LEN_PWD);
	((CEdit*)GetDlgItem(IDC_FIELD_RELATION))->SetLimitText(MAX_LEN_NAME);
	((CEdit*)GetDlgItem(IDC_FIELD_COMMENT))->SetLimitText(MAX_LEN_TEXT);

	CComboBox* pBom = (CComboBox*)GetDlgItem(IDC_FIELD_LV_LIST);
	for (uint8 i = SHOW_ITEM_LV_NOR; i < SHOW_ITEM_LV_SECRET;++i)
		pBom->InsertString(i,g_ItemLvName[i]);
	pBom->SetCurSel(0);

	return TRUE;
}

void CCreateNewField::UpdateGui()
{
	BOOL isEnable(FALSE);
	if (m_mode == EDlg_Mode_New)
		isEnable = TRUE;
	((CEdit*)GetDlgItem(IDC_FIELD_NICKNAME))->SetReadOnly(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_ACCOUNT))->SetReadOnly(isEnable);

	if (m_mode == EDlg_Mode_Read)
		isEnable = TRUE;
	else
		isEnable = FALSE;
	((CComboBox*)GetDlgItem(IDC_FIELD_LV_LIST))->EnableWindow(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD1))->SetReadOnly(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD2))->SetReadOnly(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD3))->SetReadOnly(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_RELATION))->SetReadOnly(isEnable);
	((CEdit*)GetDlgItem(IDC_FIELD_COMMENT))->SetReadOnly(isEnable);
}
