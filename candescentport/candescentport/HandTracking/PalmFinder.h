#ifndef PALMFIND_H
#define PALMFIND_H

#include "Palm.h"
#include "HandDataSourceSettings.h"
#include "..\Point.h"
#include "Contour.h"
#include <vector>
class PalmFinder
{
public:
	Palm* result;

	float contourReduction;
	int searchRadius;

	PalmFinder(HandDataSourceSettings* settings);

	Palm* FindCenter(Contour *contour, std::vector<Point*>* candidates);

	void FindCenterFromCandidates(std::vector<Point*>* contour, std::vector<Point*>* candidates);

	void IncreaseAccuracy(Point* center, std::vector<Point*>* contour);

	double FindMaxDistance(std::vector<Point*>* contourPoints, Point* candidate);
};

#endif 