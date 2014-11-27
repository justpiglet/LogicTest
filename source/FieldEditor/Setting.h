#pragma once
#include "Field/UserFieldManage.h"

// CSetting �Ի���

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(const User_Set* puSet, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetting();

// �Ի�������
	enum { IDD = IDD_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	void SetFieldCheckStatus(uint32 iVal);
	void SetLevelCheckStatus(uint32 iVal);
private:
	const User_Set* m_pUSet;
public:
	afx_msg void OnBnClickedApplyBtn();
};
