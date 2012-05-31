#include "FingerpointDetector.h"


#include <limits>



Fingerpoint** FingerpointDetector::FindFingerpoints(Contour* contour, ConvexHull* convexHull, int* outcount){
	cont = contour;
	LT.set(settings->MinimumDistanceBetweenFingerpoints,true);
	LT.Filter1(convexHull);
	VerifypointsByContour(convexHull);
	//iterate through and create Fingerpoints from points, return this
	int i = 0;
	int j = 0;
	fingercnt = 0;
	int close = 0;
	for (i = 0;i<convexHull->Count;i++) {
		if (convexHull->points[i]) {
			for (j=0;j<fingercnt;j++) {
				close = check(fingerpnt[j].location,convexHull->points[i]);
				if (close) {
					fingerpnt[j].location->x = (fingerpnt[j].location->x+convexHull->points[i]->x)/2;
					fingerpnt[j].location->y = (fingerpnt[j].location->y+convexHull->points[i]->y)/2;
					fingerpnt[j].location->z = (fingerpnt[j].location->z+convexHull->points[i]->z)/2;
					j++;
				}
			}
			if (!close) {
				if ((convexHull->points[i]->x>10)&&(convexHull->points[i]->x<630)&&(convexHull->points[i]->y>10)&&(convexHull->points[i]->y<470)) {
					fingerpnt[fingercnt].location = convexHull->points[i];
					fingerpntpnt[fingercnt] = &fingerpnt[fingercnt];
					fingercnt++;
				}
			}
		}
	}
	printf("DETECTED %d", fingercnt);
	*outcount = fingercnt;
	return &fingerpntpnt[0];
}

point** FingerpointDetector::VerifypointsByContour(ConvexHull* conv){
	//point** out = new std::vector<point*>;
	//point* p;
	int i = 0;
	for (i=0;i<conv->Count;i++) { //contourpnts
		
		if (VerifyIsFingerpointByContour(conv->points[i])){
			//pass it to out?
		}
		else
		{
			conv->points[i] = 0;
		}

	}

	return 0;//out;

}

bool FingerpointDetector::VerifyIsFingerpointByContour(point* candidatepoint){
	int index = FindIndexOfClosestpointOnContour(candidatepoint);

	point* pointOnContour = cont->contourpoints[index];
	point* point1 = FindpointInDistanceForward(pointOnContour, index);
	point* point2 = FindpointInDistanceBackward(pointOnContour, index);
	pointman pntfnc;
	double distance = pntfnc.distance(point1, point2);
	if (distance > settings->MaximumDistanceBetweenIntersectionpoints) 
	{
		return false;
	}

	point center;
	pntfnc.Center(point1, point2,&center);
	return pntfnc.distance(&center, pointOnContour) >= settings->MinimumDistanceFingerpointToIntersectionLine;


}

int FingerpointDetector::FindIndexOfClosestpointOnContour(point* fingerpoint){
	
	int resultIndex = -1;
	double minDist = std::numeric_limits<double>::max();
	
	
	pointman pntfnc;
	double distance;
	int i = 0;
	for (i=0;i<cont->contourpntcnt;i++) { //contourpnts
		if (cont->contourpoints[i]) {
			distance = pntfnc.distance(cont->contourpoints[i]->x, cont->contourpoints[i]->y, fingerpoint->x, fingerpoint->y);
			if (distance < minDist)
			{
				resultIndex = i;
				minDist = distance;
			}
		}
		
	}
	return resultIndex;

}

point* FingerpointDetector::FindpointInDistanceForward(point* candidatepoint, int startIndex){
	return FindpointInDistance(candidatepoint, startIndex, 1);

}

point* FingerpointDetector::FindpointInDistanceBackward(point* candidatepoint, int startIndex){
	return FindpointInDistance(candidatepoint, startIndex, 0);

}

point* FingerpointDetector::FindpointInDistance(point* candidatepoint, int startIndex, int dir){
	int resultIndex = startIndex;
	pointman pntfnc;
	bool conti;
	do
	{
		if (dir) {
		resultIndex = resultIndex++;
		}
		else
		{
		resultIndex = resultIndex--;
		}

		if (resultIndex < 0)
		{
			resultIndex = cont->contourpntcnt - 1;
		}
		if (resultIndex >= cont->contourpntcnt)
		{
			resultIndex = 0;
		}
		if (cont->contourpoints[resultIndex]) {
			conti = pntfnc.distance(candidatepoint, cont->contourpoints[resultIndex]) < settings->MinimumDistanceIntersectionpoints && resultIndex != startIndex;
		}
		else
		{
			conti = true;
		}
		}
	while (conti);
	
	return cont->contourpoints[resultIndex];


}

int FingerpointDetector::check(point* pnt1, point* pnt2) {
	pointman pntfnc;
	if (pntfnc.distance(pnt1, pnt2)<25) {
		return 1;
	}
	else
	{
		return 0;
	}

}

FingerpointDetector::FingerpointDetector() {


}