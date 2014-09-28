#pragma once

#include <map>
#include <list>

typedef std::list<BallNum> LIST_BallNums;
struct LISTINDEX
{
	bool isOk;
	LIST_BallNums::iterator mItor_begin;
	LIST_BallNums::iterator mItor_end;
	LISTINDEX() :isOk(false)
	{
	}
};
typedef std::map<uint8, LISTINDEX> MAP_LINSTINDEX;
class BaseAnalysis
{
	friend class ManageDataBase;
public:
	static BaseAnalysis* share();

	void CalculateBallCount(uint8 shortId, uint8 count=1);
	void AnBlueBallTrend(uint8 shortId, uint8 count=1);
	LISTINDEX CalculateListIndex(uint8 beginId,uint8 count);
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