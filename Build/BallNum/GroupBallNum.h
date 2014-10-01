#pragma once
#include <time.h>

enum BallColor
{
	BallColor_Red = 0,
	BallColor_Red_Max = 5,
	BallColor_Blue,
	BallColor_Max
};

#define BALL_COUNT BallColor_Max
#define COUNT_RED 33
#define COUNT_BULE 16
#define F_COUNT_NUM(isRed) (isRed?COUNT_RED:COUNT_BULE)
#define F_MAX_BALL_NUM(Index) F_COUNT_NUM(Index<=BallColor_Red_Max)
#define	F_VAILD_BALL_NUM(Index,Val) (Val<=F_COUNT_NUM(Index))


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
	
	static bool IsNumAppear(const BallNum&, const uint8&,bool isRed=true );
};

