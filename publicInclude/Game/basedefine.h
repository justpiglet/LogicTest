#ifndef _FHKJEF_FDS_CAN_BASEDEFINE
#define _FHKJEF_FDS_CAN_BASEDEFINE

#include<string>
#include<vector>
#include <list>
#include "../Base/macro.h"

typedef struct Point
{
	DECIMALS x, y;
	Point(DECIMALS x = 0.0f, DECIMALS y = 0.0f) :x(x), y(y){}


	Point& operator + (Point& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;

		return *this;
	}

	Point& operator / (DECIMALS div)
	{
		this->x = this->x / div;
		this->y = this->y / div;

		return *this;
	}

}*PPoint;

typedef struct Line 
{
	Point mstart;
	Point mend;
	Line(const Point& _start = Point(0.0, 0.0), const Point& _end = Point(0.0, 0.0)) :mstart(_start), mend(_end){}
}*PLine;

typedef struct Polygon
{
	std::list<Point> mpointArr;
}*PPolygon;

typedef struct  Circle
{
	Point mcenter;
	DECIMALS mr;
	Circle(const Point& _center = Point(0.0, 0.0), DECIMALS _r = 0.0) :mcenter(_center), mr(_r){}
}*PCircle;

#endif