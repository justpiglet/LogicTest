#include "stdafx.h"
#include "GroupBallNum.h"


GroupBallNum::GroupBallNum()
{
	Reset();
}


GroupBallNum::~GroupBallNum()
{
}

void GroupBallNum::Reset()
{
 	id = 0;
 	memset(number, 0, sizeof(number));
}

bool GroupBallNum::Parsing(const char* szText)
{
	int result = sscanf_s(szText, "%d:%d,%d,%d,%d,%d,%d,%d", &id, &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
	if (result != BALL_COUNT+1)
	{
		Reset();
		return false;
	}
	else
		return  true;
}
bool GroupBallNum::Parsing(const wchar_t* szText)
{
	int result = swscanf_s(szText, _T("%d:%d,%d,%d,%d,%d,%d,%d"), &id, &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
	if (result != BALL_COUNT+1)
	{
		Reset();
		return false;
	}
	else
		return  true;
}
CString GroupBallNum::toCString()
{
	CString res;
	res.Format(_T("%d:%d,%d,%d,%d,%d,%d,%d"), id, number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
	return res;
}

bool GroupBallNum::ChehckNumVaild()const
{
	time_t nowTime = time(NULL);
	tm tmNowTime;
	localtime_s(&tmNowTime, &nowTime);
	if (id<2014001 || id>(tmNowTime.tm_year + 1900 + 1) * 1000)
		return false;
	else
		return true;
}

// void GroupBallNum::toChar(char szOut[],int len)
// {
// 	sprintf_s(szOut, len, "%d:%d, %d, %d, %d, %d, %d, %d", id, number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
// }

void GroupBallNum::SaveChar(char szOut[], int len, const GroupBallNum& src)
{
	sprintf_s(szOut, len, "%d,%d,%d,%d,%d,%d,%d,%d,%d", src.id, src.number[0], src.number[1], src.number[2], src.number[3], src.number[4], src.number[5], src.number[6],time(NULL));
}

// void GroupBallNum::toChar(char szOut[], const GroupBallNum& src)
// {
// 	sprintf_s(szOut, "%d:%d, %d, %d, %d, %d, %d, %d", src.id, src.number[0], src.number[1], src.number[2], src.number[3], src.number[4], src.number[5], src.number[6]);
// }
