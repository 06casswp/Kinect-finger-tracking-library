#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "..\Point.h"
#include <vector>
class ConvexHull
{
public:
	ConvexHull(std::vector<Point*>* points);

	std::vector<Point*>* Points;

	int Count();
};

#endif 