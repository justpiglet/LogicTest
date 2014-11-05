#ifndef fdgjfdljgld_UserFieldManage_h
#define fdgjfdljgld_UserFieldManage_h
#include "stdafx.h"
#include "FieldDeifne.h"
#include <fstream>

class CField : public User_Field
{
	friend class UserFieldManage;
public:
	CField();
	~CField();
	uint16 GetFieldRow() const { return listItem.size(); }
	bool IsShowRow(uint8 iRow) const;
	bool IsVaild(uint8 iRow, uint8 iColumn = 0) const;

	const char* GetUserName() const { return strName;}
	const char* GetFieldString(uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField = NULL)const;
	CString GetFieldItemCS(uint8 iRow, uint8 iColumn, bool isHideParts)const;

	const FIELD_ITEM* GetItem(uint8 iRow)const;
	
protected:
	

	bool WriteBuffer(std::ofstream& wFile);
	bool LoadBuffer(std::ifstream& rFile);

	bool IsNeedHideParts(bool isHideParts, uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField = NULL)const;
private:
	void GetDataToChar(std::string&);
	void ParsingString(const char*);
	
};

//////////////////////////////////////////////////////////////////////////
class UserFieldManage
{
public:
	static UserFieldManage* Share();

	inline static void ParsingStringCopy(const char* pIndex, void* pDest, uint32 iLen)
	{
		memcpy(pDest, pIndex, iLen);
		pIndex = pIndex + iLen;
	}
	inline static uint32 ParsingStringCopy(const std::string& strSrc,uint32& iOffset, void* pDest, uint32 iLen)
	{
		if (iOffset + iLen >= strSrc.length())
			return iOffset;
		memcpy(pDest,strSrc.c_str() + iOffset, iLen);
		iOffset += iLen;
		return iOffset;
	}

	bool InitData();
	//return error
	std::string UserLogoin(const std::string& straNme, const std::string& strPwd);

	const CField* GetCurUserFields(){ return m_curUser; }

	void SaveConfigField();
	bool LoadConfigField(std::ifstream& rFile);

	uint32 GetUserCount(VEC_STR& vecOut,bool isUse=true);
	uint32 GetUserCount(bool isUse = true);
private:
	UserFieldManage();
	~UserFieldManage();

	
	std::string GetResourcePath();
	std::string GetResourceFileName(const char*);
private:
	static UserFieldManage* m_gShare;
	Config_Info m_ConfigInfo;
	CField* m_curUser;
};


#endif