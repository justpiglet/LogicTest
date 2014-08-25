#ifndef _FHKJEF_FDS_CAN_CaAttributeManage
#define _FHKJEF_FDS_CAN_CaAttributeManage

#include "define.h"
#include "cantools/rapidjson/document.h"
#include"cantools/tools.h"

#define MAX_LV_COUNT 7

class CaAttributeManage
{
	friend class CaLogicPool;
	friend class CaLogicCell;
	friend class CaObject;
protected:
	static CaAttributeManage* share();
	void update(DECIMALS);

	//## loading fish attribute by jason file @param file full path ##
	bool LoadAttributeJason(char*);
	
	//##Calculate times for boject by it's id##
	uint16 GetObjectTimes(uint8);
	
	//##get object attribute by id##
	const CaAttribute* GetObjectAttribute(uint8);
	
	//##Destroy##
	void DestroyManage();
private:
	CaAttributeManage();
	~CaAttributeManage();

	void WriteExample();

private:
	static CaAttributeManage* m_gpManage;
	CaAttribute* m_pAttributeArr;
	uint8 m_attCount;
};
//////////////////////////////////////////////////////////////////////////
class  ConfigManage
{
public:
	static ConfigManage* share();
	bool LoadData(const char* filepath);
	OLEVEL CalculateObjectLv(uint16 timesVal); 
	inline uint16 CheckTimes(uint16 timesVal){if (timesVal>m_maxTimes)timesVal=m_maxTimes;return timesVal;}
private:
	 ConfigManage();
	~ ConfigManage();

private:
	static ConfigManage* m_pConfig;
	uint16 m_lvArr[MAX_LV_COUNT];
	uint16 m_maxTimes;
};
#endif
