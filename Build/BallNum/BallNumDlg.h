
// BallNumDlg.h : ͷ�ļ�
//

#pragma once

#include "sqlitedb/SqliteDatabasePro.h"
#include "sqlitedb/SqliteDatabase.h"
#include "sqlitedb/SqliteRecordSet.h"

// CBallNumDlg �Ի���
class CBallNumDlg : public CDialogEx
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

private:
	CSqliteDatabase* m_pDataBase;
};
