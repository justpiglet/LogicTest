#ifndef _FHKJEF_FDS_CAN_CALOGICFACTROY
#define _FHKJEF_FDS_CAN_CALOGICFACTROY
#include"publicpro.h"

enum  OBJECT_STATE
{
	OBJECT_STATE_NULL=0,
	OBJECT_STATE_CREATE,
	OBJECT_STATE_ACTIVITY,
	OBJECT_STATE_OUT,
	OBJECT_STATE_DEATH
};
//##object class##
class __declspec(DLL_EX_OR_IM)CaObject
{
	friend class ObjectManage;
public:
	CaObject(uint8 id = -1);
	virtual ~CaObject();
public:
	virtual uint16 ChangeObjectTimes(int16 times);
	virtual bool IsObjectActivity(){ return m_state > OBJECT_STATE_NULL&&m_state < OBJECT_STATE_DEATH; }
protected:
	virtual bool ResetDataById(uint8 id);

protected:
	CaAttribute* m_pAttbute;
	uint16 m_realtime;			//##result##
	uint16 m_buffertime;		//##buffer##
	DECIMALS m_posx;
	DECIMALS m_posy;
	uint8 m_state;
};

//##logic control class##
class __declspec(DLL_EX_OR_IM)ILogicPool
{
public:
	//##first step£¬Init LogicPool £¬param£º@1,Attribute Path.@2,pool count  ##
	virtual bool Init(char*,uint8)=0;
	
	//##need Cycle call ##
	virtual void update(DECIMALS) = 0;

	//##add score value over 0 is add else is minus##
	virtual void OperateScore(uint8,int32) = 0;
	
	//##Get current score##
	virtual SCORE GetCurScore(uint8) = 0;
	
	//##Reset game value##
	virtual void ResetGameValue()=0;
	
	//##calculate finnal result @1playerId,@2power@3objects@result object ##
	virtual bool CalculateResult(uint8, uint16, const std::vector<CaObject*>&, std::vector<CaObject*>&) = 0;

	//##calculate a times for object by it's id##
	virtual uint16 GetObjectTimes(uint8) = 0;

	//##call Destroy before quit game  ##
	virtual void Destroy() = 0;
	
	//##Object##
	virtual CaObject* CreateObject(uint8) = 0;
	//virtual void DestroyObject(CaObject*) = 0;
};
//##Get the LogicPool object ##
__declspec(DLL_EX_OR_IM)ILogicPool* CaLogicFactroyShare();

#endif
