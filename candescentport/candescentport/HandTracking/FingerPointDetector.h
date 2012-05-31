#ifndef FINGERpointDET_H
#define FINGERpointDET_H

#include "..\point.h"
#include "Fingerpoint.h"
#include "HandDataSourceSettings.h"
#include "ConvexHull.h"
#include <vector>
#include "Contour.h"
#include "LineThinner.h"

class FingerpointDetector
{
public:

	HandDataSourceSettings* settings;

	
	Contour* cont;
	LineThinner LT;

	Fingerpoint* fingerpntpnt[100];
	Fingerpoint fingerpnt[100]; //size?
	int fingercnt;

	Fingerpoint** FindFingerpoints(Contour* contour, ConvexHull* convexHull, int* outcount);
	int check(point* pnt1, point* pnt2);
	point** VerifypointsByContour(ConvexHull* conv);

	bool VerifyIsFingerpointByContour(point* candidatepoint);

	int FindIndexOfClosestpointOnContour(point* fingerpoint);

	point* FindpointInDistanceForward(point* candidatepoint, int startIndex);

	point* FindpointInDistanceBackward(point* candidatepoint, int startIndex);

	point* FindpointInDistance(point* candidatepoint, int startIndex, int direction); //change it

	FingerpointDetector();

};

#endif 