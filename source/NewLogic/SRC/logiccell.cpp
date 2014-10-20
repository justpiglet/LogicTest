#include "logiccell.h"
#include "manage.h"
#include "depend/cantools/tools.h"

CaLogicCell::CaLogicCell() : m_state(PLAY_STATE_IDLE)
{
}

CaLogicCell::~CaLogicCell()
{
}

void CaLogicCell::SetInitialValue(const SCORE& score, const W_VAL& value, const PROFIT& profit)
{
	m_Score.setValue(score, value, profit);
}

// void CaLogicCell::OpreateResult(int score, uint32 profit)
// {
// 	m_playerScore = m_playerScore + score;
// 	m_profit = m_profit + profit;
// }

bool CaLogicCell::CalculateResult(const uint16& power, const VEC_CAOBJECT& objects, VEC_CAOBJECT& result)
{
	uint16 objectCount = _CANNP_NAME::_min((uint16)objects.size(), ConfigManage::share()->GetHitCount());
	uint16 awardCount = ConfigManage::share()->GetAwardCount();
	for (uint16 i = 0,count=0; i < objectCount; ++i)
	{
		if (CalculateResult(power, objects[i]))
		{
			result.push_back(objects[i]);
			++count;
			if (count >= awardCount)
				break;
		}
	}

	return result.size()>0;
}

bool CaLogicCell::CalculateResult(const uint16& power, const CaObject* pObject)
{
	uint8 mstatus(CATCH_STATUS_ALLOW);
	DECIMALS fAdjust(1.0f); // over 1.0 easy.  less 1.0 difficult 0.5-2.0
	uint16 objectTimes = pObject->GetObjectTimes();

	switch (pObject->m_lv)
	{
	case OLEVEL_FREE:
	{
		break;
	}
	case OLEVEL_ADJUST_LOW:
	case OLEVEL_ADJUST_MID:
	case OLEVEL_ADJUST_HIGH:
	{
		break;
	}
	case OLEVEL_AWARD_LOW:
	case OLEVEL_AWARD_MID:
	case OLEVEL_AWARD_HIGH:
	{
		break;
	}
	case OLEVEL_SURPRISE:
	{
		break;
	}
	default:
		break;
	}

	bool isResult(false);
	switch (mstatus)
	{
	case CATCH_STATUS_BAN:
		isResult = false;
		break;
	case CATCH_STATUS_CATCH:
		isResult = true;
		break;
	case CATCH_STATUS_ALLOW:
	{
		uint16 objectRate = (uint16)(pObject->GetAwardRate()*fAdjust);
		if (objectRate < BASE_RATE)
		{
			uint16 rval = _CANNP_NAME::randoom::GetRandoom(0, (uint16)BASE_RATE);
			isResult = rval >= objectRate;
		}
		break;
	}
	default:
		break;
	}

	if (isResult)
		OperateScore(power*objectTimes);

	return isResult;
}

void CaLogicCell::OperateScore(const int32& score)
{
	m_Score.setScore(score);
	m_state = PLAY_STATE_DOING;
}

void CaLogicCell::ResetGameValue()
{
	m_Score.setValue(0, 0, 0);
}

const SaveScore* CaLogicCell::GetSaveScore(bool isSave/*=true*/)
{
	if (isSave)
		m_state = PLAY_STATE_IDLE;

	return &m_Score;
}

bool CaLogicCell::Onfire(uint16& power)
{
	if (m_Score.score <= 0)
		return false;
	else if (m_Score.score < power)
		power = m_Score.score;

	OperateScore(-power);
	
	return true;
}
