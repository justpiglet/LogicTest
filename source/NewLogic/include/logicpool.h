
#ifndef _FHKJEF_FDS_CAN_CALOGICPOOL
#define _FHKJEF_FDS_CAN_CALOGICPOOL
#include "define.h"
#include "game/publicpro.h"


#include "manage.h"
#include "logiccell.h"
#include <mutex>
#define SQLITE_OUTSIDE
#include "depend/sqlitedb/SqliteDatabase.h"

class  CaLogicPool :public ILogicPool
{
	friend class CaLogicCell;
public:
	~CaLogicPool();
	static CaLogicPool* caShare();
	bool Check();

public:
	virtual void update(const DECIMALS&);
	virtual void Destroy();
	virtual bool Init(const char*, const uint8&);
	virtual uint16 GetObjectTimes(const uint8&);
	virtual void OperateScore(const uint8&, const int32&);
	virtual SCORE GetCurScore(const uint8&);
	virtual bool Onfire(const uint8& , uint16&);
	virtual bool CalculateResult(const uint8&, const uint16&, const VEC_CAOBJECT&, VEC_CAOBJECT&);
	virtual bool CalculateResult(const uint8&, const uint16&, const CaObject*);
	virtual void ResetGameValue();
	virtual CaObject* CreateObject(const uint8&);
	//virtual void DestroyObject(CaObject*);
protected:
	void AddProfit(const int32& score){ if (score > 0)m_Profit = m_Profit + score; }
private:
	CaLogicPool();
	static DWORD WINAPI SaveDataThread(LPVOID);
	void SavePoolData();
private:
	static CaLogicPool* m_gLogicPool;
	uint8 m_State; 
	CaLogicCell* m_pLogicCells;
	uint8 m_CellCount;
	PROFIT m_Profit;

	DECIMALS m_saveTime;
	CSqliteDatabase* m_pDataBase;

	static HANDLE m_hThread;
	static HANDLE m_event;
	static std::mutex m_Mutex;
	static volatile bool m_isRun;
};

#endif // !_FHKJEF_FDS_CAN_CALOGICPOOL