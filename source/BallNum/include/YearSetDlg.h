#pragma once
#include "afxwin.h"


// YearSetDlg 对话框

class YearSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YearSetDlg)
public:
	const YearInfo& GetYearIfo(){ return m_yearInfo; }
public:
	YearSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~YearSetDlg();

// 对话框数据
	enum { IDD = IDD_YEAR_DLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()
private:
	YearInfo m_yearInfo;
	CComboBox m_startList;
	CComboBox m_countList;
};
