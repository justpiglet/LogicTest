// CreateNewField.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "CreateNewField.h"
#include "afxdialogex.h"
#include "UserLogin.h"
#include "Depend/cantools/tools.h"
#include "FieldEditorDlg.h"

TCHAR* g_ItemLvName[] = { _T("NULL"), _T("Nomal"), _T("Email"), _T("Web"), _T("Secrect") };
uint32 g_ItemLvValue[] = { 0, 1, 2, 4 ,8};

// CCreateNewField 对话框

IMPLEMENT_DYNAMIC(CCreateNewField, CDialogEx)

CCreateNewField::CCreateNewField(EDlg_Mode mMode, CWnd* pParent /*= NULL*/)
: CDialogEx(CCreateNewField::IDD, pParent), m_mode(mMode), m_pReadField(NULL), m_iShowPwdTime(-1), m_iCurRow(-1)
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
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CCreateNewField::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_DELETE_BTN, &CCreateNewField::OnBnClickedDeleteBtn)
	ON_BN_CLICKED(IDC_SHOWPWD_BTN, &CCreateNewField::OnBnClickedShowpwdBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCreateNewField 消息处理程序


void CCreateNewField::OnBnClickedOk()
{
	if (m_mode == EDlg_Mode_Modify || m_mode == EDlg_Mode_New)
	{
		FIELD_ITEM mField;
		ReadEdit(IDC_FIELD_NICKNAME, mField.strNameNick, MAX_LEN_NAME);
		ReadEdit(IDC_FIELD_ACCOUNT, mField.strNameNick, MAX_LEN_NAME);
		int32 inDex= ((CComboBox*)GetDlgItem(IDC_FIELD_LV_LIST))->GetCurSel();
		if (inDex == -1)
			inDex = 0;
		if (inDex == 0)
			mField.iLv = 0;
		else if (inDex<4)
			mField.iLv = 1 << inDex;

		ReadEdit(IDC_FIELD_PWD1, mField.strLoginPwd, MAX_LEN_PWD);
		ReadEdit(IDC_FIELD_PWD2, mField.strPayPwd, MAX_LEN_PWD);
		ReadEdit(IDC_FIELD_PWD3, mField.strOtherPwd, MAX_LEN_PWD);

		ReadEdit(IDC_FIELD_RELATION, mField.strRelation, MAX_LEN_NAME);
		ReadEdit(IDC_FIELD_COMMENT, mField.strDescribe, MAX_LEN_TEXT);

		const FIELD_ITEM* pData = UserFieldManage::Share()->UserFieldModify(mField);

		if (g_mainDlg)
			g_mainDlg->UpdateListControlOneRow(m_iCurRow, pData);
	}

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
	GetDlgItem(IDC_MODIFY_BTN)->ShowWindow(isEnable ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_DELETE_BTN)->ShowWindow(isEnable ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SHOWPWD_BTN)->ShowWindow(isEnable ? SW_SHOW : SW_HIDE);
}

void CCreateNewField::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == EVENT_CREATE_FILED_TIMER)
	{
		if (m_mode == EDlg_Mode_Read  && m_iShowPwdTime > 0)
		{
			++m_iShowPwdTime;
			if (m_iShowPwdTime > UserFieldManage::Share()->GetCurUserFields()->GetShowPwdTime())
			{
				m_iShowPwdTime = -1;
				GetDlgItem(IDC_SHOWPWD_BTN)->EnableWindow(true);
			}
		}
	}
}
void CCreateNewField::OnBnClickedModifyBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	m_mode = EDlg_Mode_Modify;
	UpdateGui();
}


void CCreateNewField::OnBnClickedDeleteBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!m_pReadField)
		return;

	UserFieldManage::Share()->UserFieldDelete(m_pReadField->iFieldId);
}

bool CCreateNewField::VerifyPassword()
{
	CUserLogin dlg(ELOGOIN_MODE_OPERATE, UserFieldManage::Share()->GetCurAccount()->strName);
	if (dlg.DoModal() == IDOK)
		return dlg.IsLogoinSuccess();
	
	return false;
}

void CCreateNewField::SetDataInfo(uint32 iRow, const FIELD_ITEM* pFiled/*=NULL*/)
{
	m_iCurRow = iRow;
	if (m_mode != EDlg_Mode_Read)
		return;

	m_pReadField = pFiled;

	((CEdit*)GetDlgItem(IDC_FIELD_NICKNAME))->SetWindowText(CString(pFiled->strNameNick));
	((CEdit*)GetDlgItem(IDC_FIELD_ACCOUNT))->SetWindowText(CString(pFiled->strAccount));

	for (int32 i = sizeof(g_ItemLvValue) - 1; i >= 0; --i)
		if (g_ItemLvValue[i] == pFiled->iLv)
			((CComboBox*)GetDlgItem(IDC_FIELD_LV_LIST))->SetCurSel(i);

	ShowPassword(pFiled, true);

	((CEdit*)GetDlgItem(IDC_FIELD_RELATION))->SetWindowText(CString(pFiled->strRelation));
	((CEdit*)GetDlgItem(IDC_FIELD_COMMENT))->SetWindowText(CString(pFiled->strDescribe));
}


void CCreateNewField::OnBnClickedShowpwdBtn()
{
	if (m_mode == EDlg_Mode_Read && m_pReadField != NULL)
	{
		ShowPassword(m_pReadField, false);
	}
		
}

void CCreateNewField::ShowPassword(const FIELD_ITEM* pFiled,bool isHidePart /*= true*/)
{
	if (!isHidePart)
	{
		GetDlgItem(IDC_SHOWPWD_BTN)->EnableWindow(false);
		m_iShowPwdTime = 0;
	}
		

	STDSTR strTemp = UserFieldManage::Share()->GetCurUserFields()->GetFieldHideParts(pFiled, FieldColumn_PwdLogin, isHidePart);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD1))->SetWindowText(CString(strTemp.c_str()));

	strTemp = UserFieldManage::Share()->GetCurUserFields()->GetFieldHideParts(pFiled, FieldColumn_PwdPay, isHidePart);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD2))->SetWindowText(CString(strTemp.c_str()));

	strTemp = UserFieldManage::Share()->GetCurUserFields()->GetFieldHideParts(pFiled, FieldColumn_PwdOther, isHidePart);
	((CEdit*)GetDlgItem(IDC_FIELD_PWD3))->SetWindowText(CString(strTemp.c_str()));
}

void CCreateNewField::ReadEdit(uint32 iItemId, void* pDest, uint16 Len)
{
	CString cstrText("");
	GetDlgItemText(iItemId, cstrText);
	STDSTR strText("");
#ifdef _UNICODE
	char* pText = _CANNP_NAME::code::UnicodeToAscii(cstrText.GetBuffer(), cstrText.GetLength());
	memcpy_s(pDest, Len, pText, strlen(pText));
	delete pText;
#else
	memcpy_s(pDest, Len, cstrText.GetBuffer(), cstrText.GetLength());
#endif
}
