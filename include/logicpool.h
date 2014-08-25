
#ifndef _FHKJEF_FDS_CAN_CALOGICPOOL
#define _FHKJEF_FDS_CAN_CALOGICPOOL
#include "define.h"
#include"publicpro.h"


#include "manage.h"
#include "logiccell.h"
#include <mutex>
#define SQLITE_OUTSIDE
#include "sqlitedb/SqliteDatabase.h"

class  CaLogicPool :public ILogicPool
{
	friend class CaLogicCell;
public:
	~CaLogicPool();
	static CaLogicPool* caShare();
	bool Check();

public:
	virtual void update(DECIMALS);
	virtual void Destroy();
	virtual bool Init(char*, uint8);
	virtual uint16 GetObjectTimes(uint8);
	virtual void OperateScore(uint8,int32);
	virtual SCORE GetCurScore(uint8);
	virtual bool CalculateResult(uint8 , uint16 ,const vector<CaObject*>& , vector<CaObject*>& );
	virtual void ResetGameValue();
	virtual CaObject* CreateObject(uint8);
	//virtual void DestroyObject(CaObject*);
protected:
	void AddProfit(int32 score){ if (score > 0)m_Profit = m_Profit + score; }
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