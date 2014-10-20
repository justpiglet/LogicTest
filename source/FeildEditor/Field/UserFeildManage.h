#ifndef fdgjfdljgld_UserFeildManage_h
#define fdgjfdljgld_UserFeildManage_h
#include "stdafx.h"
#include "FeildDeifne.h"

typedef std::vector<User_Feild> VEC_FEILDS;

class UserFeildManage
{
public:
	static UserFeildManage* Share();
	bool LoadData();
	//return error
	std::string UserLogoin(const std::string& straNme, const std::string& strPwd);
	uint16 GetFeildRow();
	bool IsShowRow(uint8 iRow);
	//iRow between 0->n, iColumn same.
	CString GetFeildItemCS(uint8 iRow, uint8 iColumn);
	std::string GetFeildItemStd(uint8 iRow, uint8 iColumn);
	std::string GetUserName();
	const FIELD_ITEM* GetItem(uint8 iRow);
private:
	UserFeildManage();
	~UserFeildManage();

	bool IsVaild(uint8 iRow, uint8 iColumn=0);
	std::string GetResourcePath();
	std::string GetResourceFileName(const char*);
private:
	static UserFeildManage* m_gShare;
	VEC_FEILDS m_vecUserInfo;

	User_Feild* m_curUser;
};


#endif