#pragma once
#include <time.h>

enum BallColor
{
	BallColor_Red = 0,
	BallColor_Red_Max = 5,
	BallColor_Blue
};

#define BALL_COUNT 7
#define MAX_BALL_NUM(Index) (Index<=BallColor_Red_Max?33:16)
#define	VAILD_BALL_NUM(Index,Val) (Val<=MAX_BALL_NUM(Index))


class GroupBallNum :public BallNum
{
public:
	GroupBallNum();
	~GroupBallNum();
	
	void Reset();
	bool Parsing(const int iNums[], uint32 count);
	bool Parsing(const char* szText);
	bool Parsing(const wchar_t* szText);

	CString toCString(bool showTime = false)const;
	std::string toStdstring(bool showTime=false)const;

	inline void SetId(uint16 _id){ mId = _id; }
	inline uint16 GetId(){ return mId; }
	void SetNum(uint8 index, uint8 val){ if (index < BALL_COUNT)mNumber[index] = val;}

	bool ChehckNumVaild()const;
	bool IsEmpty()const{ return mId <= 0; }

	void operator= (const GroupBallNum& other);
	
};

