#ifndef HANDAT_H
#define HANDAT_H

#include "..\point.h"
#include "Fingerpoint.h"
#include "ConvexHull.h"
#include "../clusters.h"
#include "Palm.h"
#include "Contour.h"

#include <vector>

class HandData
{
public:

	int id;
	ConvexHull* convexHull;


	clusterdat* clusterdata;
	Palm* palm;
	Contour* contour;

	HandData(int id1, clusterdat* clusterdat1, ConvexHull* convexHull1, Contour *contour1, Palm *palm1, Fingerpoint** fingerpoints1);
	//void set(int id1, clusterdat* clusterdat1, ConvexHull* convexHull1, Contour *contour1, Palm *palm1, Fingerpoint** fingerpoints1);

	point* Center();

	point* Location();

	bool HasPalm();

	point* Palmpoint();

	double PalmDistance();

	Fingerpoint** Fingerpoints;


	int FingerpointCount;

	bool HasContour();


};

#endif 