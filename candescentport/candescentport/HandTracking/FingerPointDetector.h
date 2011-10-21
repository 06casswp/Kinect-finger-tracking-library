#ifndef FINGERPOINTDET_H
#define FINGERPOINTDET_H

#include "..\Point.h"
#include "FingerPoint.h"
#include "HandDataSourceSettings.h"
#include "ConvexHull.h"
#include <vector>
#include "Contour.h"

class FingerPointDetector
{
public:

	HandDataSourceSettings* settings;
	std::vector<Point*>* contourPoints;

	FingerPointDetector(HandDataSourceSettings* settings);

	std::vector<FingerPoint*>* FindFingerPoints(Contour* contour, ConvexHull* convexHull);

	std::vector<Point*>* VerifyPointsByContour(std::vector<Point*>* candidatePoints);

	bool VerifyIsFingerPointByContour(Point* candidatePoint);

	int FindIndexOfClosestPointOnContour(Point* fingerPoint);

	Point* FindPointInDistanceForward(Point* candidatePoint, int startIndex);

	Point* FindPointInDistanceBackward(Point* candidatePoint, int startIndex);

	Point* FindPointInDistance(Point* candidatePoint, int startIndex, int direction); //change it
};

#endif 