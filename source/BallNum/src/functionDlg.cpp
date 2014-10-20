// functionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BallNum.h"
#include "functionDlg.h"
#include "afxdialogex.h"
#include "../Analysis/BaseAnalysis.h"
#include "SelectNumDlg.h"

// functionDlg 对话框

IMPLEMENT_DYNAMIC(functionDlg, CDialogEx)

functionDlg::functionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(functionDlg::IDD, pParent)
{

}

functionDlg::~functionDlg()
{
}

void functionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(functionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SETYEAR_BTN, &functionDlg::OnBnClickedSetyearBtn)
	ON_BN_CLICKED(IDC_RED_COUNT_BTN, &functionDlg::OnBnClickedRedCountBtn)
	ON_BN_CLICKED(IDC_BLUE_COUNT_BTN, &functionDlg::OnBnClickedBlueCountBtn)
	ON_BN_CLICKED(IDC_BLUE_OFFSET, &functionDlg::OnBnClickedBlueOffset)
	ON_BN_CLICKED(IDC_CLOSE_BTN, &functionDlg::OnBnClickedCloseBtn)
	ON_BN_CLICKED(IDC_RED_FREQUENCY, &functionDlg::OnBnClickedRedFrequency)
	ON_BN_CLICKED(IDC_BLUE_FREQUENCY, &functionDlg::OnBnClickedBlueFrequency)
END_MESSAGE_MAP()


// functionDlg 消息处理程序


void functionDlg::OnBnClickedSetyearBtn()
{
	YearSetDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		SetYearInfo(dlg.GetYearIfo());
		UpdateTitle();
	}
}


void functionDlg::OnBnClickedRedCountBtn()
{
	BaseAnalysis::share()->CalculateBallCount(m_yearInfo);
	
}


void functionDlg::OnBnClickedBlueCountBtn()
{
	BaseAnalysis::share()->CalculateBallCount(m_yearInfo,false);
	// TODO:  在此添加控件通知处理程序代码
}


void functionDlg::OnBnClickedBlueOffset()
{
	BaseAnalysis::share()->AnBlueBallTrend(m_yearInfo);
}

void functionDlg::UpdateTitle()
{
	std::string strTitle= m_yearInfo.GetStringInterval();
	SetWindowText(CString(strTitle.c_str()));
}


void functionDlg::OnBnClickedCloseBtn()
{
	// TODO:  在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
}


void functionDlg::OnBnClickedRedFrequency()
{
	// TODO:  在此添加控件通知处理程序代码
	bool isRed(true);
	CRect rc;
	GetDlgItem(IDC_RED_FREQUENCY)->GetWindowRect(rc);
	SelectNumDlg dlg(rc.TopLeft(), isRed);
	
	if (dlg.DoModal() == IDOK)
	{
		uint8 selectNum = dlg.GetCurSelectNum();
		if (selectNum != 255)
			BaseAnalysis::share()->NumAppearance(m_yearInfo, selectNum, isRed);
	}
}


void functionDlg::OnBnClickedBlueFrequency()
{
	// TODO:  在此添加控件通知处理程序代码
	bool isRed(false);
	CRect rc;
	GetDlgItem(IDC_BLUE_FREQUENCY)->GetWindowRect(rc);
	SelectNumDlg dlg(rc.TopLeft(), isRed);
	
	if (dlg.DoModal() == IDOK)
	{
		uint8 selectNum = dlg.GetCurSelectNum();
		if (selectNum != 255)
			BaseAnalysis::share()->NumAppearance(m_yearInfo, selectNum, isRed);
	}
}
