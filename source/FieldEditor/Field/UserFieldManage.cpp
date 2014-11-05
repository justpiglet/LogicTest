#include "UserFieldManage.h"
#include "GobalConfig.h"
#include "depend/cantools/tools.h"

#define FLORD_NAME "Dont_Delete"
#define CONFIG_FILE "f68dc1044703e358580461aec4504fdf"

CField::CField()
{
}

CField::~CField()
{
}

void CField::ParsingString(const char* pSrc)
{
	if (!pSrc)
		return;
	const char* pIndex = pSrc;
	UserFieldManage::ParsingStringCopy(pIndex, &iLastLogoinTime, sizeof(iLastLogoinTime));
	UserFieldManage::ParsingStringCopy(pIndex, &iVaildLoginTime, sizeof(iVaildLoginTime));
	UserFieldManage::ParsingStringCopy(pIndex, &iShowItemTime, sizeof(iShowItemTime));
	UserFieldManage::ParsingStringCopy(pIndex, &iShowLevel, sizeof(iShowLevel));
	UserFieldManage::ParsingStringCopy(pIndex, &iHideParts, sizeof(iHideParts));

	UserFieldManage::ParsingStringCopy(pIndex, strName, sizeof(strName));
	UserFieldManage::ParsingStringCopy(pIndex, strPwd, sizeof(strPwd));

	uint32 iItemCount(0);
	UserFieldManage::ParsingStringCopy(pIndex, &iItemCount, sizeof(iItemCount));
	
	FIELD_ITEM mItem;
	for (uint32 i = 0; i < iItemCount; ++i)
	{
		memset(&mItem, 0, sizeof(mItem));
		mItem.id = i;
		//ParsingStringCopy(pIndex, &mItem.id, sizeof(mItem.id));
		UserFieldManage::ParsingStringCopy(pIndex, &mItem.iLv, sizeof(mItem.iLv));

		UserFieldManage::ParsingStringCopy(pIndex, mItem.strNameNick, sizeof(mItem.strNameNick));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strAccount, sizeof(mItem.strAccount));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strLoginPwd, sizeof(mItem.strLoginPwd));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strPayPwd, sizeof(mItem.strPayPwd));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strOtherPwd, sizeof(mItem.strOtherPwd));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strRelation, sizeof(mItem.strRelation));
		UserFieldManage::ParsingStringCopy(pIndex, mItem.strDescribe, sizeof(mItem.strDescribe));

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
		//strOut.append((char*)&(itor->id), sizeof(itor->id));
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

const char* CField::GetFieldString(uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField/* = NULL*/)const
{
	if (!pField)
		if (!(pField = GetItem(iRow)))
			return NULL;

	switch (iColumn)
	{
	case FieldColumn_Nick:
		return pField->strNameNick;
	case FieldColumn_Account:
		return pField->strAccount;
	case FieldColumn_PwdLogin:
		return pField->strLoginPwd;
	case FieldColumn_PwdPay:
		return pField->strPayPwd;
	case FieldColumn_PwdOther:
		return pField->strOtherPwd;
	case FieldColumn_Relation:
		return pField->strRelation;
	case FieldColumn_Describe:
		return pField->strDescribe;
	default:
		return NULL;
	}
}

bool CField::IsVaild(uint8 iRow, uint8 iColumn /*= 0*/)const
{
	if (iRow >= GetFieldRow() || iColumn >= FieldColumn_Max)
		return false;
	else
		return true;
}

const FIELD_ITEM* CField::GetItem(uint8 iRow)const
{
	if (!IsVaild(iRow))
		return NULL;
	return &listItem[iRow];
}

bool CField::IsShowRow(uint8 iRow)const
{
	const FIELD_ITEM* pField = GetItem(iRow);
	if (pField && (pField->iLv == SHOW_ITEM_LV_NOR || (iShowLevel&pField->iLv) == pField->iLv))
		return true;
	else
		return false;
}



CString CField::GetFieldItemCS(uint8 iRow, uint8 iColumn, bool isHideParts)const
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

bool CField::IsNeedHideParts(bool isHideParts, uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField/* = NULL*/)const
{
	if (!isHideParts)
		return false;

	if (!pField)
		if (!(pField = GetItem(iRow)))
			return false;

	if ((iHideParts&pField->iLv) == pField->iLv && (iColumn == FieldColumn_Account ||
		iColumn == FieldColumn_Relation || iColumn == FieldColumn_Describe))
		return true;
	else
		return false;
}



//////////////////////////////////////////////////////////////////////////
UserFieldManage* UserFieldManage::m_gShare=NULL;
UserFieldManage::UserFieldManage() :m_curUser(NULL)
{
}

UserFieldManage::~UserFieldManage()
{
	if (m_curUser)
		delete m_curUser;
}

UserFieldManage* UserFieldManage::Share()
{
	if (!m_gShare)
		m_gShare = new UserFieldManage;

	return m_gShare;
}

bool UserFieldManage::InitData()
{
	CreateDirectoryA(GetResourcePath().c_str(), NULL);

	bool isCreate(false);
	std::ifstream rFile(GetResourceFileName(CONFIG_FILE).c_str(), std::ios::binary | std::ios::in);
	if (rFile)
	{
		LoadConfigField(rFile);
	}
	else
		isCreate = true;

	if (isCreate)
	{
		CGobalConfig::Share()->CreateRandStr(32, m_ConfigInfo.strFieldPwd);
		m_ConfigInfo.strFieldPwd[32] = '\0';
		CGobalConfig::Share()->CreateRandStr(32, m_ConfigInfo.strPwdPwd);
		m_ConfigInfo.strPwdPwd[32] = '\0';

		SaveConfigField();
	}
	
	return true;
}

