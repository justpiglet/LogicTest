#pragma once
#include <time.h>

enum BallColor
{
	BallColor_Red = 0,
	BallColor_Red_Max = 5,
	BallColor_Blue
};

#define BALL_COUNT 7
#define	VAILD_BALL_NUM(Index,Val) (Val<=(Index<=BallColor_Red_Max?33:16))


class GroupBallNum :public BallNum
{
public:
	GroupBallNum();
	~GroupBallNum();
	
	void Reset();
	bool Parsing(const char* szText);
	bool Parsing(const wchar_t* szText);

	CString toCString(bool showTime = false)const;
	std::string toStdstring(bool showTime=false)const;

	void SetId(uint32 _id){ id = _id; }
	void SetNum(uint8 index, uint8 val){ if (index < BALL_COUNT)number[index] = val;}

	bool ChehckNumVaild()const;
	bool IsEmpty()const{ return id <=0; }
};

