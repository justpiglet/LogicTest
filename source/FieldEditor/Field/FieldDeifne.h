#ifndef FERTRHTH_FieldDeifne_h
#define FERTRHTH_FieldDeifne_h
#include "base/basedefine.h"
#include <string.h>
#include <list>
#include <queue>
#include <vector>

#define MAX_LEN_AES  16   //include end
#define MAX_LEN_NAME 32
#define MAX_LEN_PWD  32
#define MAX_LEN_TEXT 128

#define DEFINE_LEN_AES 17
#define DEFINE_LEN_NAME 33
#define DEFINE_LEN_PWD 33
#define DEFINE_LEN_TEXT 129

#define MAX_RECORD_COUNT 50
typedef std::vector<std::string> VEC_STR;

enum FieldColumn
{
	FieldColumn_Nick=0,
	FieldColumn_Account,
	FieldColumn_PwdBegin,
	FieldColumn_PwdLogin = FieldColumn_PwdBegin,
	FieldColumn_PwdPay,
	FieldColumn_PwdOther,
	FieldColumn_PwdEnd = FieldColumn_PwdOther,
	FieldColumn_Relation,
	FieldColumn_Describe,

	FieldColumn_Max
};

enum SHOW_ITEM_LV
{
	SHOW_ITEM_LV_NULL	= 0,/*allways show*/
	SHOW_ITEM_LV_NOR	= 1, 
	SHOW_ITEM_LV_EMAIL	= 1<<1,
	SHOW_ITEM_LV_WEB	= 1<<2,
	SHOW_ITEM_LV_SECRET = 1<<3,

	SHOW_ITEM_LV_COUNT	= 3
};

struct FIELD_PWD_RECORD
{
	uint32 iMTime;
	char   strOldPwd[DEFINE_LEN_PWD];

	FIELD_PWD_RECORD() :iMTime(time(NULL))
	{
		memset(strOldPwd, 0, DEFINE_LEN_NAME);
	}
};
typedef std::list<FIELD_PWD_RECORD> LIST_PWD_RECORD;

struct FIELD_ITEM
{
	uint32	iFieldId;
	uint32	iLv;
	char	strNameNick[DEFINE_LEN_NAME];
	char	strAccount[DEFINE_LEN_NAME];
	char	strLoginPwd[DEFINE_LEN_PWD];
	char	strPayPwd[DEFINE_LEN_PWD];
	char	strOtherPwd[DEFINE_LEN_PWD];
	char	strRelation[DEFINE_LEN_NAME];
	char	strDescribe[MAX_LEN_TEXT];

	LIST_PWD_RECORD listRecord[FieldColumn_PwdEnd - FieldColumn_PwdBegin + 1]; //MAX_RECORD_COUNT

public:
	FIELD_ITEM() 
	{
		ClearData();
	}
	const char* GetText(uint32 iColumn) const
	{
		switch (iColumn)
		{
		case FieldColumn_Nick:
			return this->strNameNick;
		case FieldColumn_Account:
			return this->strAccount;
		case FieldColumn_PwdLogin:
			return this->strLoginPwd;
		case FieldColumn_PwdPay:
			return this->strPayPwd;
		case FieldColumn_PwdOther:
			return this->strOtherPwd;
		case FieldColumn_Relation:
			return this->strRelation;
		case FieldColumn_Describe:
			return this->strDescribe;
		default:
			return NULL;
		}
	}

	void ReplaceFiled(char* pDest, uint32 iLenD, const char* pSrc, uint32 iLenS, FieldColumn mColumn)
	{
		if (strcmp(pDest, pSrc) != 0)
		{
			if (mColumn >= FieldColumn_PwdBegin && mColumn <= FieldColumn_PwdEnd)
			{
				LIST_PWD_RECORD& vecTemp = listRecord[mColumn - FieldColumn_PwdBegin];
				if (vecTemp.size() >= MAX_RECORD_COUNT)
					vecTemp.erase(vecTemp.begin());

				FIELD_PWD_RECORD mRecord;
				memcpy_s(mRecord.strOldPwd, MAX_LEN_PWD, pSrc, iLenS);
				vecTemp.push_back(mRecord);
			}
			memcpy_s(pDest, iLenD, pSrc, iLenS);
		}
	}

