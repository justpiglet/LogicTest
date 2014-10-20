#include<stdio.h>
#include<stdlib.h> 
#include <iostream>
#include <math.h>
#include <algorithm>
#include "publicpro.h"
using namespace std;
const double E = 1e-10;//¾«¶È


uint8 dblcmp(double d);
double cross(const Point &A, const Point &B, const Point &C);
int xycmp(double p, double mini, double maxi);
int betweencmp(const Point &a, const Point &b, const Point &c);
int segcrossEX(const Point &a, const Point &b, const Point &c, const Point &d, Point &p);
int segcross(const Point &a, const Point &b, const Point &c, const Point &d, Point &p);

bool IsInLinePart(Point pi, Point pj, Point pk);
bool onsegment(Point pi, Point pj, Point pk,Point pl);
double determinant(double v1, double v2, double v3, double v4);
bool intersect3(Point aa, Point bb, Point cc, Point dd);