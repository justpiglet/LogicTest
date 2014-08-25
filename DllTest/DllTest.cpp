// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string>
#include <time.h>
#include"publicpro.h"
#include "tools.h"


typedef ILogicPool* (*GET_HFUNC)();
typedef void(*DESTROY_HFUNC)(ILogicPool*);


#ifdef _DEBUG
#define DLLName _T("NewLogicD.dll")
#else
#define DLLName _T("NewLogic.dll")
#endif // _DEBUG

ILogicPool* pp = NULL;

#include "mathTest.h"
/*
int _tmain(int argc, _TCHAR* argv[])
{
	Point a(2.3, 5.5);
	Point b(0.1, -5.5);
	//Point c(0.1+1, -5.5);
	//Point d(5+1,19);
	Point c(-1, -1);
	Point d(4,2);
	Point p(-99,-99);
	
	LONGLONG start = GetTickCount();
	LONGLONG ends = start;
	//for (int i = 0; i < 10000000; ++i)
		segcrossEX(c, d, a, b, p);

	ends = GetTickCount();
	printf("111,%lld \n", ends - start);
	start = ends;
		
	for (int i = 0; i < 10000000; ++i)
	bool result = intersect3(c,d, a, b);

	/*ends = GetTickCount();
	printf("222,%lld \n", ends - start);

	system("pause");
	return 0;
}*/

int _tmain(int argc, _TCHAR* argv[])
{
	float aa = 0.00000001;
	float bb = -0.00000001;
	float cc = 1e-10;

	//////////////////////////////////////////////////
	/*std::string aa;
	aes_byte outtex[16 + 1] = "";
	aes_ctx ctx;
	aes_set_key(&ctx, (aes_byte*)pwd, 32, aes_both);
	if (aes_encrypt(&ctx, (aes_byte*)text, outtex) == aes_good)
		aa=((char*)outtex);
	else
		aa=("ERROR");*/

	//////////////////////////////////////////////////
	/*FILE *fp = nullptr;
	int nerror = fopen_s(&fp, "aa.log", "w");
	
	for (int i = 0; i < 100; ++i)
	{
		int ntemp = CaRandoom::GetRandoom(0,2);
		fwrite((char*)&ntemp, sizeof(int), 1, fp);
		//fwrite("  ", 1, 2, fp);
	}*/
	/////////////////////////////////////////////////	
	
	TCHAR textName[128]=_T("");
	int nn[128]={0};

	wsprintf(textName, _T("../libraries/%s"), DLLName);
	HINSTANCE hDLL = LoadLibrary(textName);
	if (hDLL)
	{
		GET_HFUNC hFun = (GET_HFUNC)GetProcAddress(hDLL,"CaLogicFactroyShare");      

		if (hFun)
			pp = hFun();
		else
			return 0;
		bool aa = pp->Init("../resource/attribute.json",8);
		//bool aa = pp->Init("../resource/menu.json");
		pp->GetObjectTimes(1);

		DWORD t1= GetTickCount();
		DWORD t2;
		while (true)
		{
			t2 = GetTickCount();
			pp->update((t2-t1)/1000.0);
			t1 = t2;
			Sleep(160);
		}
	}
	else
	{
		//加载失败
	}

	system("pause");
	return 0;
}

