#include "UserFeildManage.h"
#include "depend/cantools/tools.h"

CField::CField()
{
}

CField::~CField()
{
}

void CField::ParsingStringCopy(const char* pIndex, void* pDest, uint32 iLen)
{
	memcpy(pDest, pIndex, iLen);
	pIndex += iLen;
}

void CField::ParsingString(const char* pSrc)
{
	if (!pSrc)
		return;
	const char* pIndex = pSrc;
	ParsingStringCopy(pIndex, &iLastLogoinTime, sizeof(iLastLogoinTime));
	ParsingStringCopy(pIndex, &iVaildLoginTime, sizeof(iVaildLoginTime));
	ParsingStringCopy(pIndex, &iShowItemTime, sizeof(iShowItemTime));
	ParsingStringCopy(pIndex, &iShowLevel, sizeof(iShowLevel));
	ParsingStringCopy(pIndex, &iHideParts, sizeof(iHideParts));

	ParsingStringCopy(pIndex, strName, sizeof(strName));
	ParsingStringCopy(pIndex, strPwd, sizeof(strPwd));

	uint32 iItemCount(0);
	ParsingStringCopy(pIndex, &iItemCount, sizeof(iItemCount));
	
	FIELD_ITEM mItem;
	for (uint32 i = 0; i < iItemCount; ++i)
	{
		memset(&mItem, 0, sizeof(mItem));

		ParsingStringCopy(pIndex, &mItem.id, sizeof(mItem.id));
		ParsingStringCopy(pIndex, &mItem.iLv, sizeof(mItem.iLv));

		ParsingStringCopy(pIndex, mItem.strNameNick, sizeof(mItem.strNameNick));
		ParsingStringCopy(pIndex, mItem.strAccount, sizeof(mItem.strAccount));
		ParsingStringCopy(pIndex, mItem.strLoginPwd, sizeof(mItem.strLoginPwd));
		ParsingStringCopy(pIndex, mItem.strPayPwd, sizeof(mItem.strPayPwd));
		ParsingStringCopy(pIndex, mItem.strOtherPwd, sizeof(mItem.strOtherPwd));
		ParsingStringCopy(pIndex, mItem.strRelation, sizeof(mItem.strRelation));
		ParsingStringCopy(pIndex, mItem.strDescribe, sizeof(mItem.strDescribe));

		listItem.push_back(mItem);
	}
}

bool CField::LoadBuffer(std::ifstream& rFile)
{
	if (!rFile.is_open())
		return false;
	uint32 iLen(0);
	rFile.read((char*)&iLen, sizeof(uint32));
	char* pNewData = new char[iLen+1];
	pNewData[iLen + 1] = '\0';
	rFile.read(pNewData, sizeof(iLen));
	ParsingString(pNewData);

	delete pNewData;
// 	rFile.read((char*)&iLastLogoinTime, sizeof(iLastLogoinTime));
// 	rFile.read((char*)&iVaildLoginTime, sizeof(iVaildLoginTime));
// 	rFile.read((char*)&iShowItemTime, sizeof(iShowItemTime));
// 	rFile.read((char*)&iShowLevel, sizeof(iShowLevel));
// 	rFile.read((char*)&iHideParts, sizeof(iHideParts));
// 	
// 	rFile.read(strName, sizeof(strName));
// 	rFile.read(strPwd, sizeof(strName));
// 
// 	uint32 iItemCount(0);
// 	rFile.read((char*)&iItemCount, sizeof(uint32));
// 
// 	FIELD_ITEM mItem;
// 	for (uint32 i = 0; i < iItemCount; ++i)
// 	{
// 		memset(&mItem,0, sizeof(mItem));
// 
// 		rFile.read((char*)&mItem.id, sizeof(mItem.id));
// 		rFile.read((char*)&mItem.iLv, sizeof(mItem.iLv));
// 
// 		rFile.read(mItem.strNameNick, sizeof(mItem.strNameNick));
// 		rFile.read(mItem.strAccount, sizeof(mItem.strAccount));
// 		rFile.read(mItem.strLoginPwd, sizeof(mItem.strLoginPwd));
// 		rFile.read(mItem.strPayPwd, sizeof(mItem.strPayPwd));
// 		rFile.read(mItem.strOtherPwd, sizeof(mItem.strOtherPwd));
// 		rFile.read(mItem.strRelation, sizeof(mItem.strRelation));
// 		rFile.read(mItem.strDescribe, sizeof(mItem.strDescribe));
// 
// 		listItem.push_back(mItem);
// 	}
	return true;
}

