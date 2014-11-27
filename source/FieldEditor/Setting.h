#pragma once
#include "Field/UserFieldManage.h"
#include "afxwin.h"

// CSetting 对话框

class CSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting( CWnd* pParent = NULL);   // 标准构造函数
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

	uint32 GetFieldCheckStatus();
	uint32 GetLevelCheckStatus();
private:
	
public:
	afx_msg void OnBnClickedApplyBtn();
	CComboBox m_TimeList;
};
