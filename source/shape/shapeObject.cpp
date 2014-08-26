#include "shapeObject.h"

//////////////////////////////////////////////////////////////////////////ShapeObject begin
ShapeObject::ShapeObject(uint8 shapeType /*= ShapeType_NULL*/) :m_shapeType(shapeType)
{
}

ShapeObject::~ShapeObject()
{
}

Circle ShapeObject::RectangleToCircle(const Point& lt, const Point& rb)const
{
	DECIMALS _d = _CANNP_NAME::_max(lt.x - rb.x, lt.y - rb.y);
	Point center((lt.x + rb.x) / 2, (lt.y + rb.y) / 2);
	
	return Circle(center, _d / 2.0f);
}

bool ShapeObject::IsCircleCollision(const Circle* pc1, const Circle* pc2) const
{
	if (pc1&&pc2)
		return _CANNP_NAME::lineIntersection::IsVaildDistance2Points(pc1->mcenter, pc2->mcenter, pc1->mr + pc2->mr);
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////ShapeObject end


////////////////////////////////////////////////////////////////////////// CircleObject begin
CircleObject::CircleObject() :ShapeObject(ShapeType_Circle)
{

}

CircleObject::~CircleObject()
{
	

}

bool CircleObject::IsCollision(const ShapeObject* pObject) const
{
	if (!pObject)
		return false;

	switch (pObject->GetShapeType())
	{
	case ShapeType_Polygon:
		return pObject->IsCollision(this);
	case ShapeType_Circle:
		return IsCircleCollision(this, dynamic_cast<const CircleObject*>(pObject));
	default:
		break;
	};
	
	return false;
}

////////////////////////////////////////////////////////////////////////// CircleObject end


//////////////////////////////////////////////////////////////////////////PolygonObject begin
PolygonObject::PolygonObject() :ShapeObject(ShapeType_Polygon)
{

}

PolygonObject::~PolygonObject()
{

}

bool PolygonObject::IsCollision(const ShapeObject* pObject) const
{
	if (!pObject)
		return false;

	switch (pObject->GetShapeType())
	{
	case ShapeType_Circle:
		return IsCollisionCircle(dynamic_cast<const CircleObject*>(pObject));
	case ShapeType_Polygon:
		return IsCollisionPolygon(dynamic_cast<const PolygonObject*>(pObject));
	default:
		break;
	}

	return false;
}

bool PolygonObject::IsCollisionCircle(const CircleObject* pObject) const
{
	
	Circle polyC=  RectangleToCircle(m_ltpos,m_rbpos);
	const Circle* pCircleData = pObject->getCircle();
	if (!IsCircleCollision(&polyC, pCircleData))
		return false;

	bool isIn(false);
	bool isIns(false);
	std::list<Point>::const_iterator itor1 = mpointArr.begin();
	std::list<Point>::const_iterator itor2 = itor1; ++itor2;
	std::list<Point>::const_iterator itor_end = mpointArr.end();
	 
	 
	 while (true)
	 {
		 isIn = _CANNP_NAME::lineIntersection::IsVaildDistance2Points(pCircleData->mcenter, *itor1, pCircleData->mr);
		 if (isIn)
			 break;

		 isIns = _CANNP_NAME::lineIntersection::isLineInterCircle(*itor1, *itor2, pCircleData->mcenter, pCircleData->mr);

		 if (isIns)
			 break;

		 if (itor2 == itor_end)
		 {
			 isIn = _CANNP_NAME::lineIntersection::IsVaildDistance2Points(pCircleData->mcenter, *itor2, pCircleData->mr);
			 if (!isIn)
				 isIns = _CANNP_NAME::lineIntersection::isLineInterCircle(*mpointArr.begin(), *itor2, pCircleData->mcenter, pCircleData->mr);
			 break;
		 }
		
		 ++itor1;
		 ++itor2;
	 }
	

	 return isIn || isIns;
}

bool PolygonObject::IsCollisionPolygon(const PolygonObject* pObject) const
{
	Circle polyC = RectangleToCircle(m_ltpos, m_rbpos);
	Circle polyC2 = RectangleToCircle(pObject->m_ltpos, pObject->m_rbpos);
	if (!IsCircleCollision(&polyC, &polyC2))
		return false;
	const Polygon* pPolygon = pObject->getPloygon();
	std::list<Point>::const_iterator itor1 = pPolygon->mpointArr.begin();
	std::list<Point>::const_iterator itor2 = itor1; ++itor2;
	std::list<Point>::const_iterator itor_end = pPolygon->mpointArr.end();
	bool isIns(false);
	while (true)
	{
		isIns = IsIntersectionLine(*itor1,*itor2);
		if (isIns)
			break;

		if (itor2 == itor_end)
		{
			isIns = IsIntersectionLine(*itor2, *pPolygon->mpointArr.begin());
			break;
		}
		++itor1;
		++itor2;
	}

	return isIns;
}

bool PolygonObject::IsIntersectionLine(const Point& a, const Point& b) const
{
	std::list<Point>::const_iterator itor1 = mpointArr.begin();
	std::list<Point>::const_iterator itor2 = itor1; ++itor2;
	std::list<Point>::const_iterator itor_end = mpointArr.end();
	bool isIns(false);
	while (true)
	{
		isIns = _CANNP_NAME::lineIntersection::IsIntersection(*itor1, *itor2, a, b);
		if (isIns)
			break;
		if (itor2 == itor_end)
		{
			isIns = _CANNP_NAME::lineIntersection::IsIntersection(*itor2, *mpointArr.begin(),a,b);
			break;
		}

		++itor1;
		++itor2;
	}
	return isIns;
}

void PolygonObject::CalculateBound()
{
	std::list<Point>::const_iterator itor1 = mpointArr.begin();
	std::list<Point>::const_iterator itor_end = mpointArr.end();
	m_ltpos = *(itor1++);
	m_rbpos = m_ltpos;
	for (; itor1 != itor_end; ++itor1)
	{
		CalculateBound(*itor1);
	}
	
}

void PolygonObject::CalculateBound(Point pos)
{
	if (m_ltpos.x > pos.x)
		m_ltpos.x = pos.x;
	else if (m_rbpos.x < pos.x)
		m_rbpos.x = pos.x;

	if (m_ltpos.y > pos.y)
		m_ltpos.y = pos.y;
	else if (m_rbpos.y < pos.y)
		m_rbpos.y = pos.y;
}

//////////////////////////////////////////////////////////////////////////PolygonObject end