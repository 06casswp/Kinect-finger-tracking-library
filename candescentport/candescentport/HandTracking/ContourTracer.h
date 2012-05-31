#ifndef CONTOURTRACER_H
#define CONTOURTRACER_H

#include "..\point.h"
#include "DepthMap.h"
#include <vector>
#include "Contour.h"

class pointRotation
{
public:
	pointman pntfnc;
	point* points[8];
	point p1;
	point p2;
	point p3;
	point p4;
	point p5;
	point p6;
	point p7;
	point p8;
	
	void set();
	
};

class ContourTracer
{
public:
	depthmapdat* contourMap;

	Contour* cont;

	pointRotation pntrot;
	pointman pntfnc;

	int maximumRetraceSteps;



	int GetStartIndex(float diffX, float diffY);


	void GetContourpoints(depthmapdat* contourMap1,Contour* contour);

	int Width();

	int Height();

	int ResultCount(); 

	point* FindFirstpoint();

	bool IsContourpoint(int x, int y);

	bool IsAllowed(int x, int y);

	bool IsSetAndAllowed(int x, int y);

	point* GetNextpoint(point* currentPoint, point* directionPoint);

	void Process();
};



#endif 