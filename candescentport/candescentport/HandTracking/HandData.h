#ifndef HANDAT_H
#define HANDAT_H

#include "..\Point.h"
#include "FingerPoint.h"
#include "ConvexHull.h"
#include "../clusters.h"
#include "Palm.h"
#include "Contour.h"
#include "../ILocatable.h"
#include <vector>

class HandData : public ILocatable
{
public:

	int id;
	ConvexHull* convexHull;


	Cluster* cluster;
	Palm* palm;
	Contour* contour;

	HandData(int id1, Cluster* cluster1, ConvexHull* convexHull1, Contour *contour1, Palm *palm1, std::vector<FingerPoint*>* fingerPoints1);

	Point* Center();

	Point* Location();

	bool HasPalm();

	Point* PalmPoint();

	double PalmDistance();

	std::vector<FingerPoint*>* FingerPoints;

	int FingerPointCount();

	bool HasContour();

	bool HasFingerPoints();
};

#endif 