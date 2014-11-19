#include "UserFieldManage.h"
#include "GobalConfig.h"
#include "depend/cantools/tools.h"

#define FLORD_NAME "Dont_Delete"
#define CONFIG_FILE "ConfigFile"
#define SETTING_FILE "ConfigFile"

CField::CField(uint32 iId) :m_iID(iId)
{

}

CField::~CField()
{
}

bool CField::ParsingString(const std::string& strSrc)
{
	uint32 iOffset(0),iIDTemp(0);

// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iId, sizeof(iId));
// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iLastLogoinTime, sizeof(iLastLogoinTime));
// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iVaildLoginTime, sizeof(iVaildLoginTime));
// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iShowItemTime, sizeof(iShowItemTime));
// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iShowLevel, sizeof(iShowLevel));
// 	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iHideParts, sizeof(iHideParts));

	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iIDTemp, sizeof(iIDTemp));
	if (m_iID != iIDTemp)
		return false;

	uint32 iItemCount(0),iItemR(0);
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iItemCount, sizeof(iItemCount));
	
	FIELD_ITEM mItem;
	FIELD_PWD_RECORD mItemR;
	for (uint32 i(0),j(0); i < iItemCount; ++i)
	{
		memset(&mItem, 0, sizeof(mItem));
		mItem.id = i;
		//ParsingStringCopy(pIndex, &mItem.id, sizeof(mItem.id));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItem.iLv, sizeof(mItem.iLv));

		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strNameNick, sizeof(mItem.strNameNick));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strAccount, sizeof(mItem.strAccount));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strLoginPwd, sizeof(mItem.strLoginPwd));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strPayPwd, sizeof(mItem.strPayPwd));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strOtherPwd, sizeof(mItem.strOtherPwd));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strRelation, sizeof(mItem.strRelation));
		UserFieldManage::ParsingStringCopy(strSrc, iOffset, mItem.strDescribe, sizeof(mItem.strDescribe));

		UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iItemR, sizeof(iItemR));
		for (j = 0; j < iItemR; ++j)
		{
			memset(&mItemR, 0, sizeof(mItemR));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.iMTime, sizeof(mItemR.iMTime));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.strOldPwd, sizeof(mItemR.strOldPwd));
			mItem.vecLogoin.push_back(mItemR);
		}

		UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iItemR, sizeof(iItemR));
		for (j = 0; j < iItemR; ++j)
		{
			memset(&mItemR, 0, sizeof(mItemR));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.iMTime, sizeof(mItemR.iMTime));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.strOldPwd, sizeof(mItemR.strOldPwd));
			mItem.vecPay.push_back(mItemR);
		}

		UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iItemR, sizeof(iItemR));
		for (j = 0; j < iItemR; ++j)
		{
			memset(&mItemR, 0, sizeof(mItemR));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.iMTime, sizeof(mItemR.iMTime));
			UserFieldManage::ParsingStringCopy(strSrc, iOffset, &mItemR.strOldPwd, sizeof(mItemR.strOldPwd));
			mItem.vecOther.push_back(mItemR);
		}

		listItem.push_back(mItem);
	}

	return true;
}
bool CField::ReadBuffer(const std::string& strName, const std::string& strPwd)
{
	std::string strDe(""), strBasePwd(strPwd);;
	if (UserFieldManage::Share()->ReadInfo(strName, strDe, strBasePwd))
	{
		if (!strDe.empty())
		{
			if (!ParsingString(strDe))
				UserFieldManage::Share()->SaveCopyOfError(strName);
			else
				return true;
		}
	}
			
	return false;
}

