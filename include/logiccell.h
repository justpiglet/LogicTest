#ifndef _FHKJEF_FDS_CAN_CALOGICCELL
#define _FHKJEF_FDS_CAN_CALOGICCELL

#include"publicpro.h"

//class CaLogicPool;
struct SaveScore
{
	SCORE score;
	W_VAL waterVal;
	PROFIT profit;

	SaveScore() :score(0), waterVal(0), profit(0)
	{
	}
	void setValue(SCORE score, W_VAL value, PROFIT profit)
	{
		this->score = score;
		this->waterVal = value;
		this->profit = profit;
	}
	void setScore(SCORE score)
	{
		this->score = this->score + score;
	}
};

class CaLogicCell
{
	friend class CaLogicPool;

	enum P_STATE
	{
		P_STATE_IDLE=0,
		P_STATE_DOING,
	};

	CaLogicCell();
protected:
	inline SCORE GetCurScore(){ return m_Score.score; }
	void SetInitialValue(SCORE, W_VAL,PROFIT);
	void OperateScore(int32);
	bool CalculateResult(uint16, const std::vector<CaObject*>&, std::vector<CaObject*>&);
	void ResetGameValue();
	inline bool IsNeedSave(){ return m_state == P_STATE_DOING; }
	const SaveScore* GetSaveScore(bool isSave=true);
public:
	~CaLogicCell();

private:
	SaveScore m_Score;
	P_STATE m_state;
};
#endif
