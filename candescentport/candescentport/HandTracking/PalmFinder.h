#ifndef PALMFIND_H
#define PALMFIND_H

#include "Palm.h"
#include "HandDataSourceSettings.h"
#include "..\point.h"
#include "Contour.h"
#include <vector>
#include "LineThinner.h"
class PalmFinder
{
public:
	Palm* result;

	float contourReduction;
	int searchRadius;

	LineThinner LT;
	pointman pntfnc;
	Palm* FindCenter(Contour* contour, point** candidates,int count);

	void FindCenterFromCandidates(Contour* cont, point** candidates,int count);

	void IncreaseAccuracy(point* center, Contour* cont);

	double FindMaxDistance(Contour* cont, point* candidate);

	point** newCandidatepointspnt;
	point* newcandidatepnt[640*480];
	point newcandidate[640*480];
	int newcandidatecnt;

};

#endif 