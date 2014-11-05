#ifndef fdgjfdljgld_Operate_h
#define fdgjfdljgld_Operate_h

#include "base/basedefine.h"

enum EOpSatus
{
	EOpSatus_NULL=0,
	EOpSatus_Logoin,

};

__interface IMainDlgHandle
{
	
};

class COperate
{
	typedef void (COperate::*func)();

public:
	COperate();
	~COperate();
	
	void SetMainDlgHandle(IMainDlgHandle* pHandle){ m_pHandle = pHandle; }
	uint8 GetStatus(){ return m_status; }
	void UserOperate(const uint8&);
private:
	IMainDlgHandle* m_pHandle;
	EOpSatus m_status;


};

#endif
