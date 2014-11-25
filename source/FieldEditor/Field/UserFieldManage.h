#ifndef fdgjfdljgld_UserFieldManage_h
#define fdgjfdljgld_UserFieldManage_h
#include "stdafx.h"
#include "FieldDeifne.h"
#include <fstream>

enum ELOGOIN_RET
{
	ER_SUCCESS = 0,
	ER_ERROR_ACCOUNT,
	ER_ERROR_PWD,
	ER_ERROR
};

enum ELOGOIN_MODE
{
	ELOGOIN_MODE_NOR=0,
	ELOGOIN_MODE_OPERATE
};

class CField : public User_Field
{
	friend class UserFieldManage;
public:
	CField(uint32 iUserId);
	~CField();
	uint16 GetFieldRow() const { return listItem.size(); }
	bool IsShowRow(uint8 index) const;
	bool IsVaild(uint8 index, uint8 iColumn = 0) const;
	inline bool IsVaildId(uint32 iId)const { return iId <= m_userSet.iCurFiledId; }

	STDSTR GetFieldHideParts(const FIELD_ITEM* pField, uint8 iColumn, bool isNeedHide) const;
	STDSTR GetFieldHideParts(uint8 index, uint8 iColumn, bool isNeedHide)const;

	const FIELD_ITEM* GetItem(uint8 index)const;

	bool IsCanUseNickName(const char*)const;

	const FIELD_ITEM* ModifyField(const FIELD_ITEM&);
	bool DeleteField(const uint32 iId);

	inline uint32 GetShowPwdTime()const { return m_userSet.iShowItemTime; }
	bool IsVaildFiled(const FIELD_ITEM*)const;
protected:
	void WriteBuffer(const std::string& strName, const std::string& strPwd);
	bool ReadBuffer(const std::string& strName, const std::string& strPwd);

	void WriteUserSet(const std::string& strName, const std::string& strPwd);
	bool ReadUserSet(const std::string& strName, const std::string& strPwd);

	bool IsNeedHideParts(bool isNeedHide, uint8 index, uint8 iColumn, const FIELD_ITEM* pField = NULL)const;
private:
	void GetDataToChar(std::string&);
	bool ParsingString(const std::string&);

private:
	uint32 m_iUserID;
	User_Set m_userSet;
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
		if (iOffset + iLen > strSrc.length())
			return iOffset;
		memcpy(pDest,strSrc.c_str() + iOffset, iLen);
		iOffset += iLen;
		return iOffset;
	}

	bool InitData();

	uint32 CreateAccount(const std::string&, const std::string&, const std::string&);
	uint8 UserLogoin(const char* szName, const char* szPwd, ELOGOIN_MODE mmode=ELOGOIN_MODE_NOR);
	bool UserLogoinSuccess(Account_Info* pInfo);
	
	const CField* GetCurUserFields(){ return m_pCurUser; }
	const Account_Info* GetCurAccount(){ return m_pCurAccount; }

	void SaveConfigField();
	bool LoadConfigField(const std::string& strName);

	uint32 GetUserCount(VEC_STR& vecOut,bool isUse=true);
	uint32 GetUserCount(bool isUse = true);
	bool VerifyAccount(CONST_STDSTR& strAccount);

	const FIELD_ITEM* UserFieldModify(const FIELD_ITEM&);
	bool UserFieldDelete(const uint32& iFieldId);
private:
	UserFieldManage();
	~UserFieldManage();

protected:
	std::string GetResourcePath();
	std::string GetResourceFileName(const char*);
	std::string GetResourceFileNameMD5(const char*,const char* szAdd=NULL);
	void SaveCopyOfError(const std::string& strName);

	const std::string& GetBasePwd(){ return m_strBasePwd; }
	void WriteInfo(const std::string& strName, const std::string& strSrc,const std::string& strBasePwd,bool isMainConfig=false);
	bool ReadInfo(const std::string& strName, std::string& strOut, std::string& strBasePwd = std::string());
private:
	static UserFieldManage* m_gShare;
	Config_Info m_ConfigInfo;
	CField* m_pCurUser;
	Account_Info* m_pCurAccount;
	std::string m_strBasePwd;
};


#endif