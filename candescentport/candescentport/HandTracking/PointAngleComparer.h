#ifndef PNTANGCOMP_H
#define PNTANGCOMP_H

#include "..\Point.h"

class PointAngleComparer2D //removed c# comparer interface
{
public:
	Point* p0;

	PointAngleComparer2D(Point* zeroPoint);
	PointAngleComparer2D();

	int Compare(Point* p1, Point* p2);

	float Compare(Point* p0, Point* p1, Point* p2);
};

#endif 