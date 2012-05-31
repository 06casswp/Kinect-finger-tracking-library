#ifndef HANDATFAC_H
#define HANDATFAC_H

#include "HandDataSourceSettings.h"
#include "ContourFactory.h"
#include "PalmFinder.h"
#include "FingerpointDetector.h"
#include "IdGenerator.h"
#include "HandData.h"
#include "../clusters.h"
#include "Fingerpoint.h"
#include "DepthMap.h"
#include "ConvexHull.h"
#include <vector>
#include "GrahamScan.h"
#include "DistanceMap2.h"
#include <fstream>
#include <iostream>
#include <string>

class HandDataFactory
{
public:

	HandDataSourceSettings* settings;
	ContourFactory contourFactory;
	PalmFinder palmFinder;
	FingerpointDetector fingerpointDetector;
	IdGenerator idGenerator;
	
	GrahamScan GS;

	DistanceMap2b distanceMap;

	void setsettings();

	void ReturnId(int id);

	HandData* Create(clusterdat* clusterdat); //create new handdata

	HandData* Create(HandData* lastFrameData, clusterdat* clusterdat); //reuse and return the old 1

	void ClearIds();

	HandData* Create1(HandData* HD);//create new 1


	Fingerpoint** MapFingerpoints(Fingerpoint** oldFingerpoints, int oldcount, Fingerpoint** newFingerpoints, int newcount, int*outcount);


	Contour* CreateContour(depthmapdat* map, clusterdat* clusterdat);

	Fingerpoint** DetectFingerpoints(ConvexHull* convexHull, Contour* contour, int* outcount);


	depthmapdat* CreateMap(clusterdat* clusterdat);

	HandDataFactory();
};

#endif 