#pragma once
#include "YearSetDlg.h"
// functionDlg 对话框

class functionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(functionDlg)

public:
	functionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~functionDlg();

// 对话框数据
	enum { IDD = IDD_FUNCTION_DLG };

	inline void SetYearInfo(const YearInfo& myearInfo){ m_yearInfo = myearInfo; }
	void UpdateTitle();
private:
	YearInfo m_yearInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSetyearBtn();
	afx_msg void OnBnClickedRedCountBtn();
	afx_msg void OnBnClickedBlueCountBtn();
	afx_msg void OnBnClickedBlueOffset();
	afx_msg void OnBnClickedCloseBtn();
	afx_msg void OnBnClickedRedFrequency();
	afx_msg void OnBnClickedBlueFrequency();
};
