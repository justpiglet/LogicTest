#pragma once

#include "sqlitedb/SqliteDatabasePro.h"
#include "sqlitedb/SqliteDatabase.h"
#include "sqlitedb/SqliteRecordSet.h"
#include "GroupBallNum.h"
#include<vector>
using std::vector;


class ManageDataBase
{
public:
	static ManageDataBase* Share();

	void InitDataBase();
	bool GetNearDataByIndex(uint32 index, GroupBallNum& out);
	bool InsertData(const GroupBallNum& data);
	std::string GetMissData();
	bool QueryDatas(uint32, GroupBallNum&);
	bool ModifyData(const GroupBallNum& data);
	bool DeleteData(uint32);

	std::string GetLastError();

	//math
	bool GetNumList(vector<BallNum>& outList,uint32 iyear=-1);
	//void CalculateNumCount();
private:
	ManageDataBase();
	~ManageDataBase();
	
	void CheckDataBase();
	bool ParsingRecord(GroupBallNum& ,CSqliteRecordSet* ,bool check=true);
	CSqliteRecordSet* Execute(const char* format, ...);
private:
	static ManageDataBase* g_self;
	CSqliteDatabase* m_pDataBase;
	vector<int> m_checckVec;
};

