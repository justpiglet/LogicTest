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

void CGobalConfig::CreateRandStr(uint8 iLen, std::string& strOut)
{
	char szTemp[2] = "";
	uint16 iRandVal(0);
	for (uint8 i = 0; i < iLen; ++i)
	{
		iRandVal = _CANNP_NAME::randoom::GetRandoom(0, 0xffff);
		
		szTemp[0] = iRandVal & 0x007f;
		strOut.append(szTemp,1);
		++i;
		if (i==iLen-1)
			break;
		szTemp[0] = iRandVal >> 5;
		strOut.append(szTemp,1);
	}
}

CGobalConfig* CGobalConfig::Share()
{
	if (!m_gSelf)
		m_gSelf = new CGobalConfig;

	return m_gSelf;
}


