#ifndef HANDATFAC_H
#define HANDATFAC_H

#include "HandDataSourceSettings.h"
#include "ContourFactory.h"
#include "PalmFinder.h"
#include "FingerPointDetector.h"
#include "IdGenerator.h"
#include "HandData.h"
#include "../clusters.h"
#include "FingerPoint.h"
#include "BinaryMap.h"
#include "ConvexHull.h"
#include <vector>




class HandDataFactory
{
public:

	HandDataSourceSettings* settings;
	ContourFactory* contourFactory;
	PalmFinder* palmFinder;
	FingerPointDetector* fingerPointDetector;
	IdGenerator* idGenerator;

	HandDataFactory(HandDataSourceSettings *settings1);

	void ReturnId(int id);

	HandData* Create(Cluster* cluster);

	HandData* Create(HandData* lastFrameData, Cluster* cluster);

	void ClearIds();

	HandData* Create(int id, Cluster* cluster, std::vector<FingerPoint*>* lastFrameFingerPoints);

	std::vector<FingerPoint*>* MapFingerPoints(std::vector<FingerPoint*>* oldFingerPoints, std::vector<FingerPoint*>* newFingerPoints);

	Contour* CreateContour(BinaryMap* map, Cluster* cluster);

	std::vector<FingerPoint*>* DetectFingerPoints(ConvexHull* convexHull, Cluster* cluster, Contour* contour);

	BinaryMap* CreateMap(Cluster* cluster);
};

#endif 