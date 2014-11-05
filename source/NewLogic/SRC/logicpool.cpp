#include "logicpool.h"
#include "depend/cantools/tools.h"
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
	std::string cpuid,strMac;
	_CANNP_NAME::encrypt::CPUID2(cpuid);
	_CANNP_NAME::encrypt::MAC_ETHERNET(strMac);
	cpuid.append(strMac);
	std::string strMd5,strAes1,strAes2;
	_CANNP_NAME::encrypt::EncryptMD5(cpuid.c_str(), cpuid.length(), strMd5);
	_CANNP_NAME::encrypt::EncryptAES(strMd5.c_str(), pwd, strAes1);
	_CANNP_NAME::encrypt::EncryptAES(strMd5.c_str() + 16, pwd, strAes2);
	strAes1.append(strAes2);
	//std::string aesa1 = _CANNP_NAME::encrypt::DecryptAES(strAes1.c_str(), pwd);
	//std::string aesb1 = _CANNP_NAME::encrypt::DecryptAES(strAes1.c_str() + 16, pwd);
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

bool CaLogicPool::Init(const char* folderPath, const uint8& poolCount)
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
uint16 CaLogicPool::GetObjectTimes(const uint8& id)
{
	return CaAttributeManage::share()->GetObjectTimes(id);
}

void CaLogicPool::OperateScore(const uint8& id, const int32& score)
{
	if (id < m_CellCount)
		m_pLogicCells[id].OperateScore(score);
}

SCORE CaLogicPool::GetCurScore(const uint8& id)
{
	if (id < m_CellCount)
		return m_pLogicCells[id].GetCurScore();
	else
		return 0;
}

bool CaLogicPool::CalculateResult(const uint8& id, const uint16& power, const VEC_CAOBJECT& objects, VEC_CAOBJECT& result)
{
	if (power <= 0 || objects.size() <= 0)
		return false;

	if (id < m_CellCount)
		return m_pLogicCells[id].CalculateResult(power, objects, result);
	else
		return false;
}

bool CaLogicPool::CalculateResult(const uint8& id, const uint16& power, const CaObject* pObject)
{
	if (power <= 0 || !pObject)
		return false;

	if (id < m_CellCount)
		return m_pLogicCells[id].CalculateResult(power, pObject);
	else
		return false;
}

void CaLogicPool::ResetGameValue()
{
	for (int32 i = 0; i < m_CellCount; ++i)
		m_pLogicCells[i].ResetGameValue();
}

void CaLogicPool::update(const DECIMALS& ft)
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

CaObject* CaLogicPool::CreateObject(const uint8& id)
{
	return ObjectManage::share()->CreateObject(id);
}

bool CaLogicPool::Onfire(const uint8& id, uint16& power)
{
	if (power <= 0 )
		return false;

	if (id < m_CellCount)
		return m_pLogicCells[id].Onfire(power);
	else
		return false;
}

// void CaLogicPool::DestroyObject(CaObject* object)
// {
// 	ObjectManage::share()->DestroyObject(object);
// }