void CField::GetDataToChar(std::string& strOut)
{
// 	strOut.append((char*)&iId, sizeof(iId));
// 	strOut.append((char*)&iLastLogoinTime, sizeof(iLastLogoinTime));
// 	strOut.append((char*)&iVaildLoginTime, sizeof(iVaildLoginTime));
// 	strOut.append((char*)&iShowItemTime, sizeof(iShowItemTime));
// 	strOut.append((char*)&iShowLevel, sizeof(iShowLevel));
// 	strOut.append((char*)&iHideParts, sizeof(iHideParts));

	uint32 iItemCount = listItem.size();

	strOut.append((char*)&m_iID, sizeof(m_iID));
	strOut.append((char*)&iItemCount, sizeof(uint32));

	if (iItemCount == 0)
		return;

	uint32 iRCount(0);
	VEC_ITEMS::iterator itor = listItem.begin();
	VEC_PWD_RECORD::iterator itors;
	for (int i = 0,j=0; i < iItemCount; ++i, ++itor)
	{
		strOut.append((char*)&(itor->iLv), sizeof(itor->iLv));

		strOut.append(itor->strNameNick, sizeof(itor->strNameNick));
		strOut.append(itor->strAccount, sizeof(itor->strAccount));
		strOut.append(itor->strLoginPwd, sizeof(itor->strLoginPwd));
		strOut.append(itor->strPayPwd, sizeof(itor->strPayPwd));
		strOut.append(itor->strOtherPwd, sizeof(itor->strOtherPwd));
		strOut.append(itor->strRelation, sizeof(itor->strRelation));
		strOut.append(itor->strDescribe, sizeof(itor->strDescribe));
		
		iRCount = itor->vecLogoin.size();
		itors = itor->vecLogoin.begin();
		strOut.append(iRCount, sizeof(iRCount));
		for (j = 0; j < iRCount; ++j,++itors)
		{
			strOut.append((char*)&(itors->iMTime), sizeof(itors->iMTime));
			strOut.append((char*)&(itors->strOldPwd), sizeof(itors->strOldPwd));
		}

		iRCount = itor->vecPay.size();
		itors = itor->vecPay.begin();
		strOut.append(iRCount, sizeof(iRCount));
		for (j = 0; j < iRCount; ++j, ++itors)
		{
			strOut.append((char*)&(itors->iMTime), sizeof(itors->iMTime));
			strOut.append((char*)&(itors->strOldPwd), sizeof(itors->strOldPwd));
		}

		iRCount = itor->vecOther.size();
		itors = itor->vecOther.begin();
		strOut.append(iRCount, sizeof(iRCount));
		for (j = 0; j < iRCount; ++j, ++itors)
		{
			strOut.append((char*)&(itors->iMTime), sizeof(itors->iMTime));
			strOut.append((char*)&(itors->strOldPwd), sizeof(itors->strOldPwd));
		}
	}

}

void CField::WriteBuffer(const std::string& strName, const std::string& strPwd)
{
	std::string strData;
	GetDataToChar(strData);

	UserFieldManage::Share()->WriteInfo(strName, strData, strPwd);
}

void CField::WriteUserSet(const std::string& strName, const std::string& strPwd)
{
	std::string strOut(""), strNameAdd(strName);
	uint32 iOffset(0);

	strOut.append((char*)&m_iID, sizeof(m_iID));
	strOut.append((char*)&m_userSet.iLastLogoinTime, sizeof(m_userSet.iLastLogoinTime));
	strOut.append((char*)&m_userSet.iVaildLoginTime, sizeof(m_userSet.iVaildLoginTime));
	strOut.append((char*)&m_userSet.iShowItemTime, sizeof(m_userSet.iShowItemTime));
	strOut.append((char*)&m_userSet.iShowLevel, sizeof(m_userSet.iShowLevel));
	strOut.append((char*)&m_userSet.iHideParts, sizeof(m_userSet.iHideParts));
	
	strNameAdd.append(SETTING_FILE);
	UserFieldManage::Share()->WriteInfo(strNameAdd, strOut, strPwd);
}

