#pragma once
#include "GroupBallNum.h"
#include <map>
#include <list>

typedef std::list<uint16> LISTID;
typedef	std::map<uint8, LISTID> MAPID;
typedef std::list<BallNum> LIST_BallNums;
struct LISTINDEX
{
	bool isOk;
	LIST_BallNums::iterator mItor_begin;
	LIST_BallNums::iterator mItor_end;
	uint32 mCount;
	LISTINDEX() :isOk(false), mCount(0)
	{
	}
};
struct LISTNUMINDEX
{
	bool isOk;
	LISTID::iterator mItor_begin;
	LISTID::iterator mItor_end;
	LISTNUMINDEX() :isOk(false)
	{
	}
};
typedef std::map<uint8,LISTNUMINDEX> MAPGROUPINDEX;

typedef std::map<uint8, LISTINDEX> MAP_LINSTINDEX;
typedef std::map<uint8, uint16> MAP_U8U16;
class BaseAnalysis
{
	friend class ManageDataBase;
public:
	static BaseAnalysis* share();

	void CalculateBallCount(const YearInfo&,bool isRed=true);
	void NumAppearance(const YearInfo&,uint8 , bool isRed = true);
	void AnBlueBallTrend(const YearInfo&);
	LISTINDEX CalculateListIndex(const YearInfo&);
	
	uint16 GetCurOffset(const uint8& numIndex, const uint16& id);
	uint16 GetMaxDisAppear(const uint8& numIndex,const uint16& id);

	inline uint8 GetMinID(){ return m_minID; }
	inline uint8 GetMaxID(){ return m_maxID; }

	void WriteNumAppear();
private:
	BaseAnalysis();
	~BaseAnalysis();
protected:
	void AddDataBegin(){m_bAddData = true;}
	//the data must sord  id ASC
	void AddOriginData(const BallNum& );

	void AddDataEnd();
private:
	bool AnalysisBallNum(const uint16&,const uint8&,const bool&);
private:
	bool m_bAddData;

	static BaseAnalysis* m_gSelf;

	LIST_BallNums m_listData;
	MAP_LINSTINDEX m_mapSectionIndex;
	
	uint8 m_minID;
	uint8 m_maxID;

	LISTID m_arrNumID[COUNT_RED + COUNT_BULE];
	MAPGROUPINDEX m_NumIDIndex[COUNT_RED + COUNT_BULE];

	MAP_U8U16 m_mapOffset[COUNT_RED + COUNT_BULE];
	MAP_U8U16 m_mapMaxDisAppear[COUNT_RED + COUNT_BULE];
	MAP_U8U16 m_mapNumCount[COUNT_RED + COUNT_BULE];
};