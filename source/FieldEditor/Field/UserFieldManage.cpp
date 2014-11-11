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

void CField::ParsingString(const std::string& strSrc)
{
	if (strSrc.empty())
		return;
	uint32 iOffset(0);

	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iId, sizeof(iId));
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iLastLogoinTime, sizeof(iLastLogoinTime));
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iVaildLoginTime, sizeof(iVaildLoginTime));
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iShowItemTime, sizeof(iShowItemTime));
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iShowLevel, sizeof(iShowLevel));
	UserFieldManage::ParsingStringCopy(strSrc, iOffset, &iHideParts, sizeof(iHideParts));

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
}

bool CField::LoadBuffer(std::ifstream& rFile, const std::string& strName, const std::string& strPwd)
{
	if (!rFile.is_open())
		return false;
	uint32 iLen(0),iEnLen(0);
	rFile.read((char*)&iLen, sizeof(uint32));
	rFile.read((char*)&iEnLen, sizeof(uint32));
	char* pNewData = new char[iLen+1];
	pNewData[iLen] = '\0';
	rFile.read(pNewData, sizeof(iLen));

	std::string strDe(""),strEnPwd(strPwd);
	strEnPwd.append(strName);
	const char *pEnSrc = pNewData;
	_CANNP_NAME::encrypt::DecryptBuffer(pEnSrc, iLen, strEnPwd.c_str(), strDe);
	delete pNewData;
	ParsingString(strDe.c_str());
	return true;
}

void CField::GetDataToChar(std::string& strOut)
{
	
	strOut.append((char*)&iId, sizeof(iId));
	strOut.append((char*)&iLastLogoinTime, sizeof(iLastLogoinTime));
	strOut.append((char*)&iVaildLoginTime, sizeof(iVaildLoginTime));
	strOut.append((char*)&iShowItemTime, sizeof(iShowItemTime));
	strOut.append((char*)&iShowLevel, sizeof(iShowLevel));
	strOut.append((char*)&iHideParts, sizeof(iHideParts));

	uint32 iItemCount = listItem.size();
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
	std::string strFilePath = UserFieldManage::Share()->GetResourceFileName(strName.c_str());
	std::ofstream wFile(strFilePath.c_str(), std::ios::binary | std::ios::out);
	if (!wFile.is_open())
		return ;

	std::string strData;
	GetDataToChar(strData);
	uint32 iLen = strData.length();
	wFile.write((char*)&iLen, sizeof(iLen));

	std::string strEn, strEnPwd(strPwd);
	strEnPwd.append(strName);

	_CANNP_NAME::encrypt::EncryptBuffer(strData.c_str(), strData.length(), strEnPwd.c_str(), strEn);
	
	iLen = strEn.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strEn.c_str(), strEn.length());
	
	wFile.close();
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

	if ((iHideParts&pField->iLv) == pField->iLv && (iColumn == FieldColumn_Account ||
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

void  UserFieldManage::SaveCopyOfError(std::ifstream& rFile, const std::string& strName)
{
	std::string strPath = GetResourcePath();
	strPath.append("/ErrorCopy/");
	CreateDirectoryA(strPath.c_str(), NULL);

	strPath.append(strName);
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

	std::ofstream wFile(strPath.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
	wFile.write(pBuffer, iSize);
	wFile.close();

	delete pBuffer;
}

bool UserFieldManage::UserLogoinSuccess(Account_Info* pInfo)
{
	m_pCurAccount = pInfo;
	m_pCurUser = new CField;
	std::string strMd5;
	_CANNP_NAME::encrypt::EncryptMD5(pInfo->strName, strlen(pInfo->strName), strMd5);
	std::ifstream rFile(GetResourceFileName(strMd5.c_str()), std::ios::binary | std::ios::in);
	if (rFile)
	{
		m_pCurUser->LoadBuffer(rFile, strMd5, m_strBasePwd);
	}
	else
	{
		m_pCurUser->iId = m_pCurAccount->iId;
		m_pCurUser->iLastLogoinTime = time(NULL);
		m_pCurUser->iVaildLoginTime = 0;
		m_pCurUser->iShowItemTime = 5;
		m_pCurUser->iShowLevel = SHOW_ITEM_LV_WEB | SHOW_ITEM_LV_SECRET;
		m_pCurUser->iHideParts = (1 << FieldColumn_PwdLogin) | (1 << FieldColumn_PwdPay) | (1 << FieldColumn_PwdOther);

		m_pCurUser->WriteBuffer(strMd5, m_strBasePwd);
	}

	return true;
}

uint8 UserFieldManage::UserLogoin(const char* szName, const char* szPwd)
{
	if (m_ConfigInfo.vecUse.empty())
		return 1;

	std::string strMd5;
	_CANNP_NAME::encrypt::EncryptMD5(szPwd, strlen(szPwd), strMd5);

	VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin();
	for (; itor != m_ConfigInfo.vecUse.end(); ++itor)
	{
		if (strcmp(itor->strName, szName) == 0)
		{
			if (strcmp(itor->strPwd, strMd5.c_str()) == 0)
			{
				UserLogoinSuccess(&(*itor));
				return 0;
			}
			else
				return 2;
		}
	}

	return 1;
}

void UserFieldManage::WriteInfo(const std::string& strName, const std::string& strSrc, const std::string& strPwd/*=""*/)
{
	std::ofstream wFile(GetResourceFileName(strName.c_str()).c_str(), std::ios::binary | std::ios::out | std::ios::trunc);

	std::string strValue;
	char szPwd[MAX_LEN_PWD + 1] = "";
	CGobalConfig::Share()->CreateRandStr(MAX_LEN_PWD, szPwd);
	_CANNP_NAME::encrypt::EncryptAES(szPwd, szPwd, strValue);
	wFile.write(szPwd, MAX_LEN_PWD);
	wFile.write(strValue.c_str(), MAX_LEN_AES);

	std::string strEn, strEnPwd(strPwd);
	if (strEnPwd.empty())
		strEnPwd.append(szPwd, MAX_LEN_PWD);
	_CANNP_NAME::encrypt::EncryptBuffer(strSrc.c_str(), strSrc.length(), strEnPwd.c_str(), strEn);
	uint32 iLen(strSrc.length());
	wFile.write((char*)&iLen, sizeof(iLen));
	iLen = strEn.length();
	wFile.write((char*)&iLen, sizeof(iLen));
	wFile.write(strEn.c_str(), strEn.length());

	wFile.close();
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
		}
	}

	WriteInfo(CONFIG_FILE, strBuff);
}

bool UserFieldManage::ReadInfo(const std::string& strName, std::string& strOut, const std::string& strPwd /*= ""*/)
{
	std::ifstream rFile(GetResourceFileName(strName.c_str()).c_str(), std::ios::binary | std::ios::in);
	if (!rFile)
		return false;
	
	strOut.clear();

	char szPwd[DEFINE_LEN_PWD] = "", szResult[DEFINE_LEN_AES] = "";
	rFile.read(szPwd, MAX_LEN_PWD);
	rFile.read(szResult, MAX_LEN_AES);

	std::string strDes;
	_CANNP_NAME::encrypt::EncryptAES(szPwd, szPwd, strDes);
	bool isSuccess(false);
	if (strDes.compare(szResult) == 0) //Verification
	{
		m_strBasePwd.append(szPwd, MAX_LEN_PWD);
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

			std::string strEnPwd(strPwd);
			if (strEnPwd.empty())
				strEnPwd.append(szPwd, MAX_LEN_PWD);

			_CANNP_NAME::encrypt::DecryptBuffer(pBuffer, iEncLen, strEnPwd.c_str(), strOut);
			delete pBuffer;
			pBuffer = NULL;

			isSuccess = true;
		}
	}

	if (!isSuccess)
	{
		//
		SaveCopyOfError(rFile, strName);
	}
	return isSuccess;
}


