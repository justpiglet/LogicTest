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

	const char* GetFieldString(uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField = NULL)const;
	CString GetFieldItemCS(uint8 iRow, uint8 iColumn, bool isNeedHide)const;

	const FIELD_ITEM* GetItem(uint8 iRow)const;
	
protected:
	void WriteBuffer(const std::string& strName, const std::string& strPwd);
	bool LoadBuffer(std::ifstream& rFile, const std::string& strName, const std::string& strPwd);

	bool IsNeedHideParts(bool isNeedHide, uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField = NULL)const;
private:
	void GetDataToChar(std::string&);
	void ParsingString(const char*);
	
};

//////////////////////////////////////////////////////////////////////////
class UserFieldManage
{
	friend class CField;
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

	uint32 CreateAccount(const char* szAccount, uint32 iLenA, const char*szPwd, uint32 iLenP);
	uint8 UserLogoin(const char* szName, const char* szPwd);
	bool UserLogoinSuccess(Account_Info* pInfo);
	
	const CField* GetCurUserFields(){ return m_pCurUser; }
	const Account_Info* GetCurAccount(){ return m_pCurAccount; }

	void SaveConfigField();
	bool LoadConfigField(const std::string& strName);

	uint32 GetUserCount(VEC_STR& vecOut,bool isUse=true);
	uint32 GetUserCount(bool isUse = true);
private:
	UserFieldManage();
	~UserFieldManage();

protected:
	std::string GetResourcePath();
	std::string GetResourceFileName(const char*);
	void SaveCopyOfError(std::ifstream& rFile,const std::string& strName);

	void WriteInfo(const std::string& strName, const std::string& strSrc, const std::string& strPwd="");
	bool ReadInfo(const std::string& strName, std::string& strOut, const std::string& strPwd = "");
private:
	static UserFieldManage* m_gShare;
	Config_Info m_ConfigInfo;
	CField* m_pCurUser;
	Account_Info* m_pCurAccount;
	std::string m_strBasePwd;
};


#endif