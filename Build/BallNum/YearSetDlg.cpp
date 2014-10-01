// YearSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "YearSetDlg.h"
#include "afxdialogex.h"
#include "Analysis/BaseAnalysis.h"

// YearSetDlg 对话框

IMPLEMENT_DYNAMIC(YearSetDlg, CDialogEx)

YearSetDlg::YearSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(YearSetDlg::IDD, pParent)
{
	
}

YearSetDlg::~YearSetDlg()
{
}

void YearSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_YEAR_START_LIST, m_startList);
	DDX_Control(pDX, IDC_YEAR_COUNT_LIST, m_countList);
}


BEGIN_MESSAGE_MAP(YearSetDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &YearSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL YearSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	uint8 istartID = BaseAnalysis::share()->GetMinID();
	uint8 iEndID = BaseAnalysis::share()->GetMaxID();
	CString strCount;
	CString strYear;
	uint8 index = 0;
	for (uint8 i = istartID; i <= iEndID; ++i, ++index)
	{
		strCount.Format(_T("%d"), index + 1);
		m_countList.InsertString(index,strCount);
		strYear.Format(_T("20%02d"), i);
		m_startList.InsertString(index, strYear);
	}
	m_countList.SetCurSel(0);
	m_startList.SetCurSel(index-1);
	return TRUE;
}


// YearSetDlg 消息处理程序


void YearSetDlg::OnBnClickedOk()
{
	int index = m_startList.GetCurSel();
	if (index == -1)
		return;
	CString strText;
	m_startList.GetLBText(index,strText);
	int nYear(0);
	swscanf_s(strText.GetBuffer(), _T("%d"), &nYear);
	m_yearInfo.mSYear = nYear % 100;
	m_yearInfo.mCount = m_countList.GetCurSel() + 1;
	if (m_yearInfo.mCount <= 0)
		m_yearInfo.mCount = 1;
	CDialogEx::OnOK();
}
