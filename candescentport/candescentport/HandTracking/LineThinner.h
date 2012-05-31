#ifndef LINETHIN_H
#define LINETHIN_H

#include "..\point.h"
#include <vector>
#include "Contour.h"
#include "ConvexHull.h"
class LineThinner
{
public:
	bool checkBoundary;
	float mindDistBetweenpoints;
	pointman pntfnc;

	point* newstore[640*480];
	int size;

	void set(float mindDistBetweenpoints1, bool check);

	void Filter(Contour* cont);
	void Filter1(ConvexHull* conv);

	bool DistanceIsTooSmall(point* sourcepoint, point* destpoint);

	void CheckFirstAndLastpoint(Contour* cont);
	void CheckFirstAndLastpoint1(ConvexHull* conv);
};

#endif 