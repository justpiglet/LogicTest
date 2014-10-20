// SelectNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "SelectNumDlg.h"
#include "afxdialogex.h"
#include "GroupBallNum.h"

#define ID_BTN_START (USER_VALUE+1000)
// SelectNumDlg 对话框

IMPLEMENT_DYNAMIC(SelectNumDlg, CDialogEx)

SelectNumDlg::SelectNumDlg(CPoint pos, bool isRed/* = true*/, CWnd* pParent /*=NULL*/)
: CDialogEx(SelectNumDlg::IDD, pParent), m_isRed(isRed), m_pos(pos)
{
	m_numBtnArr = new CButton[F_COUNT_NUM(m_isRed)];
	m_selectNum = -1;
}

SelectNumDlg::~SelectNumDlg()
{
	if (m_numBtnArr)
		delete [] m_numBtnArr;
}

void SelectNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectNumDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL SelectNumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	uint8 hCount(4), vCount(4);
	if (m_isRed)
	{
		hCount = 6;
		vCount = 6;
	}
	uint8 allCount = F_COUNT_NUM(m_isRed);
	uint8 hTemp(0), vTemp(0);
	CPoint sPos(2, 2);
	CSize mSize(40, 40);
	CSize mSpace(2, 2);
	CString strCap("");
	CRect rc;
	for (uint8 i = 0; i < allCount; ++i)
	{
		hTemp = i / hCount;
		vTemp = i % vCount;
		rc.left = sPos.x + vTemp*(mSize.cx+mSpace.cx);
		rc.top = sPos.y + hTemp*(mSize.cy + mSpace.cy);
		rc.right = rc.left + mSize.cx;
		rc.bottom = rc.top + mSize.cy;
		
		strCap.Format(_T("%d"), i+1);
		m_numBtnArr[i].Create(strCap, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc, this, ID_BTN_START + i);
	}
	
	int nWidth = GetSystemMetrics(SM_CXSCREEN);  //屏幕宽度    
	int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
	CSize rcSize;
	//if (allCount%vCount != 0)
	//	hCount += 1;
	rcSize.cx =17 + sPos.x * 2 + (mSize.cx + mSpace.cx)*(vCount - 1) + mSize.cx;
	rcSize.cy =37 + sPos.y * 2 + (mSize.cy + mSpace.cy)*(hCount - 1) + mSize.cy;
	if (m_pos.x * 2>nWidth)
		rc.left = m_pos.x - rcSize.cx;
	else
		rc.left = m_pos.x;

	if (m_pos.y * 2 > nHeight)
		rc.top = m_pos.y - rcSize.cy;
	else
		rc.top = m_pos.y;
	rc.right = rc.left + rcSize.cx;
	rc.bottom = rc.top + rcSize.cy;
	SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	return TRUE;
}

BOOL SelectNumDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int32 numId = uint8(wParam - ID_BTN_START + 1);
	if (numId > 0 && numId <= F_COUNT_NUM(m_isRed))
	{
		m_selectNum = (uint8)numId;
		OnOK();
		return true;
	}
	else 
		return CDialogEx::OnCommand(wParam, lParam);
}


// SelectNumDlg 消息处理程序
