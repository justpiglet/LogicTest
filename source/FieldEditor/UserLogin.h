#pragma once


// CUserLogin �Ի���

class CUserLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CUserLogin)

public:
	CUserLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserLogin();

// �Ի�������
	enum { IDD = IDD_LOGOIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
