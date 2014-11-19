#ifndef FERTRHTH_FieldDeifne_h
#define FERTRHTH_FieldDeifne_h
#include "base/basedefine.h"
#include <string.h>
#include <list>
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


struct FIELD_PWD_RECORD
{
	uint32 iMTime;
	char   strOldPwd[DEFINE_LEN_PWD];
};
typedef std::vector<FIELD_PWD_RECORD> VEC_PWD_RECORD;

struct FIELD_ITEM
{
	uint32	id;
	uint32	iLv;
	char	strNameNick[DEFINE_LEN_NAME];
	char	strAccount[DEFINE_LEN_NAME];
	char	strLoginPwd[DEFINE_LEN_PWD];
	char	strPayPwd[DEFINE_LEN_PWD];
	char	strOtherPwd[DEFINE_LEN_PWD];
	char	strRelation[DEFINE_LEN_NAME];
	char	strDescribe[MAX_LEN_TEXT];

	VEC_PWD_RECORD vecLogoin; //MAX_RECORD_COUNT
	VEC_PWD_RECORD vecPay;
	VEC_PWD_RECORD vecOther;

	FIELD_ITEM() :id(0), iLv(0)
	{
		memset(strNameNick, 0, DEFINE_LEN_NAME);
		memset(strAccount, 0, DEFINE_LEN_NAME);
		memset(strLoginPwd, 0, DEFINE_LEN_PWD);
		memset(strPayPwd, 0, DEFINE_LEN_PWD);
		memset(strOtherPwd, 0, DEFINE_LEN_PWD);
		memset(strRelation, 0, DEFINE_LEN_NAME);
		memset(strDescribe, 0, MAX_LEN_TEXT);
	}
};
enum SHOW_ITEM_LV
{
	SHOW_ITEM_LV_NOR = 0, /*allways show*/
	SHOW_ITEM_LV_EMAIL=1,
	SHOW_ITEM_LV_WEB = 2,
	SHOW_ITEM_LV_SECRET=4,
};
typedef std::vector<FIELD_ITEM>	VEC_ITEMS;
struct User_Field
{
	VEC_ITEMS	listItem;
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
		, iShowLevel(SHOW_ITEM_LV_WEB | SHOW_ITEM_LV_SECRET)
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
