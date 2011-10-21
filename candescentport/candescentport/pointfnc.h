#ifndef POINTFNC_H
#define POINTFNC_H

#include "Point.h"

class pointfunctions
{
public:
	double distance(Point *p1, Point *p2);
	double distance(float x1, float y1, float x2, float y2);
	Point Center(Point *p1, Point *p2);



};

#endif 