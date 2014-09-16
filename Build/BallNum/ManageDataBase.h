#pragma once

#include "sqlitedb/SqliteDatabasePro.h"
#include "sqlitedb/SqliteDatabase.h"
#include "sqlitedb/SqliteRecordSet.h"

#include<vector>
using std::vector;

class ManageDataBase
{
public:
	static ManageDataBase* Share();

	void InitDataBase();
	GroupBallNum GetNearDataByIndex(uint32 index);
	bool InsertData(const GroupBallNum& data);
private:
	ManageDataBase();
	~ManageDataBase();
	
	void CheckDataBase();
private:
	static ManageDataBase* g_self;
	CSqliteDatabase* m_pDataBase;
	vector<int> m_checckVec;
};

