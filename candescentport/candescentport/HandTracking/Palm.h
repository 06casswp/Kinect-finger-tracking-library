#ifndef PALM_H
#define PALM_H

#include "..\Point.h"

class Palm
{
public:
	Point* location;
	double distanceToContour;

	Palm(Point* locationz, double distanceToContourz);
};

#endif 