#ifndef PALM_H
#define PALM_H

#include "..\point.h"

class Palm
{
public:
	point* location;
	double distanceToContour;

	Palm(point* locationz, double distanceToContourz);
};

#endif 