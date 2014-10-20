#pragma once

// SelectNumDlg 对话框

class SelectNumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SelectNumDlg)

public:
	SelectNumDlg(CPoint pos,bool isRed=true,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectNumDlg();

// 对话框数据
	enum { IDD = IDD_SELECT_NUM_DLG };
	inline uint8 GetCurSelectNum(){ return m_selectNum; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	CButton* m_numBtnArr;
	bool m_isRed;
	CPoint m_pos;
	uint8 m_selectNum;
};
