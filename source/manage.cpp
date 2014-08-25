#include "manage.h"
#include"json/reader.h"
CaAttributeManage* CaAttributeManage::m_gpManage=NULL;

CaAttributeManage::CaAttributeManage() :m_pAttributeArr(nullptr), m_attCount(0)
{
	
}

void CaAttributeManage::WriteExample()
{
	/*
	Json::Value value;
	if (!_CANNP_NAME::ReadFileJsonCpp("../resource/attribute.json", value))return;

	Json::Value objects = value["ojects"];
	bool aa=objects.isArray();
	m_attCount = objects.size();

	m_pAttributeArr = new  CaAttribute[m_attCount];

	int iTemp(0), iArrCount(0);
	for (int i = 0,k=0; i < m_attCount; ++i)
	{
		m_pAttributeArr[i].name = objects[i]["name"].asString();
		m_pAttributeArr[i].id = objects[i]["id"].asInt();
		m_pAttributeArr[i].type = objects[i]["typed"].asInt();
		iTemp = objects[i]["level"].asInt();
		m_pAttributeArr[i].level = min(max(0, iTemp), MAX_OBJECT_LEVEL);
		iTemp = objects[i]["body"].asInt();
		m_pAttributeArr[i].body = min(max(0, iTemp), MAX_OBJECT_BODY);

		const Json::Value& timesArr = objects[i]["times"];
		switch (m_pAttributeArr[i].type)
		{
		case TIMES_TYPE_UNIQUE:
			iTemp = 0;
			m_pAttributeArr[i].count = 1;
			m_pAttributeArr[i].timesArr[iTemp] = timesArr[iTemp].asInt();
			break;
		case TIMES_TYPE_MULTI:
		{
			const Json::Value& rateArr = objects[i]["rate"];
			m_pAttributeArr[i].count = min(timesArr.size() / 2, rateArr.size());
			for (k = 0; k < m_pAttributeArr[i].count; ++k)
			{
				iTemp = k << 1;
				m_pAttributeArr[i].timesArr[iTemp] = timesArr[iTemp].asInt();
				m_pAttributeArr[i].timesArr[iTemp + 1] = timesArr[iTemp + 1].asInt();
				m_pAttributeArr[i].rateArr[k] = rateArr[k].asInt();
			}
			break;
		}
		default:
			break;
		}
	}
	_CANNP_NAME::WriteFile("../resource/cccc.json",value.toStyledString().c_str());*/

	TCHAR strExample[] = _T("{\n   \"describe\" : {")
		_T("\n      \"id\" : \"0-255 unique \",")
		_T("\n      \"level\" : \"0 low ,1 mid ,2 hight,3 super,level more big and times value more big\",")
		_T("\n      \"body\" : \"0 small, move no limit. 1 mid, move light curve. 2 big, move lamost straight line\",")
		_T("\n      \"typed\":\"0 single times, 1 multi times\",")
		_T("\n      \"times\":\"objects times\",")
		_T("\n      \"rate\":\"if typed is mutli times then get a times base on rates\"")
		_T("\n      },")
		_T("\n  \"ojects\": [")
		_T("\n      {")
		_T("\n         \"name\": \"·¢ÉúµÄÁé»ê\", ")
		_T("\n         \"id\": 0, ")
		_T("\n         \"level\":0, ")
		_T("\n         \"body\":0, ")
		_T("\n         \"typed\": 0, ")
		_T("\n         \"times\": [2]")
		_T("\n      },")
		_T("\n      {")
		_T("\n         \"name\": \"object name 1\", ")
		_T("\n         \"id\": 1, ")
		_T("\n         \"level\":1, ")
		_T("\n         \"body\":1, ")
		_T("\n         \"typed\": 1, ")
		_T("\n         \"times\": [10,20,30,40,50,50,60,100],")
		_T("\n         \"rate\": [10,20,10,50]")
		_T("\n      }")
		_T("\n  ]\n}";)
	_CANNP_NAME::files::WriteFile("../resource/example.json", strExample);
}

CaAttributeManage::~CaAttributeManage()
{
	m_gpManage = nullptr;
	m_attCount = 0;
}

CaAttributeManage* CaAttributeManage::share()
{
	if (!m_gpManage)
		m_gpManage = new CaAttributeManage();

	return m_gpManage;
}

void CaAttributeManage::DestroyManage()
{

	if (m_gpManage)
		delete m_gpManage;
}

