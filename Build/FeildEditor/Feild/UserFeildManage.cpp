#include "UserFeildManage.h"
#include "cantools/tools.h"

UserFeildManage* UserFeildManage::m_gShare=NULL;
UserFeildManage::UserFeildManage() :m_curUser(NULL)
{
}

UserFeildManage::~UserFeildManage()
{
}

UserFeildManage* UserFeildManage::Share()
{
	if (!m_gShare)
		m_gShare = new UserFeildManage;

	return m_gShare;
}

bool UserFeildManage::LoadData()
{
	std::string strFilePath=GetResourceFileName("Important.db");

	//load config

	rapidjson::Document document;
	if (!_CANNP_NAME::files::ReadFileRapidJson(strFilePath.c_str(), document))
		return false;

	const rapidjson::Value& accounts = document["Account"];
	uint16 counts = accounts.Size();
	
	const char* pSz = NULL;
	for (uint16 i = 0; i < counts; ++i)
	{
		User_Feild* pFeild=new User_Feild;
		pFeild->strName = accounts[i]["Name"].GetString();
		pSz = accounts[i]["Pwd"].GetString();
		if (pSz)
		{
			std::string aesa = _CANNP_NAME::encrypt::EncryptAES(pSz, pwd);
		}
		
	}

	return true;
}

std::string UserFeildManage::GetFeildItemStd(uint8 iRow, uint8 iColumn)
{
	if (!IsVaild(iRow, iColumn))
		return std::string("");

	FIELD_ITEM& mItem = m_curUser->listItem[iRow];
	switch (iColumn)
	{
	case FeildColumn_Nick:
		return mItem.strNameNick;
	case FeildColumn_Account:
		return mItem.strAccount;
	case FeildColumn_PwdLogin:
		return mItem.strLoginPwd;
	case FeildColumn_PwdPay:
		return mItem.strPayPwd;
	case FeildColumn_PwdOther:
		return mItem.strOtherPwd;
	case FeildColumn_Relation:
		return mItem.strRelation;
	case FeildColumn_Describe:
		return mItem.strDescribe;
	default:
		break;
	}

	return std::string("");
}

std::string UserFeildManage::UserLogoin(const std::string& straNme, const std::string& strPwd)
{
	
	if (!m_vecUserInfo.empty())
		return std::string("There haven't any user info,you need create one.");

	std::string strError;
	VEC_FEILDS::iterator itor = m_vecUserInfo.begin(),itor_end = m_vecUserInfo.end();
	for (; itor != itor_end; ++itor)
	{
		if (itor->strName == straNme)
		{
			if (itor->strPwd == strPwd)
			{
				m_curUser = &(*itor);
				return strError;
			}
				
			else
				return std::string("PassWord error,input again!");
		}
	}

	return std::string("Account error,input again!");
}

uint16 UserFeildManage::GetFeildRow()
{
	if (m_curUser)
		return m_curUser->listItem.size();
	else
		return 0;
}

CString UserFeildManage::GetFeildItemCS(uint8 iRow, uint8 iColumn)
{
	std::string strName = GetFeildItemStd(iRow, iColumn);
	return CString(strName.c_str());
}

std::string UserFeildManage::GetUserName()
{
	if (m_curUser)
		return m_curUser->strName;
	else
		return std::string("");
}

bool UserFeildManage::IsShowRow(uint8 iRow)
{
	if (!IsVaild(iRow))
		return false;

	FIELD_ITEM& mItem = m_curUser->listItem[iRow];
	if (mItem.iLv == SHOW_ITEM_LV_NOR || m_curUser->iShowLevel & mItem.iLv == mItem.iLv)
		return true;
	else
		return false;
}

const FIELD_ITEM* UserFeildManage::GetItem(uint8 iRow)
{
	if (!IsVaild(iRow))
		return NULL;
	return &m_curUser->listItem[iRow];
}

bool UserFeildManage::IsVaild(uint8 iRow, uint8 iColumn/*=0*/)
{
	if (!m_curUser || iRow >= this->GetFeildRow() || iColumn >= FeildColumn_Max)
		return false;
	else
		return true;
}

std::string UserFeildManage::GetResourcePath()
{
	return "";
}

std::string UserFeildManage::GetResourceFileName(const char* szFileName)
{
	std::string strPath = GetResourcePath();
	strPath.append("/");
	strPath.append(szFileName);
	return strPath;
}


