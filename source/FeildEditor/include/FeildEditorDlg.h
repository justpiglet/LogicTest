
// FeildEditorDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CFeildEditorDlg 对话框
class CFeildEditorDlg : public CDialogEx
{
// 构造
public:
	CFeildEditorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FEILDEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	void UpdateListControl();
private:

	CListCtrl m_ListInfo;
public:
	afx_msg void OnNMRClickListInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuClickPeepFeildInfo();
	afx_msg void OnMenuClickPeepPwd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedLogoin();
	afx_msg void OnBnClickedInsertInfo();
	afx_msg void OnBnClickedSetting();
	afx_msg void OnBnClickedCreateUser();
};
