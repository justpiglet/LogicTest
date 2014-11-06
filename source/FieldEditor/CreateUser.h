#pragma once
#include "Base/basedefine.h"

// CCreateUser 对话框

class CCreateUser : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateUser)

public:
	CCreateUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateUser();

// 对话框数据
	enum { IDD = IDD_CREATE_DLG };

	bool GetCreateUersInfo(std::string&,std::string&);
private:
	bool IsTextLegal(const CString&);
	void Exchange(CString&,std::string&);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	std::string m_strAccount;
	std::string m_strPwd;
};
