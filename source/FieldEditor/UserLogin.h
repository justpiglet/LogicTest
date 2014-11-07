#pragma once
#include "Base/basedefine.h"
#include "afxwin.h"

#include "Field/UserFieldManage.h"
// CUserLogin �Ի���

class CUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLogin)

public:
	CUserLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLogin();

// �Ի�������
	enum { IDD = IDD_LOGOIN_DLG };

	inline bool IsLogoinSuccess(){ return m_iStatus == 0; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedLogoinBt();
private:
	CComboBox m_AccountList;
	std::string m_strAccount;
	VEC_STR m_vecAccount;
	uint8 m_iStatus;
};
