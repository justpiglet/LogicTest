#include "stdafx.h"
#include "BaseAnalysis.h"
#include "../MainDlgHandle.h"
#include "../GroupBallNum.h"

#include "cantools/rapidjson/document.h"

BaseAnalysis* BaseAnalysis::m_gSelf=NULL;
BaseAnalysis::BaseAnalysis() :m_minID(0), m_maxID(0), m_bAddData(false)
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
	if (!m_bAddData)
		return;

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
		newIndex.mCount = 1;
		m_mapSectionIndex.insert(std::make_pair(shortId, newIndex));

		MAP_LINSTINDEX::iterator itor_before = m_mapSectionIndex.find(shortId - 1);
		if (itor_before != m_mapSectionIndex.end())
			itor_before->second.mItor_end = newIndex.mItor_begin;
	}
	else
	{
		itor->second.mCount=itor->second.mCount+1;
	}
	for (uint8 i = 0; i < BALL_COUNT; ++i)
		AnalysisBallNum(srcData.mId, srcData.mNumber[i], i <= BallColor_Red_Max);
}

bool BaseAnalysis::AnalysisBallNum(const uint16& id, const uint8& num, const bool& isRed)
{
	uint8 shortId = id / 1000;
	uint8 indexID = num;
	if (!isRed)
		indexID += COUNT_RED;
	--indexID;

	MAPGROUPINDEX* mapGroup = &m_NumIDIndex[indexID];
	MAPGROUPINDEX::iterator itor_index = mapGroup->find(shortId);
	if (itor_index == mapGroup->end())
	{
		LISTNUMINDEX mGroup;
		mapGroup->insert(std::make_pair(shortId, mGroup));
		itor_index = mapGroup->find(shortId);
	}

	uint16 lastID(0);
	LISTID* pListID = &m_arrNumID[indexID];
	if (!pListID->empty())
		lastID = pListID->back() / 1000;
		

	pListID->push_back(id);

	LISTID::iterator itor_listID_end = pListID->end();
	if (lastID == 0 || lastID != shortId) //firs data
	{
		itor_index->second.isOk = true;
		itor_index->second.mItor_end = itor_listID_end--;
		itor_index->second.mItor_begin = itor_listID_end;
		
		if (lastID != 0)
		{
			MAPGROUPINDEX::iterator itor_index_last = mapGroup->find(lastID);
			if (itor_index_last != mapGroup->end())
			{
				--itor_listID_end;
				itor_index_last->second.mItor_end = itor_listID_end;
			}	
		}
		
	}
	
	MAP_U8U16::iterator itor_16 = m_mapNumCount[indexID].find(shortId);
	if (itor_16 == m_mapNumCount[indexID].end())
		m_mapNumCount[indexID].insert(std::make_pair(shortId, 1));
	else
		itor_16->second = itor_16->second + 1;

	return true;
}

void BaseAnalysis::AddDataEnd()
{
	m_bAddData = false;
	m_mapOffset->clear();
	//offset
	MAPGROUPINDEX::iterator itor_GIndex;
	uint8 coutID(0), offsetI(0), countfor = COUNT_RED + COUNT_BULE;
	uint16 numID(0);

	//max disappear
	LISTID::iterator itor_index;
	MAPGROUPINDEX::iterator itor_groupI;
	uint16 uTemp(0), uMax(0), lastVal(0),offsetVal(0);
	for (uint8 istart(m_minID) ,i(0); istart <= m_maxID; ++istart)
	{
		if (istart>m_minID)//offset
			coutID = m_mapSectionIndex.find(istart - 1)->second.mCount;

		for (uint8 i = 0; i < countfor; ++i)
		{

			if (istart > m_minID)//offset
			{
				itor_GIndex = m_NumIDIndex[i].find(istart - 1);
				if (itor_GIndex != m_NumIDIndex[i].end())
					numID = (*(itor_GIndex->second.mItor_end)) % 1000;
				else
					numID = 0;

				if (m_mapOffset[i].empty())
					m_mapOffset[i].insert(std::make_pair(m_minID, 0));

				offsetVal = 1 + coutID - numID;
				m_mapOffset[i].insert(std::make_pair(istart, offsetVal));
			}
			else
				offsetVal = 0;

			itor_groupI = m_NumIDIndex[i].find(istart);
			if (itor_groupI == m_NumIDIndex[i].end() || !itor_groupI->second.isOk)
				continue;

			itor_index = itor_groupI->second.mItor_begin;
			uTemp = *(itor_index++);
			//offsetVal = 0; //Ignore
			uMax = offsetVal + uint16(uTemp / 1000);
			for (; itor_index != itor_groupI->second.mItor_end; ++itor_index)
			{
				lastVal = (*itor_index) - uTemp;
				uTemp = (*itor_index);
				if (lastVal > uMax)
					uMax = lastVal;
			}

			m_mapMaxDisAppear[i].insert(std::make_pair(istart, uMax));
		}
	}
}