bool UserFieldManage::LoadConfigField(const std::string& strName)
{
	std::string strDes;
	if (ReadInfo(strName,strDes))
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
			memset(&mInfo, 0, sizeof(mInfo));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.iId, sizeof(mInfo.iId));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_PWD);
			m_ConfigInfo.vecUse.push_back(mInfo);
		}
		
		for (uint32 i = 0; i < iAcount; ++i)
		{
			memset(&mInfo, 0, sizeof(mInfo));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.iId, sizeof(mInfo.iId));
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strName, MAX_LEN_NAME);
			UserFieldManage::ParsingStringCopy(strDes, iOffset, &mInfo.strPwd, MAX_LEN_PWD);
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

uint32 UserFieldManage::CreateAccount(const char* szAccount, uint32 iLenA, const char*szPwd, uint32 iLenP)
{
	if (m_ConfigInfo.vecUse.size() > 0)
	{
		VEC_ACCOUNTS::iterator itor = m_ConfigInfo.vecUse.begin() ;
		for (; itor != m_ConfigInfo.vecUse.end(); ++itor)
		{
			if (strcmp(itor->strName, szAccount) == 0)
				return 0;
		}
	}
	
	Account_Info mAccountInfo;
	
	++m_ConfigInfo.iCurID;
	mAccountInfo.iId = m_ConfigInfo.iCurID;
	memcpy_s(mAccountInfo.strName, MAX_LEN_NAME, szAccount, iLenA);
	std::string strMd5;
	_CANNP_NAME::encrypt::EncryptMD5(szPwd, iLenP, strMd5);
	memcpy_s(mAccountInfo.strPwd, MAX_LEN_PWD, strMd5.c_str(), strMd5.length());
	m_ConfigInfo.vecUse.push_back(mAccountInfo);

	SaveConfigField();
	return mAccountInfo.iId;
}



