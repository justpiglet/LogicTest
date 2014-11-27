
// FieldEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "base/basedefine.h"
#include "Field/UserFieldManage.h"
#include "CreateUser.h"
#include "UserLogin.h"
#include "CreateNewField.h"

__interface IMainDlgHandle
{
	virtual void MainDlgLogoin()=0;
	virtual void UpdateListControl() = 0;
	virtual bool UpdateListControlOneRow(uint32 iRow, const FIELD_ITEM* pData) = 0;
};

// CFieldEditorDlg �Ի���
class CFieldEditorDlg : public CDialogEx, public IMainDlgHandle
{
	enum EOpSatus
	{
		EOpSatus_NULL = 0,
		EOpSatus_Logoin,
	};
	typedef void (CFieldEditorDlg::*func)();
// ����
public:
	CFieldEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FEILDEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void MainDlgLogoin() ;

public:
	virtual void UpdateListControl();
	virtual bool UpdateListControlOneRow(uint32 iRow, const FIELD_ITEM* pData);
private:

public:
	afx_msg void OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuClickPeepFieldInfo();
	afx_msg void OnMenuClickPeepPwd();
	afx_msg void OnBnClickedOk();
private:
	void DoNothing();
	void Logoin();
	void CreateNewUser();
	void Setting();

	void LogoinOut();
	void CreateNewField();
	void TrashBasket();
	void SettingUpdate();

	void UpdateButton();
	void OpenFieldInfoDlg(EDlg_Mode mMode,uint32 iRow);
private:
	void LoginSuccessUpdate(const std::string&);
	uint32 GetClickRow(CPoint point);

	const FIELD_ITEM* GetCurFieldItem();
private:
	EOpSatus m_status;
	CListCtrl m_ListInfo;
	func m_fun[2][4];
	TCHAR* m_butName[2][4];
	const CField* m_pCurField;
	int32 m_curRow;
	//IMainDlgHandle* g_pMainDlgHandle;
public:
	afx_msg void OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult);
};

extern IMainDlgHandle* g_mainDlg;