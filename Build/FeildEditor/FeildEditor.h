
// FeildEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFeildEditorApp: 
// �йش����ʵ�֣������ FeildEditor.cpp
//

class CFeildEditorApp : public CWinApp
{
public:
	CFeildEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CFeildEditorApp theApp;