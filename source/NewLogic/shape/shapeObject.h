#ifndef _FHKJEF_FDS_CAN_SHAPE
#define _FHKJEF_FDS_CAN_SHAPE
#include "base/basedefine.h"
#include "depend/cantools/tools.h"

enum ShapeType
{
	ShapeType_NULL=0,
	ShapeType_Circle,
	ShapeType_Polygon,

	ShapeType_MAX = ShapeType_Polygon,
};

class ShapeObject
{
public:
	ShapeObject(uint8 shapeType = ShapeType_NULL);
	~ShapeObject();
	 uint8 GetShapeType()const{ return m_shapeType; }
	 Circle RectangleToCircle(const Point& lt, const Point& rb)const;
	 bool IsCircleCollision(const Circle* pc1, const Circle* pc2) const;
public:
	virtual bool IsCollision(const ShapeObject* pObject) const = 0;
private:
	uint8 m_shapeType;
};

class CircleObject :public ShapeObject,public Circle
{
public:
	CircleObject();
	~CircleObject();

public:
	inline void setCircle(const Point& _center, DECIMALS _r){mcenter = _center; mr = _r;}
	inline const Circle* getCircle()const{ return this; }
public:
	virtual bool IsCollision(const ShapeObject* pObject) const;
};

class PolygonObject :public ShapeObject,public Polygon
{
public:
	PolygonObject();
	~PolygonObject();

public:
	inline void setPolygon(const std::list<Point>& points){ mpointArr = points; CalculateBound(); }
	inline void PushBackPoint(const Point& point){ mpointArr.push_back(point); CalculateBound(point); }
	//inline const Polygon* getPloygon()const { return this; }
public:
	virtual bool IsCollision(const ShapeObject* pObject) const;
private:
	bool IsCollisionCircle(const CircleObject* pObject)const;
	bool IsCollisionPolygon(const PolygonObject* pObject)const;
	bool IsIntersectionLine(const Point& a, const Point& b) const;

	void CalculateBound(Point pos);
	void CalculateBound();
private:
	Point m_ltpos;
	Point m_rbpos;
};


#endif