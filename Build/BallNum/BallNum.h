
// BallNum.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBallNumApp: 
// �йش����ʵ�֣������ BallNum.cpp
//

class CBallNumApp : public CWinApp
{
public:
	CBallNumApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBallNumApp theApp;