void BaseAnalysis::CalculateBallCount(const YearInfo& mYearInfo, bool isRed /*= true*/)
{
	uint32 numCount[COUNT_RED] = { 0 };
	uint32 numMaxFrequency[COUNT_RED] = { 0 };
	uint32 numCurFrequency[COUNT_RED] = { 0 };
	uint32 numAvg[COUNT_RED] = { 0 };
	uint8   rate[COUNT_RED] = { 0 }; //0-50% 0-AVG 51-100%avg-max 100+% >max

	uint8 begin(BallColor_Red), ends(BallColor_Red_Max);
	if (!isRed)
		begin = ends = BallColor_Blue;

	LISTINDEX mIndexInfo = CalculateListIndex(mYearInfo);
	if (!mIndexInfo.isOk)
		return;

	uint8 istart = mYearInfo.mSYear;
	if (istart > START_ID &&istart<=m_maxID)
	{
		MAPGROUPINDEX::iterator itor_index;
		uint8 coutID = m_mapSectionIndex.find(istart - 1)->second.mCount;
		uint16 numID(0);
		uint8 offsetI(0),countfor = F_COUNT_NUM(isRed);
		if (!isRed)
			offsetI = COUNT_RED;
		
		for (uint8 i = 0; i < countfor; ++i)
		{
			numCurFrequency[i] = GetCurOffset(i + offsetI, istart);
			if (numCurFrequency[i] == -1)
				numCurFrequency[i] = 0;
		}	
	}

	LIST_BallNums::iterator itor_begin = mIndexInfo.mItor_begin, itor_end = mIndexInfo.mItor_end;
	uint8 index(0),i(0),indexVal(0);
	if (isRed)
	{
		for (; itor_begin != itor_end; ++itor_begin)
		{
			for (index = BallColor_Red; index <= BallColor_Red_Max; ++index)
			{
				indexVal = itor_begin->mNumber[index] - 1;
				numCount[indexVal] += 1;
				numCurFrequency[indexVal] = -1;
			}

			for (i = 0; i < 33; ++i)
			{
				++numCurFrequency[i];
				if (numMaxFrequency[i] < numCurFrequency[i])
					numMaxFrequency[i] = numCurFrequency[i];
			}
		}
	}
	else
	{
		for (; itor_begin != itor_end; ++itor_begin)
		{
			
			indexVal = itor_begin->mNumber[BallColor_Blue] - 1;
			numCurFrequency[indexVal] = 0;
			numCount[indexVal] += 1;

			for (i = 0; i < 16; ++i)
			{
				if (indexVal == i)
				{
					numCurFrequency[i] = 0;
					continue;
				}

				++numCurFrequency[i];
				if (numMaxFrequency[i] < numCurFrequency[i])
					numMaxFrequency[i] = numCurFrequency[i];
			}
		}
			
	}
	uint32 count = mIndexInfo.mCount;
	uint32 iForCount = isRed ? 33 : 16;
	for (i = 0; i < iForCount; ++i)
	{
		if (numCount[i] == 0 || numMaxFrequency[i] == 0)
		{
			rate[i] = 0;
			numAvg[i] = 0;
		}
		else
		{
			numAvg[i] = count / numCount[i];
			if (numCurFrequency[i] < numAvg[i])
				rate[i] = (numCurFrequency[i]*100) / numAvg[i];
			else
				rate[i] = 100+(numCurFrequency[i]*100) / numMaxFrequency[i];
		}
	}

	
	char szTitle[512] = "";
	sprintf_s(szTitle, sizeof(szTitle), "ID[%s] (%s) count(%d).\n[ID][SUM][AVG][MAX][CUR][RATE] \n", mYearInfo.GetStringInterval().c_str(), isRed ? "Red" : "Blue", count);
	std::string str(szTitle);
	
	
	for (i = 0; i < iForCount; ++i)
	{
		sprintf_s(szTitle, sizeof(szTitle), "%02d:%04d  %04d  %04d  %04d %03d \n", i + 1, numCount[i], numAvg[i], numMaxFrequency[i], numCurFrequency[i],rate[i]);
		str.append(szTitle);
	}

	ShowMainMessage::share()->InsertMsg(str);
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
	
	sprintf_s(strText, sizeof(strText), "ID[%s] Plus val first(%02d)offset(%d) :\n\0", mYearInfo.GetStringInterval().c_str(), iFirstNum, iPlus);
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
		mlistLindex.mCount = m_listData.size();
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

		for (MAP_LINSTINDEX::iterator itor11 = itor_1; itor11 != itor_2; ++itor11)
			mlistLindex.mCount += itor11->second.mCount;
		mlistLindex.mCount += itor_2->second.mCount;
		return mlistLindex;
	}
	return mlistLindex;
}

