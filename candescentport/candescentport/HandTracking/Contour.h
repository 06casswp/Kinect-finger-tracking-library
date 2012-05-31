#ifndef CONTOUR_H
#define CONTOUR_H

#include "..\Point.h"
#include <vector>

class Contour
{
public:
	
	point newpoints[640*480];
	int newpointcnt;

	point* contourpoints[640*480];
	int contourpntcnt;



};

#endif 