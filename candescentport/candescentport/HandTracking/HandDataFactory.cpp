#include "HandDataFactory.h"
#include "GrahamScan.h"
#include "Palm.h"
#include "DistanceMap2.h"

HandDataFactory::HandDataFactory(HandDataSourceSettings* settings1){
	settings = settings1;
	fingerPointDetector = new FingerPointDetector(settings);
	contourFactory = new ContourFactory(settings->ContourLineThinningDistance, settings->MaximumRetraceSteps);
	palmFinder = new PalmFinder(settings);
	idGenerator = new IdGenerator();

}

void HandDataFactory::ReturnId(int id){

	idGenerator->Return(id);
}

HandData* HandDataFactory::Create(Cluster* cluster){
	return Create(idGenerator->GetNextId(), cluster, new std::vector<FingerPoint*>);
}

HandData* HandDataFactory::Create(HandData* lastFrameData, Cluster* cluster)
{
	return Create(lastFrameData->id, cluster, lastFrameData->FingerPoints);
}

void HandDataFactory::ClearIds()
{
	idGenerator->Clear();
}

HandData* HandDataFactory::Create(int id, Cluster* cluster, std::vector<FingerPoint*>* lastFrameFingerPoints){
	GrahamScan* GS = new GrahamScan(&cluster->points);
	ConvexHull* convexHull = GS->FindHull();
	BinaryMap* map = CreateMap(cluster);

	Contour* contour = CreateContour(map, cluster);
	if (contour->Count() < settings->MinimalPointsInContour)
	{
		return &HandData(id, cluster, convexHull, 0, 0, &std::vector<FingerPoint*>());
	}

	std::vector<FingerPoint*>* newFingerPoints = DetectFingerPoints(convexHull, cluster, contour);
	std::vector<FingerPoint*>* fingerPoints = MapFingerPoints(lastFrameFingerPoints, newFingerPoints);

	std::vector<Point*>* candidates = &cluster->points;
	Palm *palm = 0;

	if (settings->DetectCenterOfPalm && cluster->Count() > 0 && contour->Count() > 0)
	{
		palm = palmFinder->FindCenter(contour, &cluster->points);
	}

	return new HandData(id, cluster, convexHull, contour, palm, fingerPoints);
}

std::vector<FingerPoint*>* HandDataFactory::MapFingerPoints(std::vector<FingerPoint*>* oldFingerPoints, std::vector<FingerPoint*>* newFingerPoints){
	IdGenerator* idGenerator = &IdGenerator();
	DistanceMap2b *distanceMap = new DistanceMap2b(oldFingerPoints, 100); //TODO)
	distanceMap->Map(newFingerPoints);
	std::vector<FingerPoint*>::iterator iter;
	std::tr1::tuple<FingerPoint*,FingerPoint*>* tupple;
	std::vector<std::tr1::tuple<FingerPoint*,FingerPoint*>*>::iterator iter1;
	for (iter1 = distanceMap->MappedItems->begin();iter1<distanceMap->MappedItems->end();iter1++) {

		tupple = (std::tr1::tuple<FingerPoint*,FingerPoint*>*)*iter1;
		idGenerator->SetUsed(std::get<0>(*tupple)->Id);
		std::get<1>(*tupple)->Id = std::get<0>(*tupple)->Id;
	}
	
	FingerPoint* newFinger;
	FingerPoint* otherFinger;
	for (iter=distanceMap->UnmappedItems->begin();iter<distanceMap->UnmappedItems->end();iter++) {
		newFinger = (FingerPoint*)*iter;
		newFinger->Id = idGenerator->GetNextId();
	}
	

	std::vector<FingerPoint*>* out= new std::vector<FingerPoint*>;
	
	//distanceMap->MappedItems.Select(i => i.Item2).Union(distanceMap.UnmappedItems).ToList();
	for (iter=distanceMap->UnmappedItems->begin();iter<distanceMap->UnmappedItems->end();iter++) {
		otherFinger = (FingerPoint*)*iter;
		for (iter1=distanceMap->MappedItems->begin();iter1<distanceMap->MappedItems->end();iter1++) {
			tupple = (std::tr1::tuple<FingerPoint*,FingerPoint*>*)*iter1;

			newFinger = std::get<1>(*tupple);
			if (newFinger==otherFinger) {
				out->push_back(newFinger);
			}
		}
	}
			return out;
}

Contour *HandDataFactory::CreateContour(BinaryMap* map, Cluster* cluster){
	return contourFactory->CreateContour(map, cluster->vol.location->x, cluster->vol.location->y);
}

std::vector<FingerPoint*>* HandDataFactory::DetectFingerPoints(ConvexHull *convexHull, Cluster* cluster, Contour* contour){
	if (!settings->DetectFingers || contour->Count() < 3)
	{
		return new std::vector<FingerPoint*>;
	}
	return fingerPointDetector->FindFingerPoints(contour, convexHull);
}

BinaryMap* HandDataFactory::CreateMap(Cluster* cluster)        {
	BinaryMap* map = new BinaryMap(cluster->vol.width + 1, cluster->vol.height + 1);
	std::vector<Point*>::iterator iter;
	for (iter = cluster->AllPoints.begin(); iter < cluster->AllPoints.end(); iter++) {
		Point* p = (Point*)*iter;
		map->map[(int)(p->x - cluster->vol.location->x)][(int)(p->y - cluster->vol.location->y)] = 1;
	}
	return map;
}