void BaseAnalysis::NumAppearance(const YearInfo& mYearInfo,uint8 num, bool isRed /*= true*/)
{
	LISTINDEX mIndexInfo = CalculateListIndex(mYearInfo);
	if (!mIndexInfo.isOk)
		return;
	LIST_BallNums::iterator itor_Index = mIndexInfo.mItor_begin, itor_end = mIndexInfo.mItor_end;
	std::list<uint16> listOut;
	uint16 uCount(0);
	uint32 amount(0);
	for (; itor_Index != itor_end; ++itor_Index)
	{
		uCount += 1;
		amount += 1;
		if (GroupBallNum::IsNumAppear(*itor_Index, num, isRed))
		{
			listOut.push_back(uCount);
			uCount = 0;
		}	
	}
	char strText[256] = "";
	sprintf_s(strText, sizeof(strText), "ID[%s],Num(%s:%02d),Amount(%d,%d) :\n\0", mYearInfo.GetStringInterval().c_str(), isRed ? "Red" : "Blue", num, amount, listOut.size());
	std::string strMsg(strText);

	if (!listOut.empty())
	{
		std::list<uint16>::iterator itor_u16 = listOut.begin(), itor_endu16 = listOut.end();
		uint16 index(0);
		for (; itor_u16 != itor_endu16; ++itor_u16, ++index)
		{
			if (index==0)
				sprintf_s(strText, sizeof(strText), "%03d\0", *itor_u16);
			else if(index%15 == 0)
				sprintf_s(strText, sizeof(strText), "\n%03d\0", *itor_u16);
			else
				sprintf_s(strText, sizeof(strText), "  %03d\0", *itor_u16);
				
			strMsg.append(strText);
		}
	}
	ShowMainMessage::share()->InsertMsg(strMsg);
}

void BaseAnalysis::WriteNumAppear()
{
	MAPID mapData;



	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value arrNum(rapidjson::kArrayType);
	//rapidjson::Value object(rapidjson::kObjectType);
	//document.AddMember("object", objects);
	arrNum.PushBack(12, allocator);

}

uint16 BaseAnalysis::GetMaxDisAppear(const uint8& numIndex, const uint16& id)
{
	if (numIndex >= COUNT_RED + COUNT_BULE)
		return 0;

	MAP_U8U16::iterator itor = m_mapMaxDisAppear[numIndex].find(id);
	if (itor != m_mapMaxDisAppear[numIndex].end())
		return itor->second;
	else
		return 0;
}

uint16 BaseAnalysis::GetCurOffset(const uint8& numIndex, const uint16& id)
{
	if (numIndex >= COUNT_RED + COUNT_BULE)
		return 0;

	MAP_U8U16::iterator itor = m_mapOffset[numIndex].find(id);
	if (itor != m_mapOffset[numIndex].end())
		return itor->second;
	else
		return 0;
}





