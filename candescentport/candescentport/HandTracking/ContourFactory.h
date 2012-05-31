#ifndef CONTOURFACTORY_H
#define CONTOURFACTORY_H

#include "ContourScanner.h"
#include "ContourTracer.h"
#include "LineThinner.h"
#include "../point.h"
#include "Contour.h"
#include "DepthMap.h"
#include <vector>

class ContourFactory
{
public:

	ContourTracer tracer;
	LineThinner thinner;  


	Contour* CreateContour(depthmapdat* map, float left, float top);

	void Translate(Contour* cont, int deltaX, int deltaY);

};

#endif 