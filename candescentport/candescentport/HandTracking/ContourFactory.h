#ifndef CONTOURFACTORY_H
#define CONTOURFACTORY_H

#include "ContourScanner.h"
#include "ContourTracer.h"
#include "LineThinner.h"
#include "../Point.h"
#include "Contour.h"
#include "BinaryMap.h"
#include <vector>

class ContourFactory
{
public:
	ContourScanner* scanner;
	ContourTracer* tracer;
	LineThinner* thinner;  

	ContourFactory(float lineThinningDistance, int maximumRetraceSteps);

	Contour* CreateContour(BinaryMap* map, float left, float top);

	std::vector<Point*>* Translate(std::vector<Point*>* points, int deltaX, int deltaY);

};

#endif 