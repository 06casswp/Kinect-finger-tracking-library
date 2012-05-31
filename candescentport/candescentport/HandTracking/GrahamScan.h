#ifndef GRAHAMSCAN_H
#define GRAHAMSCAN_H

#include "..\point.h"
#include "ConvexHull.h"
#include <vector>
#include "PointAngleComparer.h"

class GrahamScan
{
public:

	point** points;
	int pointscnt;

	pointAngleComparer2D comparer;
	pointAngleComparer2Da comparer1;

	void set(point** points, int count);

	ConvexHull* FindHull();

	point* FindMinimalOrdinatepoint();

	point* ReturnMinpoint(point* p1, point* p2);

	void SortpointsByAngle(); //sorts the points**

	double cartesian_angle(int x, int y);

	int orientation(point* p1, point* p2, point* p3);
	int orientation(int x1, int y1, int x2,int y2,int px, int py);
	bool is_equal(double v1,double v2);
}; 

#endif 