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
	int result = sscanf_s(szText, "%d,%d,%d,%d,%d,%d,%d,%d", &id, &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
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
	int result = swscanf_s(szText, _T("%d,%d,%d,%d,%d,%d,%d,%d"), &id, &number[0], &number[1], &number[2], &number[3], &number[4], &number[5], &number[6]);
	if (result != BALL_COUNT+1)
	{
		Reset();
		return false;
	}
	else
		return  true;
}
CString GroupBallNum::toCString(bool showTime/* = false*/)const
{
	CString res;
	if (IsEmpty())
		return res;

	if (showTime)
		res.Format(_T("%d,%d,%d,%d,%d,%d,%d,%d"), id, number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
	else
		res.Format(_T("%d,%d,%d,%d,%d,%d,%d"), id, number[0], number[1], number[2], number[3], number[4], number[5]);
	return res;
}

bool GroupBallNum::ChehckNumVaild()const
{
	time_t nowTime = time(NULL);
	tm tmNowTime;
	localtime_s(&tmNowTime, &nowTime);
	if (id<2014001 || id>(tmNowTime.tm_year + 1900 + 1) * 1000)
		return false;
	
	for (uint8 i = 0; i < BALL_COUNT; ++i)
	{
		if (!VAILD_BALL_NUM(i,number[i]))
			return false;
		
		if (i > 0 && i<BALL_COUNT-1 && number[i] <= number[i - 1])
			return false;

	}

	return true;
}

std::string GroupBallNum::toStdstring(bool showTime/* = false*/)const
{
	if (IsEmpty())
		return std::string();
	char szOut[256] = "";
	if (showTime)
		sprintf_s(szOut, sizeof(szOut), "%d,%d,%d,%d,%d,%d,%d,%d,%d", id, number[0], number[1], number[2], number[3], number[4], number[5], number[6], time(NULL));
	else
		sprintf_s(szOut, sizeof(szOut), "%d,%d,%d,%d,%d,%d,%d,%d", id, number[0], number[1], number[2], number[3], number[4], number[5], number[6]);
	return std::string(szOut);
}

