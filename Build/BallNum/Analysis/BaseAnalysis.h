#pragma once

#include <map>
#include <list>

typedef std::list<BallNum> LIST_BallNums;
typedef std::map<uint32, LIST_BallNums> MAP_BallNums;
class BaseAnalysis
{
public:
	BaseAnalysis* share();
private:
	BaseAnalysis();
	~BaseAnalysis();

private:
	static BaseAnalysis* m_gSelf;

	MAP_BallNums m_mapGroupNums;
};