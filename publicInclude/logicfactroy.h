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
	friend class CaLogicCell;
public:
	CaObject(uint8 id = -1);
	virtual ~CaObject();
public:
	virtual uint16 ChangeObjectTimes(int16);
	virtual bool IsObjectActivity() const;
	virtual const uint16& GetAwardRate()const;
	virtual uint16 GetObjectTimes()const;
protected:
	virtual bool ResetDataById(uint8);
private:
	virtual void AdjustAwardRate();
protected:
	CaAttribute* m_pAttbute;
	uint16 m_realtime;			//##result##
	uint16 m_buffertime;		//##buffer##
	uint16 m_awardRate;		//award rate by m_realtime 0-10000
	DECIMALS m_posx;			//pos
	DECIMALS m_posy;			//pos
	uint8 m_state;				//OBJECT_STATE
	uint8 m_lv;					//OLEVEL
};

//##logic control class##
class __declspec(DLL_EX_OR_IM)ILogicPool
{
public:
	//##first step£¬Init LogicPool £¬param£º@1,Attribute Path.@2,pool count  ##
	virtual bool Init(const char*, const uint8&) = 0;
	
	//##need Cycle call ##
	virtual void update(const DECIMALS&) = 0;

	//##add score value over 0 is add else is minus##
	virtual void OperateScore(const uint8&,const int32&) = 0;
	
	//##Get current score##
	virtual SCORE GetCurScore(const uint8&) = 0;
	
	//##Reset game value##
	virtual void ResetGameValue()=0;
	
	virtual bool Onfire(const uint8&) = 0;

	//##calculate finnal result @1playerId,@2power@3objects@result object ##
	virtual bool CalculateResult(const uint8&, const uint16&, const std::vector<CaObject*>&, std::vector<CaObject*>&) = 0;
	virtual bool CalculateResult(const uint8&, const uint16&, const CaObject*) = 0;

	//##calculate a times for object by it's id##
	virtual uint16 GetObjectTimes(const uint8&) = 0;

	//##call Destroy before quit game  ##
	virtual void Destroy() = 0;
	
	//##Object##
	virtual CaObject* CreateObject(const uint8&) = 0;
	//virtual void DestroyObject(CaObject*) = 0;
};
//##Get the LogicPool object ##
__declspec(DLL_EX_OR_IM)ILogicPool* CaLogicFactroyShare();

#endif