bool CaAttributeManage::LoadAttributeJason( char* filePath )
{
	if (!filePath)
		return false;

	rapidjson::Document document;
	if (!_CANNP_NAME::files::ReadFileRapidJson(filePath, document))
	{
		WriteExample();
		return false;
	}
		

	const rapidjson::Value& objects = document["ojects"];
	m_attCount = objects.Size();
	if (m_attCount < 1)
		return false;
	

	m_pAttributeArr = new  CaAttribute[m_attCount];

	int iTemp(0),iArrCount(0);
	for (int i = 0, k = 0; i < m_attCount; ++i)
	{
		m_pAttributeArr[i].name = objects[i]["name"].GetString();
		m_pAttributeArr[i].id = objects[i]["id"].GetInt();
		m_pAttributeArr[i].type = objects[i]["typed"].GetInt();
		//iTemp = objects[i]["level"].GetInt();
		//m_pAttributeArr[i].level = min(max(0,iTemp), MAX_OBJECT_LEVEL); 
		iTemp = objects[i]["body"].GetInt();
		m_pAttributeArr[i].body = min(max(0, iTemp), MAX_OBJECT_BODY);

		const rapidjson::Value& timesArr = objects[i]["times"];
		switch (m_pAttributeArr[i].type)
		{
		case TIMES_TYPE_UNIQUE:
			iTemp = 0;
			m_pAttributeArr[i].count = 1;
			m_pAttributeArr[i].timesArr[iTemp] = ConfigManage::share()->CheckTimes( timesArr[iTemp].GetInt());
			break;
		case TIMES_TYPE_MULTI:
			{
				const rapidjson::Value& rateArr = objects[i]["rate"];
				m_pAttributeArr[i].count = min(timesArr.Size() / 2, rateArr.Size());
				for (k = 0; k < m_pAttributeArr[i].count; ++k)
				{
					iTemp = k << 1;
					m_pAttributeArr[i].timesArr[iTemp] = ConfigManage::share()->CheckTimes(timesArr[iTemp].GetInt());
					m_pAttributeArr[i].timesArr[iTemp + 1] = ConfigManage::share()->CheckTimes(timesArr[iTemp + 1].GetInt());
					m_pAttributeArr[i].rateArr[k] = rateArr[k].GetInt();
				}
				break;
			}
		default:
			break;
		}
	}

	//_CANNP_NAME::files::WriteFileRapidJson("../resource/xxx.json", document);
	return true;
}

uint16 CaAttributeManage::GetObjectTimes(uint8 id)
{
	uint16 objectTimes(0);
	if (m_attCount <= id)
		return objectTimes;

	CaAttribute* attribute = &m_pAttributeArr[id];
	if (attribute->id==id && attribute->count>0)
	{
		if (attribute->type == TIMES_TYPE_UNIQUE)
			objectTimes = attribute->timesArr[0];
		else if (attribute->type == TIMES_TYPE_MULTI)
		{
			int index = (_CANNP_NAME::randoom::GetIndex(attribute->rateArr, attribute->count) << 1);
			objectTimes = _CANNP_NAME::randoom::GetRandoom(attribute->timesArr[index], attribute->timesArr[index + 1]);
		}
	}
	
	return objectTimes;
}

const CaAttribute* CaAttributeManage::GetObjectAttribute(uint8 id)
{
	if (m_attCount > id)
		return &m_pAttributeArr[id];
	else
		return nullptr;
}

void CaAttributeManage::update(DECIMALS ft)
{
	
}

//////////////////////////////////////////////////////////////////////////CaAttributeManage end

//////////////////////////////////////////////////////////////////////////begin
ConfigManage* ConfigManage::m_pConfig=nullptr;

ConfigManage:: ConfigManage():m_maxTimes(1)
{
}

ConfigManage* ConfigManage::share()
{
	if (!m_pConfig)
		m_pConfig = new ConfigManage;

	return m_pConfig;
}

bool ConfigManage::LoadData( const char* filepath )
{
	if(!filepath)
		return false;

	rapidjson::Document document;
	if (!_CANNP_NAME::files::ReadFileRapidJson(filepath, document))
		return false;


	const rapidjson::Value& objects = document["config"];
	const rapidjson::Value& lvArr = objects["lv"];
	uint8 count = _CANNP_NAME::_min((uint8)MAX_LV_COUNT,(uint8)lvArr.Size());
	for (uint8 i=0;i<count;++i)
		m_lvArr[i]=objects["lv"][i].GetInt();

	m_maxTimes = objects["maxTimes"].GetInt();

	return true;
}

OLEVEL ConfigManage::CalculateObjectLv( uint16 timesVal )
{
	OLEVEL mlv=OLEVEL_FREE;
	if (timesVal>m_maxTimes || timesVal>m_lvArr[MAX_LV_COUNT-1])
		mlv=OLEVEL_SURPRISE;	
	else
	{
		for(uint8 i=0;i<MAX_LV_COUNT;++i)
		{
			if (timesVal<=m_lvArr[i])
			{
				mlv =(OLEVEL)i;
				break;
			}
		}
	}

	return mlv;
}

ConfigManage::~ ConfigManage()
{
}

//////////////////////////////////////////////////////////////////////////end






