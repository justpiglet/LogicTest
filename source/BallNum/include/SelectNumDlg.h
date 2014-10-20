#pragma once

// SelectNumDlg �Ի���

class SelectNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectNumDlg)

public:
	SelectNumDlg(CPoint pos,bool isRed=true,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectNumDlg();

// �Ի�������
	enum { IDD = IDD_SELECT_NUM_DLG };
	inline uint8 GetCurSelectNum(){ return m_selectNum; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CButton* m_numBtnArr;
	bool m_isRed;
	CPoint m_pos;
	uint8 m_selectNum;
};
