#ifndef _FHKJEF_FDS_CAN_BASEDEFINE
#define _FHKJEF_FDS_CAN_BASEDEFINE

#include <stdlib.h> 
#include<Windows.h>
#include<string>
#include<vector>
#include <list>
#include "macro.h"

using std::vector;
using std::string;
struct CaAttribute;

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