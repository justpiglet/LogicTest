
// BallNumDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "MainDlgHandle.h"
#include "MainDlg.h"
#include "functionDlg.h"
// CBallNumDlg �Ի���
class CBallNumDlg : public CDialogEx,public IMainDlgHandle
{
// ����
public:
	CBallNumDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CBallNumDlg();
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
	void OpenAnalysisDlg(bool isRed=true);
	//bool InsertData(const char* szText);
	//bool InsertData(const wchar_t* szText);

	void QueryData(uint32);
public:
	virtual void InsertMsg(const std::string&);
	void CleanUpMsg();

	virtual void InsertNumMgs(const char* szTitle, uint32 src[], uint8 len);
protected:
	afx_msg void OnBnClickedInsert();
	
	afx_msg void OnEnChangeRicheditMgs();
	afx_msg void OnBnClickedCleanMsg();
	
	afx_msg void OnBnClickedBtnQ();
	afx_msg void OnBnClickedBtnD();
	afx_msg void OnBnClickedBtnM();
	afx_msg void OnBnClickedRedDlg();
	afx_msg void OnBnClickedBuleDlg();
private:
	CRichEditCtrl m_reShowMessage;
	CString m_cstrText;
	functionDlg* m_pFunctionDlg;
};
