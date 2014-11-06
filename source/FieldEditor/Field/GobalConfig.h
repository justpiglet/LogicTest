#ifndef fdgjfdljgld_GobalConfig_h
#define fdgjfdljgld_GobalConfig_h
#include "base/basedefine.h"
#include <string>

class CGobalConfig
{
public:
	static CGobalConfig* Share();
	void CreateRandStr(uint8 iLen, char szOut[]);
	
private:
	CGobalConfig();
	~CGobalConfig();

private:
	static CGobalConfig* m_gSelf;
};

#endif
