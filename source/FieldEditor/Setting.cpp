// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FieldEditor.h"
#include "Setting.h"
#include "afxdialogex.h"


// CSetting �Ի���

IMPLEMENT_DYNAMIC(CSetting, CDialogEx)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetting::IDD, pParent)
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetting, CDialogEx)
END_MESSAGE_MAP()


// CSetting ��Ϣ�������
