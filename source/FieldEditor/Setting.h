#pragma once
#include "Field/UserFieldManage.h"

// CSetting 对话框

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(const User_Set* puSet, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetting();

// 对话框数据
	enum { IDD = IDD_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