	void ReplaceField(const FIELD_ITEM &mNew)
	{
		if (this->iFieldId != mNew.iFieldId)
			return;

		this->iLv = mNew.iLv;
		ReplaceFiled(this->strNameNick, MAX_LEN_NAME, mNew.strNameNick, MAX_LEN_NAME, FieldColumn_Nick);
		ReplaceFiled(this->strAccount, MAX_LEN_NAME, mNew.strAccount, MAX_LEN_NAME, FieldColumn_Account);
		ReplaceFiled(this->strRelation, MAX_LEN_NAME, mNew.strRelation, MAX_LEN_NAME, FieldColumn_Relation);
		ReplaceFiled(this->strDescribe, MAX_LEN_TEXT, mNew.strDescribe, MAX_LEN_TEXT, FieldColumn_Describe);

		ReplaceFiled(this->strLoginPwd, MAX_LEN_PWD, mNew.strLoginPwd, MAX_LEN_PWD, FieldColumn_PwdLogin);
		ReplaceFiled(this->strPayPwd, MAX_LEN_PWD, mNew.strPayPwd, MAX_LEN_PWD, FieldColumn_PwdPay);
		ReplaceFiled(this->strOtherPwd, MAX_LEN_PWD, mNew.strOtherPwd, MAX_LEN_PWD, FieldColumn_PwdOther);
	}

	bool IsEmpty()const{ return this->iLv == SHOW_ITEM_LV_NULL; }

	void ClearData()
	{
		iFieldId = 0;
		iLv = SHOW_ITEM_LV_NULL;
		memset(strNameNick, 0, DEFINE_LEN_NAME);
		memset(strAccount, 0, DEFINE_LEN_NAME);
		memset(strLoginPwd, 0, DEFINE_LEN_PWD);
		memset(strPayPwd, 0, DEFINE_LEN_PWD);
		memset(strOtherPwd, 0, DEFINE_LEN_PWD);
		memset(strRelation, 0, DEFINE_LEN_NAME);
		memset(strDescribe, 0, MAX_LEN_TEXT);

		for (uint32 i = 0; i < FieldColumn_PwdEnd - FieldColumn_PwdBegin + 1; ++i)
			listRecord[i].clear();
	}
};

typedef std::vector<FIELD_ITEM>	VEC_ITEMS;
struct User_Field
{
	uint32		iCurFiledId;
	VEC_ITEMS	listItem;
	User_Field() :iCurFiledId(0)
	{

	}
};

struct User_Set
{
	//uint32		iLastLogoinTime;
	uint32		iVaildLoginTime;
	uint32		iShowItemTime;
	uint32		iShowLevel; //SHOW_ITEM_LV SHOW_ITEM_LV_NOR | SHOW_ITEM_LV_HIGHT
	uint32		iHideParts; //FieldColumn_PwdLogin | FieldColumn_PwdPay 
	
	User_Set() 
		//: iLastLogoinTime(time(NULL))
		: iVaildLoginTime(0)
		, iShowItemTime(5)
		, iShowLevel(SHOW_ITEM_LV_NOR | SHOW_ITEM_LV_EMAIL)
		, iHideParts( (1 << FieldColumn_PwdLogin) | (1 << FieldColumn_PwdPay) | (1 << FieldColumn_PwdOther) )
	{

	}
};

struct Account_Info
{
	uint32  iId;
	char	strName[DEFINE_LEN_NAME];
	char	strPwd[DEFINE_LEN_PWD];
	char	strOPwd[DEFINE_LEN_PWD];

	Account_Info() :iId(0)
	{
		memset(strName, 0, DEFINE_LEN_NAME);
		memset(strPwd, 0, DEFINE_LEN_PWD);
		memset(strOPwd, 0, DEFINE_LEN_PWD);
	}
};
typedef std::vector<Account_Info> VEC_ACCOUNTS;
struct Config_Info
{
	uint32  iCurID;
	char	strFieldPwd[DEFINE_LEN_PWD];
	char	strPwdPwd[DEFINE_LEN_PWD];
	VEC_ACCOUNTS vecUse;
	VEC_ACCOUNTS vecAbandon;

	Config_Info() :iCurID(0)
	{ 
		memset(strFieldPwd, 0, DEFINE_LEN_PWD);
		memset(strPwdPwd, 0, DEFINE_LEN_PWD);
	}
};
#endif // !FERTRHTH_FieldDeifne_h
