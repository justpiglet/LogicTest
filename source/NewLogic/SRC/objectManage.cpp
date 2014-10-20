#include "objectManage.h"

ObjectManage* ObjectManage::m_gObjectManage = nullptr;
ObjectManage::ObjectManage()
{

}

ObjectManage::~ObjectManage()
{
	
}

ObjectManage* ObjectManage::share()
{
	if (!m_gObjectManage)
		m_gObjectManage = new ObjectManage;
	
	return m_gObjectManage;
}

void ObjectManage::Destroy()
{
	if (m_gObjectManage)
	{
		delete m_gObjectManage;
		m_gObjectManage = nullptr;
	}
		
}

CaObject* ObjectManage::CreateObject(const uint8& id)
{
	CaObject* newObject = nullptr;
	if (!m_freeBuffer.empty())
	{
		newObject = m_freeBuffer.front();
		m_freeBuffer.pop();
		newObject->ResetDataById(id);
	}
	else
	{
		newObject = new CaObject(id);
	}
	m_actBuffer.push_back(newObject);
	return newObject;
}

void ObjectManage::DestroyObject(const CaObject* object)
{
	if (!object&&!object->IsObjectActivity())
		return;

	objectList::iterator itor=m_actBuffer.begin();
	for (; itor != m_actBuffer.end(); ++itor)
	{
		if (*itor == object)
		{
			m_actBuffer.erase(itor);
			m_freeBuffer.push(*itor);
			break;
		}
	}
}






