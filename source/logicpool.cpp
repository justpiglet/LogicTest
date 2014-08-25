#include "logicpool.h"
#include "tools.h"
#include "objectManage.h"

# define PLAYER_TABLE_NAME "playerInfo"

enum STATE_VAL
{
	STATE_NULL			= 0,
	STATE_NOT_AUTHORIZE	= 1,
	STATE_EXPIRED		= 2,

	STATE_OK			= 128
};

CaLogicPool* CaLogicPool::m_gLogicPool = nullptr;
HANDLE CaLogicPool::m_hThread = NULL;
HANDLE CaLogicPool::m_event = NULL;
volatile bool CaLogicPool::m_isRun = false;
std::mutex CaLogicPool::m_Mutex;

DWORD WINAPI CaLogicPool::SaveDataThread(LPVOID lp)
{
	while (m_isRun)
	{
		if (WaitForSingleObject(m_event, INFINITE) == WAIT_OBJECT_0)
		{
			ResetEvent(m_event);
			CaLogicPool::caShare()->SavePoolData();
		}
	}

	return 0;
}


CaLogicPool::CaLogicPool()
	:m_State(STATE_NULL), m_CellCount(0), m_Profit(0),m_saveTime(0.0f)
{
	if (m_hThread == NULL)
	{
		m_event = CreateEvent(NULL, false, false, NULL);
		m_hThread = CreateThread(NULL, 0, &CaLogicPool::SaveDataThread, NULL, 0/*CREATE_SUSPENDED*/, NULL);
		m_isRun = true;
	}
}

CaLogicPool::~CaLogicPool()
{
	m_gLogicPool = nullptr;
	m_State = STATE_NULL;
	CloseHandle(m_hThread);
	CloseHandle(m_event);
}
CaLogicPool* CaLogicPool::caShare()
{
	if (!m_gLogicPool)
		m_gLogicPool = new CaLogicPool();

	return m_gLogicPool;
}

bool CaLogicPool::Check(/**/)
{
	//check Permission  calculate result by param

	//test
	m_State = STATE_OK;

	char pwd[] = "!#$%^GRG&*%#$@$#WFfsdfsdf#%32";
	std::string cpuid = _CANNP_NAME::encrypt::CPUID2();
	cpuid.append(_CANNP_NAME::encrypt::MAC_ETHERNET());
	std::string aa = _CANNP_NAME::encrypt::EncryptMD5(cpuid.c_str(), cpuid.length());
	std::string aesa = _CANNP_NAME::encrypt::EncryptAES(aa.c_str(), pwd);
	std::string aesb = _CANNP_NAME::encrypt::EncryptAES(aa.c_str() + 16, pwd);

	//std::string aesa1 = _CANNP_NAME::DecryptAES(aesa.c_str(), pwd);
	//std::string aesb1 = _CANNP_NAME::DecryptAES(aesb.c_str(), pwd);
	//aesa1.append(aesb1);

	Point start(4*1.414213562373095f, 0.0f);
	Point endpos(0.0f, 4*1.414213562373095f);
	Point centerPos(0.0f, 0.0f);
	DECIMALS r(4);
	Point nr1(-99.9f,-99.9f), nr2(-99.9f,-99.9f);
	uint8 nresult=_CANNP_NAME::lineIntersection::LineInterCirclePos(start,endpos,centerPos,r,nr1,nr2);
	return m_State == STATE_OK;
}

void CaLogicPool::Destroy()
{
	m_isRun = false;
	Sleep(50);
	if (m_gLogicPool)
	{
		delete m_gLogicPool;
		CaAttributeManage::share()->DestroyManage();
	}
}

bool CaLogicPool::Init(char* folderPath, uint8 poolCount)
{
	if (!Check() || poolCount > MAX_POOLCELL_COUNT)
		return false;
	m_CellCount = poolCount;
	m_pLogicCells = new CaLogicCell[m_CellCount];
	char szFilePath[64]="";
	sprintf_s(szFilePath,sizeof(szFilePath),"%s/config.json",folderPath);
	ConfigManage::share()->LoadData(szFilePath);
	sprintf_s(szFilePath,sizeof(szFilePath),"%s/attribute.json",folderPath);
	CaAttributeManage::share()->LoadAttributeJason(szFilePath);
	m_pDataBase->Create("../../resource/data.db","");
	return true;
}
uint16 CaLogicPool::GetObjectTimes(uint8 id)
{
	return CaAttributeManage::share()->GetObjectTimes(id);
}

void CaLogicPool::OperateScore(uint8 playerId,int32 score)
{
	if (playerId < m_CellCount)
		m_pLogicCells[playerId].OperateScore(score);
}

SCORE CaLogicPool::GetCurScore(uint8 playerId)
{
	if (playerId < m_CellCount)
		return m_pLogicCells[playerId].GetCurScore();
	else
		return 0;
}

bool CaLogicPool::CalculateResult(uint8 playerId, uint16 power, const vector<CaObject*>& objects, vector<CaObject*>& result)
{
	if (playerId < m_CellCount)
		return m_pLogicCells[playerId].CalculateResult(power,objects,result);
	else
		return false;
}

void CaLogicPool::ResetGameValue()
{
	for (int32 i = 0; i < m_CellCount; ++i)
		m_pLogicCells[i].ResetGameValue();
}

void CaLogicPool::update(DECIMALS ft)
{
	if (m_saveTime > 3.0f)
	{
		m_saveTime = 0.0f;
		SetEvent(m_event);
	}
	else
		m_saveTime = m_saveTime + ft;

	CaAttributeManage::share()->update(ft);
}

void CaLogicPool::SavePoolData()
{
	//m_Mutex.lock();

	char strSql[128] = "";
	const SaveScore* pData = NULL;
	for (int i = 0; i < m_CellCount; ++i)
	{
		if (m_pLogicCells[i].IsNeedSave())
		{
			memset(strSql, 0, sizeof(strSql));
			pData = m_pLogicCells[i].GetSaveScore();
			sprintf_s(strSql, sizeof(strSql), "update %s set score=%d,profit=%d,waterVal=%d where id=%d", PLAYER_TABLE_NAME, pData->score,pData->profit,pData->waterVal,i);
		}
	}




	//m_Mutex.unlock();
}

CaObject* CaLogicPool::CreateObject(uint8 id)
{
	return ObjectManage::share()->CreateObject(id);
}

// void CaLogicPool::DestroyObject(CaObject* object)
// {
// 	ObjectManage::share()->DestroyObject(object);
// }

