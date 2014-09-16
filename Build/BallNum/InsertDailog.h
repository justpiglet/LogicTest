#pragma once
#include "afxwin.h"


// InsertDailog 对话框

class InsertDailog : public CDialogEx
{
	DECLARE_DYNAMIC(InsertDailog)

public:
	InsertDailog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InsertDailog();

// 对话框数据
	enum { IDD = IDD_INSERT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	bool InsertData(const char* szText);
	bool InsertData(const wchar_t* szText);
public:

	afx_msg void OnBnClickedOk();
	CString m_szData;
};
