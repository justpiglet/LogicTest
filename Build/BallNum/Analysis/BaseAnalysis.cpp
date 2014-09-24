#include "stdafx.h"
#include "BaseAnalysis.h"
#include "../MainDlgHandle.h"
#include "../GroupBallNum.h"
BaseAnalysis* BaseAnalysis::m_gSelf=NULL;
BaseAnalysis::BaseAnalysis() 
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
	uint8 shortId = srcData.mId / 1000;
	MAP_BallNums::iterator itor = m_mapData.find(shortId);
	if (itor == m_mapData.end())
	{
		LIST_BallNums newGroup;
		newGroup.push_back(srcData);
		m_mapData.insert(std::make_pair(shortId, newGroup));
	}
	else
	{
		itor->second.push_back(srcData);
	}
}

void BaseAnalysis::CalculateBallCount(uint8 shortId)
{
	uint32 redCount[33] = { 0 };
	uint32 blueCount[16] = { 0 };
	MAP_BallNums::iterator itor = m_mapData.find(shortId);
	if (itor == m_mapData.end())
		return;
	LIST_BallNums& groupData = itor->second;
	LIST_BallNums::iterator itor_begin = groupData.begin(), itor_end = groupData.end();
	uint8 index(0);
	for (; itor_begin != itor_end; ++itor_begin)
	{
		for (index = 0; index < BALL_COUNT; ++index)
		{
			if (index > BallColor_Red_Max)
			{
				blueCount[itor_begin->mNumber[index] - 1] += 1;
			}
			else
			{
				redCount[itor_begin->mNumber[index] - 1] += 1;
			}
		}
	}

	ShowMainMessage::share()->InsertNumMgs("Red ball Datas.", redCount, MAX_BALL_NUM(BallColor_Red));
	ShowMainMessage::share()->InsertNumMgs("Bue ball Datas.", blueCount, MAX_BALL_NUM(BallColor_Blue));
}