bool CField::ReadUserSet(const std::string& strName, const std::string& strPwd)
{
	std::string strDe(""), strBasePwd(strPwd), strNameAdd(strName);
	uint32 iOffset(0),iIdTemp(0);
	strNameAdd.append(SETTING_FILE);
	if (UserFieldManage::Share()->ReadInfo(strNameAdd, strDe, strBasePwd))
	{

		UserFieldManage::ParsingStringCopy(strDe, iOffset, &iIdTemp, sizeof(iIdTemp));
		if (iIdTemp != m_iID)
			return false;

		UserFieldManage::ParsingStringCopy(strDe, iOffset, &m_userSet.iLastLogoinTime, sizeof(m_userSet.iLastLogoinTime));
		UserFieldManage::ParsingStringCopy(strDe, iOffset, &m_userSet.iVaildLoginTime, sizeof(m_userSet.iVaildLoginTime));
		UserFieldManage::ParsingStringCopy(strDe, iOffset, &m_userSet.iShowItemTime, sizeof(m_userSet.iShowItemTime));
		UserFieldManage::ParsingStringCopy(strDe, iOffset, &m_userSet.iShowLevel, sizeof(m_userSet.iShowLevel));
		UserFieldManage::ParsingStringCopy(strDe, iOffset, &m_userSet.iHideParts, sizeof(m_userSet.iHideParts));

		return true;
	}
	else
		return false;
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
	if (pField && (pField->iLv == SHOW_ITEM_LV_NOR || (m_userSet.iShowLevel&pField->iLv) == pField->iLv))
		return true;
	else
		return false;
}

CString CField::GetFieldItemCS(uint8 iRow, uint8 iColumn, bool isNeedHide)const
{
	const FIELD_ITEM* pField = GetItem(iRow);
	if (!pField)
		return CString();

	const char * szTemp = GetFieldString(iRow, iColumn, pField);
	if (!szTemp)
		return CString();

	CString strTemp(szTemp);
	uint32 iLen = strTemp.GetLength();

	if (IsNeedHideParts(isNeedHide, iRow, iColumn, pField))
	{
		uint32 index = iLen / 4;
		uint32 iCount = max(1, index + index);
		CString strxx('*', 3);
		strTemp.Delete(index, iCount);
		strTemp.Insert(index, strxx);
	}
	return strTemp;
}

