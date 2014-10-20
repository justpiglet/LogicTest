#pragma once
#include "afxwin.h"


// YearSetDlg �Ի���

class YearSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YearSetDlg)
public:
	const YearInfo& GetYearIfo(){ return m_yearInfo; }
public:
	YearSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~YearSetDlg();

// �Ի�������
	enum { IDD = IDD_YEAR_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	YearInfo m_yearInfo;
	CComboBox m_startList;
	CComboBox m_countList;
};
