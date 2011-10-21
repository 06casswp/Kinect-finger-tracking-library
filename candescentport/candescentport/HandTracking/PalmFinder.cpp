#include "PalmFinder.h"
#include "LineThinner.h"
#include "../pointfnc.h"
#include <limits>
#include <math.h>


PalmFinder::PalmFinder(HandDataSourceSettings* settings)        {
	searchRadius = settings->PalmAccuracySearchRadius;
	contourReduction = settings->PalmContourReduction;
}

Palm* PalmFinder::FindCenter(Contour* contour, std::vector<Point*>* candidates)        {
	result = 0;
	LineThinner* LT =  new LineThinner(contourReduction, false);
	std::vector<Point*>* minimizedContour = LT->Filter(contour->points);
FindCenterFromCandidates(minimizedContour, candidates); 

	if (!result==0){
		IncreaseAccuracy(result->location, minimizedContour);
	}
	return result;
}

void PalmFinder::FindCenterFromCandidates(std::vector<Point*>* contour, std::vector<Point*>* candidates)        {
	int Count = 0;
	int i;
	std::vector<Point*>::iterator iter;
	for (iter=candidates->begin();iter<candidates->end(); iter++) {
		Count++;
	}
	double *distances = (double*)malloc(sizeof(double)*Count);
	Count = 0;
	Point* p;
	Point* maxind = 0;
	for (iter=candidates->begin();iter<candidates->end(); iter++) 
	{
		p = (Point*)*iter;
		distances[Count] = FindMaxDistance(contour, p);
		Count++;
	}
	Count = 0;
	double maxDistance = result == NULL ? 0 : result->distanceToContour;
	int maxIndex = -1;
	for (iter=candidates->begin();iter<candidates->end(); iter++)
	{
		p = (Point*)*iter;
		if (distances[Count] > maxDistance)
		{
			maxDistance = distances[Count];
			maxind = p;
		}
		Count++;
	}
	if (!maxind)
	{
		result = new Palm(maxind, maxDistance);
	}

}

void PalmFinder::IncreaseAccuracy(Point* center, std::vector<Point*>* contour) {
	std::vector<Point*>* newCandidatePoints = new std::vector<Point*>;

	for (int x = -searchRadius; x <= searchRadius; x++)
	{
		for (int y = -searchRadius; y <= searchRadius; y++)
		{
			if(x != 0 && y != 0)
			{
				newCandidatePoints->push_back(new Point(center->x + x, center->y + y, center->z));
			}
		}
	}
	FindCenterFromCandidates(contour, newCandidatePoints);
}

double PalmFinder::FindMaxDistance(std::vector<Point*>* contourPoints, Point *candidate)        {
	double result = std::numeric_limits<double>::max();
	std::vector<Point*>::iterator iter;
	Point* p;
	pointfunctions pntfnc;
	for (iter=contourPoints->begin();iter<contourPoints->end();iter++) {
		p = (Point*)*iter;
		result = std::min(pntfnc.distance(p->x, p->y, candidate->x, candidate->y), result);
	}
	return result;
}