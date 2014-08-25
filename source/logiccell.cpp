#include "logiccell.h"

CaLogicCell::CaLogicCell() : m_state(P_STATE_IDLE)
{
}

CaLogicCell::~CaLogicCell()
{
}

void CaLogicCell::SetInitialValue(SCORE score, W_VAL value, PROFIT profit)
{
	m_Score.setValue(score, value, profit);
}

// void CaLogicCell::OpreateResult(int score, uint32 profit)
// {
// 	m_playerScore = m_playerScore + score;
// 	m_profit = m_profit + profit;
// }

bool CaLogicCell::CalculateResult(uint16, const vector<CaObject*>&, vector<CaObject*>&)
{
	m_state = P_STATE_DOING;

	return true;
}

void CaLogicCell::OperateScore(int32 score)
{
	m_Score.setScore(score);
	m_state = P_STATE_DOING;
}

void CaLogicCell::ResetGameValue()
{
	m_Score.setValue(0, 0, 0);
}

const SaveScore* CaLogicCell::GetSaveScore(bool isSave/*=true*/)
{
	if (isSave)
		m_state = P_STATE_IDLE;

	return &m_Score;
}
