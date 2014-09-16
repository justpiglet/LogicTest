#include "stdafx.h"
#include "ManageDataBase.h"
#include <time.h>

ManageDataBase* ManageDataBase::g_self=NULL;
ManageDataBase::ManageDataBase() :m_pDataBase(NULL)
{
}


ManageDataBase::~ManageDataBase()
{
}

ManageDataBase* ManageDataBase::Share()
{
	if (!g_self)
		g_self = new ManageDataBase;

	return g_self;
}

void ManageDataBase::InitDataBase()
{
	if (!m_pDataBase)
		m_pDataBase = CSqliteDatabase::Create("res\\ballnumber.db", "");

	CheckDataBase();
}

GroupBallNum ManageDataBase::GetNearDataByIndex(uint32 index)
{
	if (!m_pDataBase)
		return GroupBallNum();

	char sztext[256] = "";
	sprintf_s(sztext, sizeof(sztext), "select * from (select * from balldata order by id DESC limit %d) order by id ASC limit 1", index);
	CSqliteRecordSet* pdata = m_pDataBase->Execute(sztext);

	GroupBallNum mballNumber;

	if (pdata && pdata->IsOk())
	{
		uint8 i(0);
		char szNumName[16] = "";
		if (pdata->NextRow())
		{

			mballNumber.id = pdata->GetInt("id", 0);
			for (i = 0; i < BALL_COUNT; ++i)
			{
				sprintf_s(szNumName, 16, "num%d", i);
				mballNumber.number[i] = pdata->GetInt(szNumName, 0);
			}
		}
	}
	pdata->Release();

	return mballNumber;
}

void ManageDataBase::CheckDataBase()
{
	if (!m_pDataBase)
		return;

	m_pDataBase->Execute("delete from balldata where id<2000000 or id >2016000");
	CSqliteRecordSet* pdata = m_pDataBase->Execute("select id from balldata order by id ASC ");
	
	if (pdata&&pdata->IsOk())
	{
		int newVal(0), oldVal(0);
		while (pdata->NextRow())
		{
			newVal = pdata->GetInt("id", 0);
			if (newVal != oldVal + 1 && oldVal > 0)
			{
				if (newVal != ((oldVal / 1000) + 1) * 1000 + 1)
				{
					m_checckVec.push_back(oldVal);
					m_checckVec.push_back(newVal);
				}
				
			}
			oldVal = newVal;
		}
	}
}

bool ManageDataBase::InsertData(const GroupBallNum& data)
{
	if (!m_pDataBase)
		return false;

	time_t nowTime = time(NULL);
	tm tmNowTime;
	localtime_s(&tmNowTime,&nowTime);
	if (data.id<2014001 || data.id>(tmNowTime.tm_year + 1900 + 1) * 1000)
		return false;

	char szText[256] = "";
	sprintf_s(szText, sizeof(szText), "insert into balldata(id,num0,num1,num2,num3,num4,num5,num6)", data.id, data.number[0], data.number[1], data.number[2], data.number[3], data.number[4], data.number[5], data.number[6]);
	return m_pDataBase->Execute(szText)!=NULL;
}


