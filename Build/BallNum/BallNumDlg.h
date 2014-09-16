
// BallNumDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"



// CBallNumDlg 对话框
class CBallNumDlg : public CDialogEx
{
// 构造
public:
	CBallNumDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BALLNUM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	int CalculateIdByTime();
	
private:
	

public:
	afx_msg void OnBnClickedInsert();
	CRichEditCtrl m_reShowMessage;
	afx_msg void OnEnChangeRicheditMgs();
};
