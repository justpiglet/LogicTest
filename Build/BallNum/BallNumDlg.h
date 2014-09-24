
// BallNumDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MainDlgHandle.h"

// CBallNumDlg �Ի���
class CBallNumDlg : public CDialogEx,public IMainDlgHandle
{
// ����
public:
	CBallNumDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BALLNUM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

protected:
	int CalculateIdByTime();
	//bool InsertData(const char* szText);
	//bool InsertData(const wchar_t* szText);

	void QueryData(uint32);
public:
	virtual void InsertMsg(const std::string&);
	void CleanUpMsg();

	virtual void InsertNumMgs(const char* szTitle, uint32 src[], uint8 len);
public:
	afx_msg void OnBnClickedInsert();
	CRichEditCtrl m_reShowMessage;
	afx_msg void OnEnChangeRicheditMgs();
	afx_msg void OnBnClickedCleanMsg();
	CString m_cstrText;
	afx_msg void OnBnClickedBtnQ();
	afx_msg void OnBnClickedBtnD();
	afx_msg void OnBnClickedBtnM();
};
