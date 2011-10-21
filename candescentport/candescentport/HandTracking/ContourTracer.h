#ifndef CONTOURTRACER_H
#define CONTOURTRACER_H

#include "..\Point.h"
#include "BinaryMap.h"
#include <vector>

class ContourTracer
{
public:
	BinaryMap* contourMap;
	int maximumRetraceSteps;

	std::vector<Point*>* contourPoints;

	ContourTracer(int maximumRetraceSteps1);

	std::vector<Point*>* GetContourPoints(BinaryMap* contourMap1);

	int Width();

	int Height();

	int ResultCount(); 

	Point* FindFirstPoint();

	bool IsContourPoint(int x, int y);

	bool IsAllowed(int x, int y);

	bool IsSetAndAllowed(int x, int y);

	Point* GetNextPoint(Point* p);

	void Process();
};

class PointRotation
{
public:
	std::vector<Point*>* points;

	PointRotation();
};

#endif 