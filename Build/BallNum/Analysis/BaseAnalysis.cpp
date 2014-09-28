#include "stdafx.h"
#include "BaseAnalysis.h"
#include "../MainDlgHandle.h"
#include "../GroupBallNum.h"
BaseAnalysis* BaseAnalysis::m_gSelf=NULL;
BaseAnalysis::BaseAnalysis() :m_minID(0), m_maxID(0)
{
}

BaseAnalysis::~BaseAnalysis()
{
}

BaseAnalysis* BaseAnalysis::share()
{
	if (!m_gSelf)
		m_gSelf = new BaseAnalysis;

	return m_gSelf;
}

void BaseAnalysis::AddOriginData(const BallNum& srcData)
{
	m_listData.push_back(srcData);
	LIST_BallNums::iterator itor_last = m_listData.end();
	
	uint8 shortId = srcData.mId / 1000;
	if (m_minID == 0)
		m_minID = shortId;

	if (m_minID > shortId)
		m_minID = shortId;
	else if (m_maxID < shortId)
		m_maxID = shortId;
		 
	MAP_LINSTINDEX::iterator itor = m_mapSectionIndex.find(shortId);
	if (itor == m_mapSectionIndex.end())
	{
		LISTINDEX newIndex;
		newIndex.mItor_end = itor_last--;
		newIndex.mItor_begin = itor_last;
		m_mapSectionIndex.insert(std::make_pair(shortId, newIndex));

		MAP_LINSTINDEX::iterator itor_before = m_mapSectionIndex.find(shortId - 1);
		if (itor_before != m_mapSectionIndex.end())
			itor_before->second.mItor_end = newIndex.mItor_begin;
	}
	else
	{
		//itor->second.mItor_end = itor_last;
	}
}

void BaseAnalysis::CalculateBallCount(const YearInfo& mYearInfo, bool isRed /*= true*/)
{
	uint32 numCount[33] = { 0 };
	uint8 begin(BallColor_Red), ends(BallColor_Red_Max);
	if (!isRed)
		begin = ends = BallColor_Blue;

	LISTINDEX mIndexInfo = CalculateListIndex(mYearInfo);
	if (!mIndexInfo.isOk)
		return;
	LIST_BallNums::iterator itor_begin = mIndexInfo.mItor_begin, itor_end = mIndexInfo.mItor_end;
	uint8 index(0);
	//uint32 nCount(0);
	for (; itor_begin != itor_end; ++itor_begin)
	{
		for (index = 0; index < BALL_COUNT; ++index)
		{
			if (index>=begin&&index<=ends)
				numCount[itor_begin->mNumber[index] - 1] += 1;
		}
	}

	char szTitle[32] = "";
	sprintf_s(szTitle, sizeof(szTitle), "%s ball Datas[%s].", isRed ? "Red" : "Blue", mYearInfo.GetStringInterval().c_str());
	ShowMainMessage::share()->InsertNumMgs(szTitle, numCount, MAX_BALL_NUM(ends));
}

void BaseAnalysis::AnBlueBallTrend(const YearInfo& mYearInfo)
{
	//std::list<int8> outs;
	int32 iPlus(0);
	char strText[64] = "";
	char strText2[64] = "";
	std::string strMsg;
	std::string strMsg2;

	LISTINDEX mIndexInfo = CalculateListIndex(mYearInfo);
	if (!mIndexInfo.isOk)
		return;
	LIST_BallNums::iterator itor_begin = mIndexInfo.mItor_begin, itor_end = mIndexInfo.mItor_end;

	uint8 index(0),iBallIndex(6), iFirstNum(itor_begin->mNumber[iBallIndex]), iLastVal(iFirstNum);
	int8  minusVal(0);
	
	for (++itor_begin; itor_begin != itor_end; ++itor_begin)
	{
		minusVal = itor_begin->mNumber[iBallIndex] - iLastVal;
		iLastVal = itor_begin->mNumber[iBallIndex];
		if (minusVal == 0)
		{
			strMsg.append(" 000");
			strMsg2.append(strText2);
		}
		else
		{
			iPlus += minusVal;
			if (minusVal > 0)
				sprintf_s(strText, sizeof(strText), " +%02d\0", minusVal);
			else
				sprintf_s(strText, sizeof(strText), "  -%02d\0", -minusVal);

			strMsg.append(strText);

			sprintf_s(strText2, sizeof(strText2), " %02d\0", iPlus);
			strMsg2.append(strText2);
		}
		
		if (++index >= 16)
		{
			strMsg.append("\n");
			strMsg2.append("\n");
			index = 0;
		}
	}
	
	sprintf_s(strText, sizeof(strText), "Plus val id(%s)first(%02d)offset(%d) :\n\0", mYearInfo.GetStringInterval().c_str(), iFirstNum, iPlus);
	strMsg.insert(0,strText);
	ShowMainMessage::share()->InsertMsg(strMsg);

	strMsg2.insert(0, "Help Data.\n");
	ShowMainMessage::share()->InsertMsg(strMsg2);
}

LISTINDEX BaseAnalysis::CalculateListIndex(const YearInfo& mYearInfo)
{
	LISTINDEX mlistLindex;
	if (mYearInfo.mSYear == 255)
	{
		mlistLindex.isOk = true;
		mlistLindex.mItor_begin = m_listData.begin();
		mlistLindex.mItor_end = m_listData.end();
	}
	else
	{
		uint8 beginID = max(m_minID, min(mYearInfo.mSYear, m_maxID));
		uint8 endID = beginID;
		if (mYearInfo.mCount>1)
			endID = max(m_minID, min(mYearInfo.EndYear(), m_maxID));

		if (beginID == 0 || endID == 0)
			return mlistLindex;

		MAP_LINSTINDEX::iterator itor_1 = m_mapSectionIndex.find(beginID);
		MAP_LINSTINDEX::iterator itor_2 = m_mapSectionIndex.find(endID);
		//assert(itor_1 != m_mapSectionIndex.end());
		//assert(itor_2 != m_mapSectionIndex.end());
		mlistLindex.isOk = true;
		mlistLindex.mItor_begin = itor_1->second.mItor_begin;
		mlistLindex.mItor_end = itor_2->second.mItor_end;
		return mlistLindex;
	}
	return mlistLindex;
}


