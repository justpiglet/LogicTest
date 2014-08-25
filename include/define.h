
#ifndef _FHKJEF_FDS_CAN_DEFINE
#define _FHKJEF_FDS_CAN_DEFINE
#include"publicpro.h"

#pragma pack(1) 

#define MAX_RATE_COUNT 16
#define MAX_TIMES_COUNT MAX_RATE_COUNT<<1
#define MAX_OBJECT_ID 199
#define MAX_POOLCELL_COUNT 20

enum OBODY
{
	OBODY_SMALL = 0,	 //0 small, move no limit. 
	OBODY_MID,			//1 mid, move light curve.
	OBODY_LARGE,		// 2 big, move lamost straight line.

	MAX_OBJECT_BODY,
};

enum OLEVEL
{
	OLEVEL_FREE = 0,	//too small to no control
	
	OLEVEL_ADJUST_BEGIN,//for adjust score
	OLEVEL_ADJUST_LOW=OLEVEL_ADJUST_BEGIN,
	OLEVEL_ADJUST_MID,
	OLEVEL_ADJUST_HIGH,
	OLEVEL_ADJUST_END=OLEVEL_ADJUST_HIGH,

	OLEVEL_AWARD_BEGIN,//award
	OBJECT_AWARD_LOW=OLEVEL_AWARD_BEGIN,
	OBJECT_AWARD_MID,
	OBJECT_AWARD_HIGH,
	OLEVEL_AWARD_END=OBJECT_AWARD_HIGH,

	OLEVEL_SURPRISE,

	MAX_OLEVEL,
};

enum TIMES_TYPE
{
	TIMES_TYPE_UNIQUE	= 0,	//only one times
	TIMES_TYPE_MULTI,			//multi times ,random select times by rate
	TIMES_TYPE_CHANGE_ADD,		//same as multi but times can plus 
	TIMES_TYPE_CHANGE_MINUS,	//same as multi but times can minus 
	TIMES_TYPE_CHANGE_ALL,
	MAX_TIMES_TYPE_ = TIMES_TYPE_CHANGE_ALL
};

struct CaAttribute
{
	uint8 id;		//"0-MAX_OBJECT_ID unique ",
	//uint8 level;	//OBJECT_LEVEL"0 low ,1 mid ,2 hight,3 super,level more big and times value more big"
	uint8 body;		//OBJECT_BODY"0 small, move no limit. 1 mid, move light curve. 2 big, move lamost straight line"
	uint8 type;		//"0 single times,1 multi times"
	uint8 count;	//vaild times pairs count
	uint16 timesArr[MAX_TIMES_COUNT];//"objects times"
	uint16 rateArr[MAX_RATE_COUNT];	//"if typed is mutli times then get a times base on rates"
	std::string name;

	CaAttribute()
		:type(0), count(0), id(0), name(""),/* level(0),*/ body(0)
	{
		memset(timesArr, 0, sizeof(timesArr));
		memset(rateArr, 0, sizeof(rateArr));
	};
};


#pragma pack()
#endif

