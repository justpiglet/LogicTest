#pragma once
#include "Base/basedefine.h"

// CCreateUser �Ի���

class CCreateUser : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateUser)

public:
	CCreateUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateUser();

// �Ի�������
	enum { IDD = IDD_CREATE_DLG };

	bool GetCreateUersInfo(std::string&,std::string&);
private:
	bool IsTextLegal(const CString&);
	void Exchange(CString&,std::string&);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	std::string m_strAccount;
	std::string m_strPwd;
};
