
// FieldEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "base/basedefine.h"

__interface IMainDlgHandle
{
	virtual void MainDlgLogoin()=0;
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

protected:
	void UpdateListControl();
private:
	void ButtonClicked(uint8);
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
private:
	void LoginSuccessUpdate(const std::string&);
private:
	EOpSatus m_status;
	CListCtrl m_ListInfo;
	func m_fun[2][4];
	TCHAR* m_butName[2][4];

	int32 m_curRow;
	IMainDlgHandle* g_pMainDlgHandle;
public:
	afx_msg void OnNMDblclkListInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