bool CField::IsNeedHideParts(bool isNeedHide, uint8 iRow, uint8 iColumn, const FIELD_ITEM* pField/* = NULL*/)const
{
	if (!isNeedHide)
		return false;

	if (!pField)
		if (!(pField = GetItem(iRow)))
			return false;

	if ((m_userSet.iHideParts&pField->iLv) == pField->iLv && (iColumn == FieldColumn_Account ||
		iColumn == FieldColumn_Relation || iColumn == FieldColumn_Describe))
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////
UserFieldManage* UserFieldManage::m_gShare=NULL;
UserFieldManage::UserFieldManage() :m_pCurUser(NULL)
{
}

UserFieldManage::~UserFieldManage()
{
	if (m_pCurUser)
		delete m_pCurUser;
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
	if (!LoadConfigField(CONFIG_FILE))
		isCreate = true;

	if (isCreate)
	{
		m_ConfigInfo.iCurID = 1;
		CGobalConfig::Share()->CreateRandStr(32, m_ConfigInfo.strFieldPwd);
		m_ConfigInfo.strFieldPwd[32] = '\0';
		CGobalConfig::Share()->CreateRandStr(32, m_ConfigInfo.strPwdPwd);
		m_ConfigInfo.strPwdPwd[32] = '\0';

		m_strBasePwd.clear();
		CGobalConfig::Share()->CreateRandStr(MAX_LEN_PWD, m_strBasePwd);
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

std::string UserFieldManage::GetResourceFileNameMD5(const char* szFileName, const char* szAdd/*=NULL*/)
{
	STDSTR strName(szFileName), strMd5("");
	if (szAdd)	
		strName.append(szAdd);

	_CANNP_NAME::encrypt::EncryptMD5(strName.c_str(), strName.length(), strMd5);
	return this->GetResourceFileName(strMd5.c_str());
}

void  UserFieldManage::SaveCopyOfError(const std::string& strName)
{
	STDSTR strPath, strMd5, strFileName;

	strPath = GetResourcePath();
	_CANNP_NAME::encrypt::EncryptMD5(strName.c_str(), strName.length(), strMd5);

	strFileName = GetResourceFileName(strMd5.c_str());
	std::ifstream rFile(strFileName.c_str(), std::ios::binary | std::ios::in);

	strPath.append("/ErrorCopy/");
	CreateDirectoryA(strPath.c_str(), NULL);

	strPath.append(strMd5);
	time_t mTime = time(NULL);
	char tmp[64]="";
	tm mmTime;
	localtime_s(&mmTime, &mTime);
	sprintf_s(tmp, "%02d%02d%02d%02d", mmTime.tm_year - 100, mmTime.tm_mon, mmTime.tm_mday, mmTime.tm_hour);
	strPath.append(tmp);
	strPath.append(".can");

	rFile.seekg(0, std::ios::end);
	std::streampos psEnd = rFile.tellg();
	rFile.seekg(0, std::ios::beg);
	uint32 iSize = psEnd;
	char* pBuffer = new char[iSize + 1];
	rFile.read(pBuffer, iSize);
	pBuffer[iSize] = '\0';
	rFile.close();

	std::ofstream wFile(strPath.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
	wFile.write(pBuffer, iSize);
	wFile.close();

	delete pBuffer;
}

bool UserFieldManage::UserLogoinSuccess(Account_Info* pInfo)
{
	m_pCurAccount = pInfo;
	m_pCurUser = new CField(m_pCurAccount->iId);
	
	if (!m_pCurUser->ReadBuffer(pInfo->strName, m_strBasePwd))
		m_pCurUser->WriteBuffer(pInfo->strName, m_strBasePwd);
	
	if (!m_pCurUser->ReadUserSet(pInfo->strName, m_strBasePwd))
		m_pCurUser->WriteUserSet(pInfo->strName, m_strBasePwd);

	return true;
}

uint8 UserFieldManage::UserLogoin(const char* szName, const char* szPwd, ELOGOIN_MODE mmode/*=ELOGOIN_MODE_NOR*/)
{
	if (m_ConfigInfo.vecUse.empty())
		return ER_ERROR;

	STDSTR strTemp, strMd5;
	_CANNP_NAME::encrypt::EncryptMD5(szPwd, strlen(szPwd), strMd5);

	VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin();
	for (; itor != m_ConfigInfo.vecUse.end(); ++itor)
	{
		if (strcmp(itor->strName, szName) == 0)
		{
			if (mmode == ELOGOIN_MODE_NOR)
				strTemp = itor->strPwd;
			else
				strTemp = itor->strOPwd;

			if (strMd5.compare(strTemp) == 0)
			{
				if (mmode == ELOGOIN_MODE_NOR)
					UserLogoinSuccess(&(*itor));

				return ER_SUCCESS;
			}
			else
				return ER_ERROR_PWD;
		}
	}

	return ER_ERROR_ACCOUNT;
}

void UserFieldManage::SaveConfigField()
{
	std::string strBuff;
	strBuff.append((char*)&m_ConfigInfo.iCurID, sizeof(m_ConfigInfo.iCurID));
	strBuff.append((char*)&m_ConfigInfo.strFieldPwd, MAX_LEN_PWD);
	strBuff.append((char*)&m_ConfigInfo.strPwdPwd, MAX_LEN_PWD);

	uint32 iUCount(m_ConfigInfo.vecUse.size());
	uint32 iACount = m_ConfigInfo.vecAbandon.size();
	strBuff.append((char*)&iUCount, sizeof(iUCount));
	strBuff.append((char*)&iACount, sizeof(iACount));
	
	
	if (iUCount > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin();
		for (int i = 0; i < iUCount; ++i, ++itor)
		{
			strBuff.append((char*)&itor->iId, sizeof(itor->iId));
			strBuff.append((char*)&itor->strName, MAX_LEN_NAME);
			strBuff.append((char*)&itor->strPwd, MAX_LEN_PWD);
			strBuff.append((char*)&itor->strOPwd, MAX_LEN_PWD);
		}
	}
	
	if (iACount > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecAbandon.begin();
		for (int i = 0; i < iUCount; ++i, ++itor)
		{
			strBuff.append((char*)&itor->iId, sizeof(itor->iId));
			strBuff.append((char*)&itor->strName, MAX_LEN_NAME);
			strBuff.append((char*)&itor->strPwd, MAX_LEN_PWD);
			strBuff.append((char*)&itor->strOPwd, MAX_LEN_PWD);
		}
	}
	
	WriteInfo(CONFIG_FILE, strBuff, m_strBasePwd,true);
}

void UserFieldManage::WriteInfo(const std::string& strName, const std::string& strSrc, const std::string& strBasePwd, bool isMainConfig/* = false*/)
{
	std::string strValue(""), strEn(""), strEnPwd(""),strHead(""),strHeadEn("");
	uint32 iLen(0);

	std::ofstream wFile(GetResourceFileNameMD5(strName.c_str()).c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
	
	CGobalConfig::Share()->CreateRandStr(MAX_LEN_PWD, strEnPwd);

	_CANNP_NAME::encrypt::EncryptAES(strEnPwd.c_str(), strEnPwd.c_str(), strValue);

	strHead.append(strValue);
	strHead.append(strEnPwd);
	if (isMainConfig)
		strHead.append(strBasePwd);
	_CANNP_NAME::encrypt::EncryptBuffer(strHead.c_str(), strHead.length(), strName.c_str(), strHeadEn);
	iLen = strHeadEn.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strHeadEn.c_str(), iLen);

	strEnPwd.append(strBasePwd);
	_CANNP_NAME::encrypt::EncryptBuffer(strSrc.c_str(), strSrc.length(), strEnPwd.c_str(), strEn);
	iLen = strSrc.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	iLen = strEn.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strEn.c_str(), strEn.length());

	wFile.close();
}

bool UserFieldManage::ReadInfo(const std::string& strName, std::string& strOut, std::string& strBasePwd /*= std::string()*/)
{
	STDSTR strFileName = GetResourceFileNameMD5(strName.c_str());
	std::ifstream rFile(strFileName.c_str(), std::ios::binary | std::ios::in);
	if (!rFile)
		return false;
	
	strOut.clear();

	uint32 iLen(0);
	std::string strDes(""), strPwd(""), strValue("");
	
	rFile.read((char*)&iLen, sizeof(iLen));
	char* pHeads = new char[iLen + 1];
	rFile.read(pHeads, iLen);
	pHeads[iLen] = '\0';

	_CANNP_NAME::encrypt::DecryptBuffer(pHeads, iLen, strName.c_str(), strDes);
	delete pHeads;

	strValue = strDes.substr(0, MAX_LEN_AES);
	strPwd = strDes.substr(MAX_LEN_AES, MAX_LEN_PWD);
	if (iLen>MAX_LEN_AES + MAX_LEN_PWD)
		strBasePwd = strDes.substr(MAX_LEN_AES+MAX_LEN_PWD, MAX_LEN_PWD);

	_CANNP_NAME::encrypt::EncryptAES(strPwd.c_str(), strPwd.c_str(), strDes);
	bool isSuccess(false);
	if (strDes.compare(strValue) == 0) //Verification
	{
		uint32 iDecLen, iEncLen(0);
		rFile.read((char*)&iDecLen, sizeof(iDecLen));
		rFile.read((char*)&iEncLen, sizeof(iEncLen));

		std::streampos ps = rFile.tellg();
		rFile.seekg(0, std::ios::end);
		std::streampos psEnd = rFile.tellg();

		if (iEncLen == psEnd - ps)
		{
			rFile.seekg(ps, std::ios::beg);

			char* pBuffer = new char[iEncLen + 1];
			pBuffer[iEncLen] = '\0';
			rFile.read(pBuffer, iEncLen);

			strPwd.append(strBasePwd);
			_CANNP_NAME::encrypt::DecryptBuffer(pBuffer, iEncLen, strPwd.c_str(), strOut);
			delete pBuffer;
			pBuffer = NULL;

			isSuccess = true;
		}
	}
	rFile.close();

	if (!isSuccess)
		SaveCopyOfError(strName);
	
	return isSuccess;
}

bool UserFieldManage::LoadConfigField(const std::string& strName)
{
	std::string strDes;
	if (ReadInfo(strName, strDes, m_strBasePwd))
	{
		if (strDes.empty())
			return true;

		uint32 iOffset(0);
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &m_ConfigInfo.iCurID, sizeof(m_ConfigInfo.iCurID));
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &m_ConfigInfo.strFieldPwd, MAX_LEN_PWD);
		UserFieldManage::ParsingStringCopy(strDes,iOffset, &m_ConfigInfo.strPwdPwd, MAX_LEN_PWD);

		uint32 iUCount(0),iAcount(0);
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &iUCount, sizeof(iUCount));
		UserFieldManage::ParsingStringCopy(strDes, iOffset, &iAcount, sizeof(iAcount));

		Account_Info mInfo;
		for (uint32 i = 0; i < iUCount; ++i)
		{
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.iId, sizeof(mInfo.iId));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_PWD);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strOPwd, MAX_LEN_PWD);
			m_ConfigInfo.vecUse.push_back(mInfo);
		}
		
		for (uint32 i = 0; i < iAcount; ++i)
		{
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.iId, sizeof(mInfo.iId));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_PWD);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strOPwd, MAX_LEN_PWD);
			m_ConfigInfo.vecAbandon.push_back(mInfo);
		}

		return true;
	}
	else
		return false;
}