std::string UserFieldManage::GetResourcePath()
{
	return FLORD_NAME;
}

std::string UserFieldManage::GetResourceFileName(const char* szFileName)
{
	std::string strPath = GetResourcePath();
	strPath.append("/");
	strPath.append(szFileName);
	strPath.append(".can");
	return strPath;
}

std::string UserFieldManage::UserLogoin(const std::string& straNme, const std::string& strPwd)
{
	
// 	if (!m_vecUserInfo.empty())
// 		return std::string("There haven't any user info,you need create one.");
// 
// 	std::string strError;
// 	VEC_FEILDS::iterator itor = m_vecUserInfo.begin(),itor_end = m_vecUserInfo.end();
// 	for (; itor != itor_end; ++itor)
// 	{
// 		if ((*itor)->strName == straNme)
// 		{
// 			if ((*itor)->strPwd == strPwd)
// 			{
// 				m_curUser = (*itor);
// 				return strError;
// 			}
// 				
// 			else
// 				return std::string("PassWord error,input again!");
// 		}
// 	}
// 
	return std::string("Account error,input again!");
}

void UserFieldManage::SaveConfigField()
{
	std::ofstream wFile(GetResourceFileName(CONFIG_FILE).c_str(), std::ios::binary | std::ios::out | std::ios::trunc);

	std::string strValue;
	char szPwd[MAX_LEN_PWD+1] = "";
	CGobalConfig::Share()->CreateRandStr(MAX_LEN_PWD, szPwd);
	_CANNP_NAME::encrypt::EncryptAES(szPwd, szPwd, strValue);
	wFile.write(szPwd, MAX_LEN_PWD);
	wFile.write(strValue.c_str(), MAX_LEN_AES);
	//wFile.flush();

	std::string strBuff;
	strBuff.append((char*)&m_ConfigInfo.strFieldPwd, MAX_LEN_PWD);
	strBuff.append((char*)&m_ConfigInfo.strPwdPwd, MAX_LEN_PWD);

	uint32 iCount(m_ConfigInfo.vecUse.size());
	strBuff.append((char*)&iCount, sizeof(iCount));

	if (iCount > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin(), itor_end = m_ConfigInfo.vecUse.end();
		for (; itor != itor_end; ++itor)
		{
			strBuff.append((char*)&itor->strName, MAX_LEN_NAME);
			strBuff.append((char*)&itor->strPwd, MAX_LEN_PWD);
		}
	}
	
	iCount = m_ConfigInfo.vecAbandon.size();
	strBuff.append((char*)&iCount, sizeof(iCount));
	if (iCount > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecAbandon.begin(), itor_end = m_ConfigInfo.vecAbandon.end();
		for (; itor != itor_end; ++itor)
		{
			strBuff.append((char*)&itor->strName, MAX_LEN_NAME);
			strBuff.append((char*)&itor->strPwd, MAX_LEN_PWD);
		}
	}

	std::string strEn;
	_CANNP_NAME::encrypt::EncryptBuffer(strBuff.c_str(), strBuff.length(), szPwd, strEn);
	uint32 iLen(strBuff.length());
	wFile.write((char*)&iLen, sizeof(iLen));
	iLen = strEn.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strEn.c_str(), strEn.length());
	
	wFile.close();
}

bool UserFieldManage::LoadConfigField(std::ifstream& rFile)
{
	char szPwd[DEFINE_LEN_PWD] = "", szResult[DEFINE_LEN_AES] = "";
	rFile.read(szPwd, MAX_LEN_PWD);
	rFile.read(szResult, MAX_LEN_AES);
	std::string strDes;
	_CANNP_NAME::encrypt::EncryptAES(szPwd, szPwd, strDes);
	if (strDes.compare(szResult) == 0) //Verification
	{
		uint32 iDecLen,iEncLen(0);
		rFile.read((char*)&iDecLen, sizeof(iDecLen));
		rFile.read((char*)&iEncLen, sizeof(iEncLen));

		std::streampos ps = rFile.tellg();
		rFile.seekg(0, std::ios::end);
		std::streampos psEnd = rFile.tellg();
		
		if (iEncLen != psEnd - ps)
			return false;

		rFile.seekg(ps, std::ios::beg);

		char* pBuffer = new char[iEncLen + 1];
		pBuffer[iEncLen] = '\0';
		rFile.read(pBuffer, iEncLen);

		std::string strDes;
		_CANNP_NAME::encrypt::DecryptBuffer(pBuffer, iEncLen, szPwd, strDes);
		delete pBuffer;
		pBuffer = NULL;

		uint32 iOffset(0);
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &m_ConfigInfo.strFieldPwd, MAX_LEN_PWD);
		UserFieldManage::ParsingStringCopy(strDes,iOffset, &m_ConfigInfo.strPwdPwd, MAX_LEN_PWD);

		uint32 iTemp(0);
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &iTemp, sizeof(iTemp));
		Account_Info mInfo;
		for (uint32 i = 0; i < iTemp; ++i)
		{
			memset(&mInfo, 0, sizeof(mInfo));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_AES);
			m_ConfigInfo.vecUse.push_back(mInfo);
		}
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &iTemp, sizeof(iTemp));
		for (uint32 i = 0; i < iTemp; ++i)
		{
			memset(&mInfo, 0, sizeof(mInfo));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_PWD);
			m_ConfigInfo.vecAbandon.push_back(mInfo);
		}

		return true;
	}
	else
		return false;
}
