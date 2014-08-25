#ifndef _FHKJEF_FDS_CAN_OBJECTMANAGE
#define _FHKJEF_FDS_CAN_OBJECTMANAGE

#include"publicpro.h"
#include <queue>
#include <list>
#define objectQueue  std::queue<CaObject*>
#define objectList	std::list<CaObject*>
class ObjectManage
{
public:
	static ObjectManage* share();
	static void Destroy();
private:
	ObjectManage();
	~ObjectManage();
public:
	virtual CaObject* CreateObject(uint8);
	virtual void DestroyObject(CaObject*);
private:
	static ObjectManage* m_gObjectManage;
	
	objectQueue m_freeBuffer;
	objectList  m_actBuffer;
};


#endif