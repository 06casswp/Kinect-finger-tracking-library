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

	double cartesian_angle(int x, int y);

	int orientation(Point* p1, Point* p2, Point* p3);
	int orientation(int x1, int y1, int x2,int y2,int px, int py);
	bool is_equal(double v1,double v2);
}; 

#endif 