
// FieldEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFieldEditorApp: 
// �йش����ʵ�֣������ FieldEditor.cpp
//

class CFieldEditorApp : public CWinApp
{
public:
	CFieldEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

};

extern CFieldEditorApp theApp;