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
	mId = 0;
	memset(mNumber, 0, sizeof(mNumber));
}
bool GroupBallNum::Parsing(const int iNums[], uint32 count)
{
	if (BALL_COUNT + 1 != count)
	{
		Reset();
		return false;
	}
	
	mId = iNums[0];
	if (mId > 2000000)
		mId = mId % 100000;

	for (uint32 i = 1; i < count; ++i)
		mNumber[i - 1] = iNums[i];

	return true;
}
bool GroupBallNum::Parsing(const char* szText)
{
	int tempArr[8] = {0};
	int result = sscanf_s(szText, "%d,%d,%d,%d,%d,%d,%d,%d", &tempArr[0], &tempArr[1], &tempArr[2], &tempArr[3], &tempArr[4], &tempArr[5], &tempArr[6], &tempArr[7]);
	return Parsing(tempArr, result);	
}
bool GroupBallNum::Parsing(const wchar_t* szText)
{
	int tempArr[8] = { 0 };
	int result = swscanf_s(szText, _T("%d,%d,%d,%d,%d,%d,%d,%d"), &tempArr[0], &tempArr[1], &tempArr[2], &tempArr[3], &tempArr[4], &tempArr[5], &tempArr[6], &tempArr[7]);
	return Parsing(tempArr, result);
}
CString GroupBallNum::toCString(bool showTime/* = false*/)const
{
	CString res;
	if (IsEmpty())
		return res;

	if (showTime)
		res.Format(_T("%d,%d,%d,%d,%d,%d,%d,%d"), mId, mNumber[0], mNumber[1], mNumber[2], mNumber[3], mNumber[4], mNumber[5], mNumber[6]);
	else
		res.Format(_T("%d,%d,%d,%d,%d,%d,%d"), mId, mNumber[0], mNumber[1], mNumber[2], mNumber[3], mNumber[4], mNumber[5], mNumber[6]);
	return res;
}

bool GroupBallNum::ChehckNumVaild()const
{
	time_t nowTime = time(NULL);
	tm tmNowTime;
	localtime_s(&tmNowTime, &nowTime);
	if (mId<14001 || mId>(tmNowTime.tm_year -100 + 1) * 1000)
		return false;
	
	for (uint8 i = 0; i < BALL_COUNT; ++i)
	{
		if (!VAILD_BALL_NUM(i, mNumber[i]))
			return false;
		
		if (i > 0 && i<BALL_COUNT - 1 && mNumber[i] <= mNumber[i - 1])
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
		sprintf_s(szOut, sizeof(szOut), "%d,%d,%d,%d,%d,%d,%d,%d,%d", mId, mNumber[0], mNumber[1], mNumber[2], mNumber[3], mNumber[4], mNumber[5], mNumber[6], time(NULL));
	else
		sprintf_s(szOut, sizeof(szOut), "%d,%d,%d,%d,%d,%d,%d,%d", mId, mNumber[0], mNumber[1], mNumber[2], mNumber[3], mNumber[4], mNumber[5], mNumber[6]);
	return std::string(szOut);
}