void CField::GetDataToChar(std::string& strOut)
{
	strOut.append((char*)&iLastLogoinTime, sizeof(iLastLogoinTime));
	strOut.append((char*)&iVaildLoginTime, sizeof(iVaildLoginTime));
	strOut.append((char*)&iShowItemTime, sizeof(iShowItemTime));
	strOut.append((char*)&iShowLevel, sizeof(iShowLevel));
	strOut.append((char*)&iHideParts, sizeof(iHideParts));

	strOut.append((char*)&strName, sizeof(strName));
	strOut.append((char*)&strPwd, sizeof(strPwd));

	uint32 iItemCount = listItem.size();
	strOut.append((char*)&iItemCount, sizeof(uint32));

	if (iItemCount == 0)
		return;

	VEC_ITEMS::iterator itor = listItem.begin(), itor_end = listItem.end();
	for (; itor != itor_end; ++itor)
	{
		strOut.append((char*)&(itor->id), sizeof(itor->id));
		strOut.append((char*)&(itor->iLv), sizeof(itor->iLv));

		strOut.append(itor->strNameNick, sizeof(itor->strNameNick));
		strOut.append(itor->strAccount, sizeof(itor->strAccount));
		strOut.append(itor->strLoginPwd, sizeof(itor->strLoginPwd));
		strOut.append(itor->strPayPwd, sizeof(itor->strPayPwd));
		strOut.append(itor->strOtherPwd, sizeof(itor->strOtherPwd));
		strOut.append(itor->strRelation, sizeof(itor->strRelation));
		strOut.append(itor->strDescribe, sizeof(itor->strDescribe));
	}
}

bool CField::WriteBuffer(std::ofstream& wFile)
{
	if (!wFile.is_open())
		return false;

	std::string strData;
	GetDataToChar(strData);
	uint32 iLen = strData.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strData.c_str(), strData.length());

	return true;
}

const char* CField::GetFieldString(uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField/* = NULL*/)
{
	if (!pField)
		if (!(pField = GetItem(iRow)))
			return NULL;

	switch (iColumn)
	{
	case FeildColumn_Nick:
		return pField->strNameNick;
	case FeildColumn_Account:
		return pField->strAccount;
	case FeildColumn_PwdLogin:
		return pField->strLoginPwd;
	case FeildColumn_PwdPay:
		return pField->strPayPwd;
	case FeildColumn_PwdOther:
		return pField->strOtherPwd;
	case FeildColumn_Relation:
		return pField->strRelation;
	case FeildColumn_Describe:
		return pField->strDescribe;
	default:
		return NULL;
	}
}

bool CField::IsVaild(uint8 iRow, uint8 iColumn /*= 0*/)
{
	if (iRow >= GetFeildRow() || iColumn >= FeildColumn_Max)
		return false;
	else
		return true;
}

const FIELD_ITEM* CField::GetItem(uint8 iRow)
{
	if (!IsVaild(iRow))
		return NULL;
	return &listItem[iRow];
}

bool CField::IsShowRow(uint8 iRow)
{
	const FIELD_ITEM* pField = GetItem(iRow);
	if (pField && (pField->iLv == SHOW_ITEM_LV_NOR || (iShowLevel&pField->iLv) == pField->iLv))
		return true;
	else
		return false;
}



CString CField::GetFeildItemCS(uint8 iRow, uint8 iColumn, bool isHideParts)
{
	const FIELD_ITEM* pField = GetItem(iRow);
	if (!pField)
		return CString();

	const char * szTemp = GetFieldString(iRow, iColumn, pField);
	if (!szTemp)
		return CString();

	CString strTemp(szTemp);
	uint32 iLen = strTemp.GetLength();

	if (IsNeedHideParts(isHideParts, iRow, iColumn, pField))
	{
		uint32 index = iLen / 4;
		uint32 iCount = max(1, index + index);
		CString strxx('*', 3);
		strTemp.Delete(index, iCount);
		strTemp.Insert(index, strxx);
	}
	return strTemp;
}

bool CField::IsNeedHideParts(bool isHideParts, uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField/* = NULL*/)
{
	if (!isHideParts)
		return false;

	if (!pField)
		if (!(pField = GetItem(iRow)))
			return false;

	if ((iHideParts&pField->iLv) == pField->iLv && (iColumn == FeildColumn_Account ||
		iColumn == FeildColumn_Relation || iColumn == FeildColumn_Describe))
		return true;
	else
		return false;
}



//////////////////////////////////////////////////////////////////////////
UserFeildManage* UserFeildManage::m_gShare=NULL;
UserFeildManage::UserFeildManage() :m_curUser(NULL)
{
}

UserFeildManage::~UserFeildManage()
{
	VEC_FEILDS::iterator itor;
	while (m_vecUserInfo.size())
	{
		itor = m_vecUserInfo.begin();
		delete (*itor);
		m_vecUserInfo.erase(itor);
	}
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
		//pFeild->strName = accounts[i]["Name"].GetString();
		//pSz = accounts[i]["Pwd"].GetString();
	//	if (pSz)
		{
			//std::string aesa = _CANNP_NAME::encrypt::EncryptAES(pSz, pwd);
		}
		
	}

	return true;
}

std::string UserFeildManage::UserLogoin(const std::string& straNme, const std::string& strPwd)
{
	
	if (!m_vecUserInfo.empty())
		return std::string("There haven't any user info,you need create one.");

	std::string strError;
	VEC_FEILDS::iterator itor = m_vecUserInfo.begin(),itor_end = m_vecUserInfo.end();
	for (; itor != itor_end; ++itor)
	{
		if ((*itor)->strName == straNme)
		{
			if ((*itor)->strPwd == strPwd)
			{
				m_curUser = (*itor);
				return strError;
			}
				
			else
				return std::string("PassWord error,input again!");
		}
	}

	return std::string("Account error,input again!");
}

CString UserFeildManage::GetFeildItemCS(uint8 iRow, uint8 iColumn, bool isHideParts/* = true*/)
{
	if (!m_curUser)
		return CString();
	else
		return m_curUser->GetFeildItemCS(iRow, iColumn, isHideParts);
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