uint32 UserFieldManage::GetUserCount(VEC_STR& vecOut, bool isUse/* = true*/)
{
	VEC_ACCOUNTS::iterator itor;
	if (isUse)
	{
		if (m_ConfigInfo.vecUse.empty())
			return 0;

		for (itor = m_ConfigInfo.vecUse.begin(); itor != m_ConfigInfo.vecUse.end(); ++itor)
			vecOut.push_back(itor->strName);
	}
	else
	{
		if (m_ConfigInfo.vecAbandon.empty())
			return 0;

		for (itor = m_ConfigInfo.vecAbandon.begin(); itor != m_ConfigInfo.vecAbandon.end(); ++itor)
			vecOut.push_back(itor->strName);
	}
	
	return vecOut.size();
}

uint32 UserFieldManage::GetUserCount(bool isUse/* = true*/)
{
	if (isUse)
		return m_ConfigInfo.vecUse.size();
	else
		return m_ConfigInfo.vecAbandon.size();
}

uint32 UserFieldManage::CreateAccount(const std::string& strA, const std::string& strP, const std::string& strOP)
{
	if (m_ConfigInfo.vecUse.size() > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin();
		for (; itor != m_ConfigInfo.vecUse.end(); ++itor)
		{
			if (strcmp(itor->strName, strA.c_str()) == 0)
				return 0;
		}
	}

	Account_Info mAccountInfo;

	++m_ConfigInfo.iCurID;
	mAccountInfo.iId = m_ConfigInfo.iCurID;
	memcpy_s(mAccountInfo.strName, MAX_LEN_NAME, strA.c_str(), strA.length());
	std::string strMd5,strOMd5;
	_CANNP_NAME::encrypt::EncryptMD5(strP.c_str(), strP.length(), strMd5);
	memcpy_s(mAccountInfo.strPwd, MAX_LEN_PWD, strMd5.c_str(), strMd5.length());
	_CANNP_NAME::encrypt::EncryptMD5(strOP.c_str(), strOP.length(), strOMd5);
	memcpy_s(mAccountInfo.strOPwd, MAX_LEN_PWD, strOMd5.c_str(), strOMd5.length());
	
	m_ConfigInfo.vecUse.push_back(mAccountInfo);

	SaveConfigField();
	return mAccountInfo.iId;
}

bool UserFieldManage::VerifyAccount(CONST_STDSTR& strAccount)
{
	if (strAccount.empty())
		return false;

	for (VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin(); itor != m_ConfigInfo.vecUse.end(); ++itor)
	{
		if (strAccount.compare(itor->strName) == 0)
			return true;
	}
	
	return false;
}



