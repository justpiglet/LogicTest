#pragma once
#include "Field/FieldDeifne.h"

// CCreateNewField 对话框

#define EVENT_CREATE_FILED_TIMER 101

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
	CCreateNewField(EDlg_Mode mMode,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateNewField();

	//EDlg_Mode！=read ，pField can NULL
	void SetDataInfo(uint32 iRow,const FIELD_ITEM*pField=NULL);
// 对话框数据
	enum { IDD = IDD_CREATE_FIELD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	void UpdateGui();
	bool VerifyPassword();
	bool Modify();
	bool Create();

	void ShowPassword(const FIELD_ITEM* pFiled, bool isHidePart = true);
	bool ReadEdit(uint32 iItemId,void* pDest,uint16 iLen);
	void ShowReadFieldInfo();
	void CloseTimer();
private:
	EDlg_Mode			m_mode;
	const FIELD_ITEM*	m_pReadField;
	uint32				m_iCurRow;
	int32				m_iShowPwdTime;
	uint32				m_iFieldID;

	//HANDLE m_event;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedDeleteBtn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedShowpwdBtn();
	afx_msg void OnClose();
};
