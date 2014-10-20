#include "stdafx.h"
#include "ManageDataBase.h"
#include "Analysis/BaseAnalysis.h"
#include <string.h>
using std::string;

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
		m_pDataBase = CSqliteDatabase::Create("../BallNum/res/ballnumber.db", "");

	CheckDataBase();
}

bool ManageDataBase::GetNearDataByIndex(uint32 index, GroupBallNum& out)
{
	if (!m_pDataBase)
		return false;

	char sztext[256] = "";
	sprintf_s(sztext, sizeof(sztext), "select * from (select * from balldata order by id DESC limit %d) order by id ASC limit 1", index);
	CSqliteRecordSet* pdata = m_pDataBase->Execute(sztext);

	ParsingRecord(out, pdata);
	pdata->Release();
	return true;
}

void ManageDataBase::CheckDataBase()
{
	if (!m_pDataBase)
		return;

	//m_pDataBase->Execute("update balldata set id=id%100000");

	m_checckVec.clear();
	//m_pDataBase->Execute("delete from balldata where id<3001 or id >2016000");
	CSqliteRecordSet* pdata = m_pDataBase->Execute("select id,num0,num1,num2,num3,num4,num5,num6 from balldata order by id ASC ");
	
	if (pdata&&pdata->IsOk())
	{
		int newVal(0), oldVal(0);
		GroupBallNum tempData;
		BaseAnalysis::share()->AddDataBegin();
		while (pdata->NextRow())
		{
			ParsingRecord(tempData, pdata,false);
			BaseAnalysis::share()->AddOriginData(tempData);
			newVal = tempData.GetId();
			if (newVal != oldVal + 1 && oldVal > 0)
			{
				if (newVal != ((oldVal / 1000) + 1) * 1000 + 1)
				{
					if (newVal != oldVal)
					{
						m_checckVec.push_back(oldVal);
						m_checckVec.push_back(newVal);
					}
				}
				
			}
			oldVal = newVal;
		}
		BaseAnalysis::share()->AddDataEnd();
	}

	if (pdata)
		pdata->Release();
}

bool ManageDataBase::InsertData(const GroupBallNum& data)
{

	if (!m_pDataBase)
		return false;
	else if(data.ChehckNumVaild())
	{
		std::string szNum=data.toStdstring(true);
		char szText[1024] = "";
		sprintf_s(szText, sizeof(szText), "insert into balldata(id,num0,num1,num2,num3,num4,num5,num6,date) VALUES(%s)", szNum.c_str());

		if (m_pDataBase->Execute(szText) != NULL)
		{
			CheckDataBase();
			return true;
		}
	}

	return false;
}

std::string ManageDataBase::GetMissData()
{
	if (m_checckVec.empty())
		return std::string(("Miss Data [0]."));

	std::string strMissData("");
	vector<int>::iterator itor = m_checckVec.begin();
	char szTemp[64] = "";
	int nums[2] = { 0 };
	uint32 iCount(0);
	for (; itor != m_checckVec.end(); ++itor)
	{
		nums[0] = *(itor++);
		nums[1] = *itor;
		sprintf(szTemp, "%d-%d \n", nums[0], nums[1]);
		strMissData.append(szTemp);
		iCount = nums[1] - nums[0] - 1;
	}
	sprintf_s(szTemp, sizeof(szTemp), "Miss Data [%d].\n", iCount);
	return std::string(szTemp).append(strMissData);
}

bool ManageDataBase::QueryDatas(uint32 id, GroupBallNum& out)
{
	
	CSqliteRecordSet* pRecord = Execute("select * from balldata where id=%d", id);
	if (pRecord)
	{
		ParsingRecord(out, pRecord);
		pRecord->Release();
	}
	
	return pRecord!=NULL;
}

std::string ManageDataBase::GetLastError()
{
	std::string strError("data base is invaild! \n");
	if (m_pDataBase)
		strError = m_pDataBase->GetLastError();

	return strError;
}

bool ManageDataBase::ModifyData(const GroupBallNum& data)
{
	return true;
}

CSqliteRecordSet* ManageDataBase::Execute(const char* format, ...)
{
	va_list arg;
	int done = 0;

	va_start(arg, format);
	char szSql[1024] = "";
	//vprintf
	//sprintf_s(szSql, sizeof(szSql), format, arg);
	_vsnprintf_s(szSql, sizeof(szSql), format, arg);
	va_end(arg);
	return m_pDataBase->Execute(szSql);
}

bool ManageDataBase::ParsingRecord(GroupBallNum& mOut, CSqliteRecordSet* pRecord, bool check/* = true*/)
{
	if (check)
	{
		if (!pRecord || !pRecord->IsOk())
			return false;
		if (!pRecord->NextRow())
			return false;
	}

	uint8 i(0);
	char szNumName[16] = "";
	mOut.SetId(pRecord->GetInt("id", 0));

	for (i = 0; i < BALL_COUNT; ++i)
	{
		sprintf_s(szNumName, 16, "num%d", i);
		mOut.SetNum(i, pRecord->GetInt(szNumName, 0));
	}
	return true;

}

bool ManageDataBase::DeleteData(uint32 id)
{
	if (Execute("delete from balldata where id=%d", id) != NULL)
	{
		CheckDataBase();
		return true;
	}
	else
		return false;
		
}

bool ManageDataBase::GetNumList(vector<BallNum>& outList, uint32 iyear/*=-1*/)
{
	outList.clear();
	CSqliteRecordSet* pRecord = NULL;

	char szSql[256] = "select id, num0, num1, num2, num3, num4, num5, num6 from balldata ";
	if (iyear == -1)
		pRecord = Execute("%s order by id ASC ",szSql);
	else
		pRecord = Execute("%s where id>%d and id<%d order by id ASC ", szSql, iyear * 1000, (iyear+1)*1000);
	
	if (pRecord&&pRecord->IsOk())
	{
		GroupBallNum mBallData;
		while (pRecord->NextRow())
		{
			ParsingRecord(mBallData, pRecord,false);
			outList.push_back(mBallData);
		}
	}
	if (pRecord)
		pRecord->Release();
	return !outList.empty();
}

// void ManageDataBase::CalculateNumCount()
// {
// 	
// }


