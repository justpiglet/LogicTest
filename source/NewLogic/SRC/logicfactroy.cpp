#include "logicfactroy.h"
#include "logicpool.h"

ILogicPool* CaLogicFactroyShare()
{
	CaLogicPool* pp = CaLogicPool::caShare();
	if (pp)
		return dynamic_cast<ILogicPool*>(pp);
	else
		return NULL;
}


CaObject::CaObject(uint8 id/*=-1*/) 
	: m_pAttbute(NULL), m_realtime(0), m_buffertime(0)
	, m_posx(0.0f), m_posy(0.0f), m_state(OBJECT_STATE_NULL)
	, m_lv(OLEVEL_ADJUST_LOW), m_awardRate(0)
{
	ResetDataById(id);
}

CaObject::~CaObject()
{

}

bool CaObject::ResetDataById(uint8 id)
{
	if (id > MAX_OBJECT_ID)
		return false;

	if (m_state > OBJECT_STATE_NULL&&m_state < OBJECT_STATE_DEATH)
		return false;

	m_pAttbute == CaAttributeManage::share()->GetObjectAttribute(id);
	m_buffertime = CaAttributeManage::share()->GetObjectTimes(id);
	m_realtime = m_buffertime;
	m_lv = ConfigManage::share()->CalculateObjectLv(m_realtime);
	
	AdjustAwardRate();
	return m_realtime > 0;
}

uint16 CaObject::ChangeObjectTimes(int16 times)
{
	if (m_pAttbute&&times != 0)
	{
		bool isOK(false);
		if (TIMES_TYPE_CHANGE_ALL == m_pAttbute->type)
			isOK = true;
		else if (TIMES_TYPE_CHANGE_ADD == m_pAttbute->type && times > 0)
			isOK = true;
		else if (TIMES_TYPE_CHANGE_MINUS == m_pAttbute->type && times < 0)
			isOK = true;

		if (isOK)
			m_buffertime = m_buffertime + times;

		uint16 ntemp(m_buffertime);
		if (m_buffertime < m_pAttbute->timesArr[0])
		{
			m_buffertime = m_pAttbute->timesArr[0];
			ntemp = m_buffertime;
		}
		else if (m_buffertime > m_pAttbute->timesArr[m_pAttbute->count * 2 - 1])
		{
			m_buffertime = m_pAttbute->timesArr[m_pAttbute->count * 2 - 1];
			ntemp = m_buffertime;
		}
		else
		{
			ntemp = m_pAttbute->timesArr[0];
			uint16 index(0);
			for (uint8 i = 1; i <= m_pAttbute->count; ++i)
			{
				index = i * 2 - 1;
				if (m_buffertime > m_pAttbute->timesArr[index])
					ntemp = m_pAttbute->timesArr[index];
				else
				{
					if (m_buffertime > m_pAttbute->timesArr[index - 1])
						ntemp = m_buffertime;
					break;
				}
			}
		}

		m_realtime = ntemp;
		ConfigManage::share()->CheckTimes(m_realtime);
		
		AdjustAwardRate();
	}

	return m_realtime;
}

void CaObject::AdjustAwardRate()
{
	m_awardRate = BASE_RATE / m_realtime;
}

const uint16& CaObject::GetAwardRate()const
{
	return m_awardRate;
}

bool CaObject::IsObjectActivity() const
{
	return m_state > OBJECT_STATE_NULL&&m_state < OBJECT_STATE_DEATH;
}

uint16 CaObject::GetObjectTimes() const
{
	return m_realtime;
}
