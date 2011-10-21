#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include "..\Point.h"
#include "ConvexHull.h"
#include <vector>

class GrahamScan
{
public:

	std::vector<Point*>* points;

	GrahamScan(std::vector<Point*>* points);

	ConvexHull* FindHull();

	Point* FindMinimalOrdinatePoint();

	Point* ReturnMinPoint(Point* p1, Point* p2);

	std::vector<Point*>* SortPointsByAngle();
}; 

#endif 