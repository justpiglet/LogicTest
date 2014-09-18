#pragma once
#include <time.h>

enum BallColor
{
	BallColor_Red = 0,
	BallColor_Red_Max = 5,
	BallColor_Blue
};

#define BALL_COUNT 7
#define	MAX_BALL_NUM(color) color<=BallColor_Red_Max?32:16

class GroupBallNum
{
public:
	GroupBallNum();
	~GroupBallNum();
	
	void Reset();
	bool Parsing(const char* szText);
	bool Parsing(const wchar_t* szText);
	CString toCString();
	//void toChar(char szOut[], int len);
	void SetId(uint32 _id){ id = _id; }
	void SetNum(uint8 index, uint8 val){ if (index < BALL_COUNT)number[index] = val;}

	bool ChehckNumVaild()const;

	static void SaveChar(char szOut[],int len, const GroupBallNum& src);
private:
	uint32 id;
	uint32 number[7];
};

