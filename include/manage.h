#ifndef _FHKJEF_FDS_CAN_CaAttributeManage
#define _FHKJEF_FDS_CAN_CaAttributeManage

#include "define.h"
#include "cantools/rapidjson/document.h"
#include"cantools/tools.h"

#define MAX_LV_COUNT 7		//times lv 
#define MAX_DIFF_COUNT 5  //##diffcult##

class CaAttributeManage
{
	friend class CaLogicPool;
	friend class CaLogicCell;
	friend class CaObject;
protected:
	static CaAttributeManage* share();
	void update(const DECIMALS&);

	//## loading fish attribute by jason file @param file full path ##
	bool LoadAttributeJason(const char*);
	
	//##Calculate times for boject by it's id##
	uint16 GetObjectTimes(const uint8&);
	
	//##get object attribute by id##
	const CaAttribute* GetObjectAttribute(const uint8&);
	
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
	OLEVEL CalculateObjectLv(const uint16& timesVal); 
	inline const uint16& CheckTimes(uint16& timesVal){ if (timesVal>m_maxTimes)timesVal = m_maxTimes; return timesVal; }
	inline const uint16& GetHitCount(){ return m_hitCount; }
	inline const uint16& GetAwardCount(){ return m_awardCount; }
	inline const DECIMALS& GetProfitRate(){ return m_profitRate[m_curDifficult]; }

private:
	 ConfigManage();
	~ ConfigManage();

private:
	static ConfigManage* m_pConfig;
	uint16 m_lvArr[MAX_LV_COUNT];
	uint16 m_maxTimes;
	uint16 m_hitCount;
	uint16 m_awardCount;
	DECIMALS m_profitRate[MAX_DIFF_COUNT];

	uint8	m_curDifficult;
};
#endif
