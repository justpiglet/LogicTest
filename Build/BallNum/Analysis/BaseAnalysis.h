#pragma once

#include <map>
#include <list>

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
typedef std::map<uint8, LISTINDEX> MAP_LINSTINDEX;
class BaseAnalysis
{
	friend class ManageDataBase;
public:
	static BaseAnalysis* share();

	void CalculateBallCount(const YearInfo&,bool isRed=true);
	void NumAppearance(const YearInfo&,uint8 , bool isRed = true);
	void AnBlueBallTrend(const YearInfo&);
	LISTINDEX CalculateListIndex(const YearInfo&);
	
	inline uint8 GetMinID(){ return m_minID; }
	inline uint8 GetMaxID(){ return m_maxID; }
private:
	BaseAnalysis();
	~BaseAnalysis();
protected:
	void AddOriginData(const BallNum& );
private:
	static BaseAnalysis* m_gSelf;

	LIST_BallNums m_listData;
	MAP_LINSTINDEX m_mapSectionIndex;

	uint8 m_minID;
	uint8 m_maxID;
};