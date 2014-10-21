#ifndef fdgjfdljgld_UserFeildManage_h
#define fdgjfdljgld_UserFeildManage_h
#include "stdafx.h"
#include "FeildDeifne.h"
#include <fstream>

class CField : public User_Feild
{
	friend class UserFeildManage;
public:
	CField();
	~CField();
	uint16 GetFeildRow(){ return listItem.size(); }
	bool IsShowRow(uint8 iRow);
	bool IsVaild(uint8 iRow, uint8 iColumn = 0);

	const char* GetUserName(){ return strName; }
	const char* GetFieldString(uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField=NULL);
	CString GetFeildItemCS(uint8 iRow, uint8 iColumn, bool isHideParts);

	const FIELD_ITEM* GetItem(uint8 iRow);
protected:
	

	bool WriteBuffer(std::ofstream& wFile);
	bool LoadBuffer(std::ifstream& rFile);

	bool IsNeedHideParts(bool isHideParts,uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField = NULL);
private:
	void GetDataToChar(std::string&);
	void ParsingString(const char*);
	void ParsingStringCopy(const char*,void*,uint32 iLen);
};

//////////////////////////////////////////////////////////////////////////
typedef std::vector<CField*> VEC_FEILDS;
class UserFeildManage
{
public:
	static UserFeildManage* Share();
	bool LoadData();
	//return error
	std::string UserLogoin(const std::string& straNme, const std::string& strPwd);

	uint16 GetFeildRow(){ return  m_curUser ? m_curUser->GetFeildRow() : 0; }
	bool IsShowRow(uint8 iRow){ return  m_curUser ? m_curUser->IsShowRow(iRow) : false; }
	const FIELD_ITEM* GetItem(uint8 iRow){ return  m_curUser ? m_curUser->GetItem(iRow) : NULL; }
	//iRow between 0->n, iColumn same.
	CString GetFeildItemCS(uint8 iRow, uint8 iColumn, bool isHideParts = true);

private:
	UserFeildManage();
	~UserFeildManage();

	
	std::string GetResourcePath();
	std::string GetResourceFileName(const char*);
private:
	static UserFeildManage* m_gShare;
	VEC_FEILDS m_vecUserInfo;

	CField* m_curUser;
};


#endif