
// FeildEditorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CFeildEditorDlg �Ի���
class CFeildEditorDlg : public CDialogEx
{
// ����
public:
	CFeildEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FEILDEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
