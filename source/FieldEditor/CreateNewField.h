#pragma once
#include "Field/FieldDeifne.h"

// CCreateNewField �Ի���

enum EDlg_Mode
{
	EDlg_Mode_New=0,
	EDlg_Mode_Read,
	EDlg_Mode_Mode,
};

class CCreateNewField : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateNewField)

public:
	CCreateNewField(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateNewField();

// �Ի�������
	enum { IDD = IDD_CREATE_FIELD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	FIELD_ITEM m_filedInfo;
};
