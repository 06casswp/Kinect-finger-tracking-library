#ifndef LINETHIN_H
#define LINETHIN_H

#include "..\Point.h"
#include <vector>
class LineThinner
{
public:
	bool checkBoundary;
	float mindDistBetweenPoints;

	LineThinner(float mindDistBetweenPointsz, bool checkBoundaryz);

	std::vector<Point*>* Filter(std::vector<Point*>* points);

	bool MergeIfDistanceIsTooSmall(Point* sourcePoint, Point* destPoint);

	void CheckFirstAndLastPoint(std::vector<Point*>* points);
};

#endif 