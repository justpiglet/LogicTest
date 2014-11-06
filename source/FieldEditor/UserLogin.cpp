// UserLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "UserLogin.h"
#include "afxdialogex.h"


// CUserLogin 对话框

IMPLEMENT_DYNAMIC(CUserLogin, CDialogEx)

CUserLogin::CUserLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserLogin::IDD, pParent)
{

}

CUserLogin::~CUserLogin()
{
}

void CUserLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUserLogin, CDialogEx)
END_MESSAGE_MAP()


// CUserLogin 消息处理程序
