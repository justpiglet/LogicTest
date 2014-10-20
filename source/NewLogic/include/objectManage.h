#ifndef _FHKJEF_FDS_CAN_OBJECTMANAGE
#define _FHKJEF_FDS_CAN_OBJECTMANAGE

#include"game/publicpro.h"
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
	virtual CaObject* CreateObject(const uint8&);
	virtual void DestroyObject(const CaObject*);
private:
	static ObjectManage* m_gObjectManage;
	
	objectQueue m_freeBuffer;
	objectList  m_actBuffer;
};


#endif