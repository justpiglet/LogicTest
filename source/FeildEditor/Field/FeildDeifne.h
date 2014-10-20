#ifndef FERTRHTH_FeildDeifne_h
#define FERTRHTH_FeildDeifne_h
#include "base/basedefine.h"
#include <string.h>
#include <list>
#include <vector>

enum FeildColumn
{
	FeildColumn_Nick=0,
	FeildColumn_Account,
	FeildColumn_PwdBegin,
	FeildColumn_PwdLogin = FeildColumn_PwdBegin,
	FeildColumn_PwdPay,
	FeildColumn_PwdOther,
	FeildColumn_PwdEnd = FeildColumn_PwdOther,
	FeildColumn_Relation,
	FeildColumn_Describe,

	FeildColumn_Max
};

static TCHAR g_FeildName[FeildColumn_Max][16] = { _T("NickName"), _T("Account"), _T("LoginPwd"), _T("PayPwd"), _T("OtherPwd"), _T("Relation"), _T("Describe")};
static uint8 g_FeildLen[FeildColumn_Max] = {100,160,130,130,130,200,200};
struct FIELD_ITEM
{
	uint32 id;
	uint32 iLv;
	std::string strNameNick;
	std::string strAccount;
	std::string strLoginPwd;
	std::string strPayPwd;
	std::string strOtherPwd;
	std::string strRelation;
	std::string strDescribe;
};

enum SHOW_ITEM_LV
{
	SHOW_ITEM_LV_NOR = 0, /*allways show*/
	SHOW_ITEM_LV_EMAIL=1,
	SHOW_ITEM_LV_WEB = 2,
	SHOW_ITEM_LV_SECRET=4,
};
typedef std::vector<FIELD_ITEM>	VEC_ITEMS;
struct User_Feild
{
	uint32 iLastLogoinTime;		
	uint32 iVaildLoginTime;
	uint32 iShowItemTime;
	uint32 iShowLevel; //SHOW_ITEM_LV SHOW_ITEM_LV_NOR | SHOW_ITEM_LV_HIGHT
	std::string strName;
	std::string strPwd;
	VEC_ITEMS listItem;
};


#endif // !FERTRHTH_FeildDeifne_h
