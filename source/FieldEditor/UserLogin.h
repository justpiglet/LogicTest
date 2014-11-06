#pragma once


// CUserLogin 对话框

class CUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLogin)

public:
	CUserLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserLogin();

// 对话框数据
	enum { IDD = IDD_LOGOIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
