#include "HandDataFactory.h"
#include "GrahamScan.h"
#include "Palm.h"
#include "DistanceMap2.h"

HandDataFactory::HandDataFactory(HandDataSourceSettings* settings1){
	settings = settings1;
	fingerPointDetector = new FingerPointDetector(settings);
	contourFactory = new ContourFactory(settings->ContourLineThinningDistance, settings->MaximumRetraceSteps);
	palmFinder = new PalmFinder(settings);

}

void HandDataFactory::ReturnId(int id){

	idGenerator.Return(id);
}

HandData* HandDataFactory::Create(Cluster* cluster){
	return Create(idGenerator.GetNextId(), cluster, new std::vector<FingerPoint*>);
}

HandData* HandDataFactory::Create(HandData* lastFrameData, Cluster* cluster)
{
	return Create(lastFrameData->id, cluster, lastFrameData->FingerPoints);
}

void HandDataFactory::ClearIds()
{
	idGenerator.Clear();
}

HandData* HandDataFactory::Create(int id, Cluster* cluster, std::vector<FingerPoint*>* lastFrameFingerPoints){
	GrahamScan* GS = new GrahamScan(cluster->points);
	ConvexHull* convexHull = GS->FindHull();
	BinaryMap* map = &CreateMap(cluster);

	Contour* contour = CreateContour(map, cluster);
	if (contour->Count() < settings->MinimalPointsInContour)
	{
		return new HandData(id, cluster, convexHull, 0, 0, new std::vector<FingerPoint*>);
	}

	std::vector<FingerPoint*>* newFingerPoints = DetectFingerPoints(convexHull, cluster, contour);
	std::vector<FingerPoint*>* fingerPoints = MapFingerPoints(lastFrameFingerPoints, newFingerPoints);

	std::vector<Point*>* candidates = cluster->points;
	Palm *palm = 0;

	if (settings->DetectCenterOfPalm && cluster->Count() > 0 && contour->Count() > 0)
	{
		palm = palmFinder->FindCenter(contour, cluster->points);
	}

	return new HandData(id, cluster, convexHull, contour, palm, fingerPoints);
}

std::vector<FingerPoint*>* HandDataFactory::MapFingerPoints(std::vector<FingerPoint*>* oldFingerPoints, std::vector<FingerPoint*>* newFingerPoints){
	IdGenerator* idGenerator = new IdGenerator();
	DistanceMap2<FingerPoint*, FingerPoint*> *distanceMap = new DistanceMap2<FingerPoint*, FingerPoint*>(oldFingerPoints, 100); //TODO)
	distanceMap->Map(newFingerPoints);
	std::vector<FingerPoint*>::iterator iter;
	/*
	foreach (var tuple in distanceMap.MappedItems)
	{
		idGenerator.SetUsed(tuple.Item1.Id);
		tuple.Item2.Id = tuple.Item1.Id;
	}
	*/
	FingerPoint* newFinger;
	FingerPoint* otherFinger;
	for (iter=distanceMap->UnmappedItems->begin();iter<distanceMap->UnmappedItems->end();iter++) {
		newFinger = (FingerPoint*)*iter;
		newFinger->Id = idGenerator->GetNextId();
	}
	

	std::vector<FingerPoint*>* out= new std::vector<FingerPoint*>;
	//std::vector<FingerPoint*>::iterator iter2; //tupple
	//distanceMap->MappedItems.Select(i => i.Item2).Union(distanceMap.UnmappedItems).ToList();
	for (iter=distanceMap->UnmappedItems->begin();iter<distanceMap->UnmappedItems->end();iter++) {
		otherFinger = (FingerPoint*)*iter;
		//for (iter2=distanceMap->MappedItems->begin();iter2<distanceMap->MappedItems->end();iter2++) {
			//newFinger = (FingerPoint*)* tupple;
			if (newFinger==otherFinger) {
				out->push_back(newFinger);
			}
		//}
	}
			return out;
}

Contour *HandDataFactory::CreateContour(BinaryMap* map, Cluster* cluster){
	return contourFactory->CreateContour(map, cluster->vol->location->x, cluster->vol->location->y);
}

std::vector<FingerPoint*>* HandDataFactory::DetectFingerPoints(ConvexHull *convexHull, Cluster* cluster, Contour* contour){
	if (!settings->DetectFingers || contour->Count() < 3)
	{
		return new std::vector<FingerPoint*>;
	}
	return fingerPointDetector->FindFingerPoints(contour, convexHull);
}

BinaryMap HandDataFactory::CreateMap(Cluster* cluster)        {
	BinaryMap* map = new BinaryMap(cluster->vol->width + 1, cluster->vol->height + 1);
	std::vector<Point*>::iterator iter;
	for (iter = cluster->AllPoints->begin(); iter < cluster->AllPoints->end(); iter++) {
		Point* p = (Point*)*iter;
		map->map[(int)(p->x - cluster->vol->location->x)][(int)(p->y - cluster->vol->location->y)] = 1;
	}
	return *map;
}
