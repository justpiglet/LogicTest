#pragma once

#include <map>
#include <list>

typedef std::list<BallNum> LIST_BallNums;
typedef std::map<uint8, LIST_BallNums> MAP_BallNums;
class BaseAnalysis
{
	friend class ManageDataBase;
public:
	static BaseAnalysis* share();

	void CalculateBallCount(uint8 shortId);
	void AnBlueBallTrend(uint8 shortId);
private:
	BaseAnalysis();
	~BaseAnalysis();
protected:
	void AddOriginData(const BallNum& );
private:
	static BaseAnalysis* m_gSelf;

	MAP_BallNums m_mapData;
};