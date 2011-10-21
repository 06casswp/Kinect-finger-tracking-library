#include "FingerPointDetector.h"
#include "LineThinner.h"
#include "../pointfnc.h"
#include <limits>

FingerPointDetector::FingerPointDetector(HandDataSourceSettings* settings1){

	settings=settings1;
}

std::vector<FingerPoint*>* FingerPointDetector::FindFingerPoints(Contour* contour, ConvexHull* convexHull){
	contourPoints = contour->points;
	LineThinner *LT = new LineThinner(settings->MinimumDistanceBetweenFingerPoints,true);
	std::vector<Point*>* thinnedHullPoints = LT->Filter(convexHull->Points);
	std::vector<Point*>* verifiedHullPoints = VerifyPointsByContour(thinnedHullPoints);
	//iterate through and create FingerPoints from Points, return this
	std::vector<FingerPoint*>* fingerpoints = new std::vector<FingerPoint*>;
	std::vector<Point*>::iterator iter;
	Point* p;
	for (iter = verifiedHullPoints->begin();iter<verifiedHullPoints->end();iter++) {
		p = (Point*)*iter;
		fingerpoints->push_back(new FingerPoint(p));

	}
	return fingerpoints;
}

std::vector<Point*>* FingerPointDetector::VerifyPointsByContour(std::vector<Point*>* candidatePoints){
	std::vector<Point*>* out = new std::vector<Point*>;
	std::vector<Point*>::iterator iter;
	Point* p;
	
	for (iter=candidatePoints->begin();iter<candidatePoints->end();iter++) {
		p = (Point*)*iter;
		if (VerifyIsFingerPointByContour(p)){
			out->push_back(p);
		}
	}

	return out;

}

bool FingerPointDetector::VerifyIsFingerPointByContour(Point* candidatePoint){
	int index = FindIndexOfClosestPointOnContour(candidatePoint);

	Point* pointOnContour = contourPoints->at(index);
	Point* point1 = FindPointInDistanceForward(pointOnContour, index);
	Point* point2 = FindPointInDistanceBackward(pointOnContour, index);
	pointfunctions pntfnc;
	double distance = pntfnc.distance(point1, point2);
	if (distance > settings->MaximumDistanceBetweenIntersectionPoints) 
	{
		return false;
	}

	Point *center = &pntfnc.Center(point1, point2);
	return pntfnc.distance(center, pointOnContour) >= settings->MinimumDistanceFingerPointToIntersectionLine;


}

int FingerPointDetector::FindIndexOfClosestPointOnContour(Point* fingerPoint){
	int index = 0;
	int resultIndex = -1;
	double minDist = std::numeric_limits<double>::max();
	std::vector<Point*>::iterator iter;
	Point *p;
	pointfunctions pntfnc;
	double distance;
	for (iter=contourPoints->begin();iter<contourPoints->end();iter++) {
		p = (Point*)*iter;
		distance = pntfnc.distance(p->x, p->y, fingerPoint->x, fingerPoint->y);
		if (distance < minDist)
		{
			resultIndex = index;
			minDist = distance;
		}
		index++;
	}
	return resultIndex;

}

Point* FingerPointDetector::FindPointInDistanceForward(Point* candidatePoint, int startIndex){
	return FindPointInDistance(candidatePoint, startIndex, 1);

}

Point* FingerPointDetector::FindPointInDistanceBackward(Point* candidatePoint, int startIndex){
	return FindPointInDistance(candidatePoint, startIndex, 0);

}

Point* FingerPointDetector::FindPointInDistance(Point* candidatePoint, int startIndex, int dir){
	int resultIndex = startIndex;
	pointfunctions pntfnc;
	do
	{
		if (dir) {
		resultIndex = resultIndex++;
		}
		else
		{
		resultIndex = resultIndex--;
		}
		std::vector<Point*>::iterator iter;
		int Count = 0;
		for (iter=contourPoints->begin();iter<contourPoints->end();iter++) {
			Count++;
		}
		if (resultIndex < 0)
		{
			resultIndex = Count - 1;
		}
		if (resultIndex >= Count)
		{
			resultIndex = 0;
		}
	}
	while (pntfnc.distance(candidatePoint, contourPoints->at(resultIndex)) < settings->MinimumDistanceIntersectionPoints && resultIndex != startIndex);

	return contourPoints->at(resultIndex);


}