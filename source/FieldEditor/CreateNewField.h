#pragma once
#include "Field/FieldDeifne.h"

// CCreateNewField 对话框

enum EDlg_Mode
{
	EDlg_Mode_New=0,
	EDlg_Mode_Read,
	EDlg_Mode_Modify,
};

class CCreateNewField : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateNewField)

public:
	CCreateNewField(uint32 iID,EDlg_Mode mMode,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateNewField();

// 对话框数据
	enum { IDD = IDD_CREATE_FIELD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	void UpdateGui();
	bool VerifyPassword();
private:
	uint32 m_iFieldId;
	EDlg_Mode m_mode;
public:
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedOk();
};
