#pragma once
#include "afxwin.h"


// InsertDailog �Ի���

class InsertDailog : public CDialogEx
{
	DECLARE_DYNAMIC(InsertDailog)

public:
	InsertDailog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InsertDailog();

// �Ի�������
	enum { IDD = IDD_INSERT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	bool InsertData(const char* szText);
	bool InsertData(const wchar_t* szText);
public:

	afx_msg void OnBnClickedOk();
	CString m_szData;
};
