#ifndef CONTOUR_H
#define CONTOUR_H

#include "..\Point.h"
#include <vector>

class Contour
{
public:
	//IList<Point> points; //points list
	std::vector<Point*>* points;

	Contour();

	Contour(std::vector<Point*>* points1);


	int Count();

	Contour* Empty(); //returns an empty contour, do it the other way
};

#endif 