#include "GobalConfig.h"
#include "Depend/cantools/tools.h"
//#include "stdafx.h"

CGobalConfig* CGobalConfig::m_gSelf=NULL;
CGobalConfig::CGobalConfig()
{
}


CGobalConfig::~CGobalConfig()
{
}

void CGobalConfig::CreateRandStr(uint8 iLen, char szOut[])
{
	char szTemp[2] = "";
	uint16 iRandVal(0);
	for (uint8 i = 0; i < iLen; ++i)
	{
		iRandVal = _CANNP_NAME::randoom::GetRandoom(0, 0xffff);
		
		szOut[i++] = iRandVal & 0x007f;
		if (i==iLen-1)
			break;
		szOut[i] = iRandVal >> 5;
	}
}

CGobalConfig* CGobalConfig::Share()
{
	if (!m_gSelf)
		m_gSelf = new CGobalConfig;

	return m_gSelf;
}


