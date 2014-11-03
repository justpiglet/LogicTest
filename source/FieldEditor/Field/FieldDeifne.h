#ifndef FERTRHTH_FieldDeifne_h
#define FERTRHTH_FieldDeifne_h
#include "base/basedefine.h"
#include <string.h>
#include <list>
#include <vector>

#define MAX_LEN_NAME 33
#define MAX_LEN_PWD  33
#define MAX_LEN_TEXT 129

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

static TCHAR g_FieldName[FieldColumn_Max][16] = { _T("NickName"), _T("Account"), _T("LoginPwd"), _T("PayPwd"), _T("OtherPwd"), _T("Relation"), _T("Describe")};
static uint8 g_FieldLen[FieldColumn_Max] = {100,160,130,130,130,200,200};
struct FIELD_ITEM
{
	uint32	id;
	uint32	iLv;
	char	strNameNick[MAX_LEN_NAME];
	char	strAccount[MAX_LEN_NAME];
	char	strLoginPwd[MAX_LEN_PWD];
	char	strPayPwd[MAX_LEN_PWD];
	char	strOtherPwd[MAX_LEN_PWD];
	char	strRelation[MAX_LEN_NAME];
	char	strDescribe[MAX_LEN_TEXT];
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
	uint32		iLastLogoinTime;		
	uint32		iVaildLoginTime;
	uint32		iShowItemTime;
	uint32		iShowLevel; //SHOW_ITEM_LV SHOW_ITEM_LV_NOR | SHOW_ITEM_LV_HIGHT
	uint32		iHideParts; //SHOW_ITEM_LV SHOW_ITEM_LV_NOR | SHOW_ITEM_LV_HIGHT
	char		strName[MAX_LEN_NAME];
	char		strPwd[MAX_LEN_PWD];
	VEC_ITEMS	listItem;
};


struct Account_Info
{
	char	strName[MAX_LEN_NAME];
	char	strPwd[MAX_LEN_PWD];
};
typedef std::vector<Account_Info> VEC_ACCOUNTS;
struct Config_Info
{
	char	strFieldPwd[MAX_LEN_PWD];
	char	strPwdPwd[MAX_LEN_PWD];
	VEC_ACCOUNTS vecUse;
	VEC_ACCOUNTS vecAbandon;
};
#endif // !FERTRHTH_FieldDeifne_h
