
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#define SQLITE_OUTSIDE
#include "basedefine.h"



// struct GroupBallNum
// {
// 	uint32 id;
// 	uint8 number[7];
// 
// 	GroupBallNum() 
// 	{
// 		Reset();
// 	}
// 	void Reset()
// 	{
// 		id = 0;
// 		memset(number, 0, sizeof(number));
// 	}
// 	bool Parsing(const char* szText)
// 	{
// 		int result = sscanf_s(szText, "%d:%d,%d,%d,%d,%d,%d,%d", &id,&number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
// 		if (result != BALL_COUNT)
// 		{
// 			Reset();
// 			return false;
// 		}
// 		else
// 			return  true;
// 	}
// 	bool Parsing(const wchar_t* szText)
// 	{
// 		int result = swscanf_s(szText, _T("%d:%d,%d,%d,%d,%d,%d,%d"), &id, &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
// 		if (result != BALL_COUNT)
// 		{
// 			Reset();
// 			return false;
// 		}
// 		else
// 			return  result != BALL_COUNT;
// 	}
// 	CString toCString()
// 	{
// 		CString res;
// 		res.Format(_T("%d:%d,%d,%d,%d,%d,%d,%d"), id, number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
// 		return res;
// 	}
// };





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


