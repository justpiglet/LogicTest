#pragma once


// MainDlg �Ի���

class MainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainDlg)

public:
	MainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MainDlg();

// �Ի�������
	enum { IDD = IDD_MAIN_DLG };
	//inline void SetRelationWnd(CWnd* pWnd){ m_pShowWnd = pWnd; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};
