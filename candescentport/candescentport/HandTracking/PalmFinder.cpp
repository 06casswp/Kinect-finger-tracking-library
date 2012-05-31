#include "PalmFinder.h"


#include <limits>
#include <math.h>



Palm* PalmFinder::FindCenter(Contour* contour, point** candidates,int count)        {
	result = 0;
	LT.checkBoundary = false;
	LT.mindDistBetweenpoints = contourReduction;
	
	int count1;

	LT.Filter(contour);
	FindCenterFromCandidates(contour, candidates,count); 

	if (!result==0){
		IncreaseAccuracy(result->location, contour);
	}
	return result;
}

void PalmFinder::FindCenterFromCandidates(Contour* cont, point** candidates,int count)       {
	int Count = 0;
	
	

	double *distances = (double*)malloc(sizeof(double)*count);
	Count = 0;
	point* p;
	point* maxind = 0;
	int i = 0;
	for (i=0;i<count; i++) 
	{
		distances[i] = FindMaxDistance(cont, candidates[i]);
	}
	double maxDistance = result == NULL ? 0 : result->distanceToContour;
	int maxIndex = -1;//wat is this for
	for (i=0;i<count; i++)
	{
		if (distances[i] > maxDistance)
		{
			maxDistance = distances[Count];
			maxind = candidates[i];
		}
	}
	if (!maxind)
	{
		result = new Palm(maxind, maxDistance);
	}

}

void PalmFinder::IncreaseAccuracy(point* center, Contour* cont) {
	newcandidatecnt =0;
	for (int x = -searchRadius; x <= searchRadius; x++)
	{
		for (int y = -searchRadius; y <= searchRadius; y++)
		{
			if(x != 0 && y != 0)
			{
				
				pntfnc.set(center->x + x, center->y + y, center->z, &newcandidate[newcandidatecnt]);
				newcandidatepnt[newcandidatecnt] = &newcandidate[newcandidatecnt];
				newcandidatecnt++;
			}
		}
	}
	FindCenterFromCandidates(cont, newCandidatepointspnt, newcandidatecnt);
}

double PalmFinder::FindMaxDistance(Contour* cont, point *candidate)        {
	double result = std::numeric_limits<double>::max();
	pointman pntfnc;
	int i = 0;
	for (i=0;i<cont->newpointcnt;i++) {
		
		result = std::min(pntfnc.distance(cont->newpoints[i].x,cont->newpoints[i].y, candidate->x, candidate->y), result);
	}
	return result;
}