#ifndef _FHKJEF_FDS_CAN_CALOGICCELL
#define _FHKJEF_FDS_CAN_CALOGICCELL

#include"publicpro.h"

typedef std::vector<CaObject*> VEC_CAOBJECT;

struct SaveScore
{
	SCORE score;
	W_VAL waterVal;
	PROFIT profit;

	SaveScore() :score(0), waterVal(0), profit(0)
	{
	}
	void setValue(const SCORE& score, const W_VAL& value, const PROFIT& profit)
	{
		this->score = score;
		this->waterVal = value;
		this->profit = profit;
	}
	void setScore(const SCORE& score)
	{
		this->score = this->score + score;
	}
};

class CaLogicCell
{
	friend class CaLogicPool;

	enum PLAY_STATE
	{
		PLAY_STATE_IDLE=0,
		PLAY_STATE_DOING,
	};

	CaLogicCell();
protected:
	inline SCORE GetCurScore(){ return m_Score.score; }
	void SetInitialValue(const SCORE&, const W_VAL& ,const PROFIT&);
	void OperateScore(const int32&);
	bool Onfire(uint16&);
	bool CalculateResult(const uint16&, const VEC_CAOBJECT&, VEC_CAOBJECT&);
	bool CalculateResult(const uint16&, const CaObject*);
	void ResetGameValue();
	inline bool IsNeedSave(){ return m_state == PLAY_STATE_DOING; }
	const SaveScore* GetSaveScore(bool isSave=true);
public:
	~CaLogicCell();

private:
	SaveScore m_Score;
	uint8 m_state;
};
#endif
