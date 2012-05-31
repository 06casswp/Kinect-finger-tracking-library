#include "HandDataFactory.h"
#include "GrahamScan.h"
#include "Palm.h"
#include "DistanceMap2.h"


	


void HandDataFactory::setsettings() {
	fingerpointDetector.settings = settings;
	contourFactory.tracer.maximumRetraceSteps = settings->MaximumRetraceSteps;
	contourFactory.thinner.checkBoundary = false;
	contourFactory.thinner.mindDistBetweenpoints = settings->ContourLineThinningDistance;
	palmFinder.searchRadius = settings->PalmAccuracySearchRadius;
	palmFinder.contourReduction = settings->PalmContourReduction;
}

void HandDataFactory::ReturnId(int id){

	idGenerator.Return(id);
}

HandData* HandDataFactory::Create(clusterdat* clusterdat){ //create new
	HandData* HD = new HandData(idGenerator.GetNextId(),clusterdat,0,0,0,0);

	return Create1(HD);
}

HandData* HandDataFactory::Create(HandData* lastFrameData, clusterdat* clusterdat)//reuse old
{
	lastFrameData->clusterdata = clusterdat;
	return Create1(lastFrameData);
}

void HandDataFactory::ClearIds()
{
	idGenerator.Clear();
}



HandData* HandDataFactory::Create1(HandData* HD){ //if existing handdata, be sure to delete convexhull, contour etc
	DepthMapFnc dfnc;
	
	if (HD->convexHull) {
		free(HD->convexHull);
		extern int hulls;
		hulls--;
		HD->convexHull = 0;
	}
	if (HD->contour) {
		free(HD->contour);
		extern int contours;
		contours--;
		HD->contour = 0;
	}

	GS.set(HD->clusterdata->allpointpnt,HD->clusterdata->allpointscnt);
	
	HD->convexHull = GS.FindHull(); //new created here! cleared when handdata's are cleared

	depthmapdat* map = CreateMap(HD->clusterdata); //new created here! cleared just here

	HD->contour = contourFactory.CreateContour(map, HD->clusterdata->vol.location.x, HD->clusterdata->vol.location.y);
	dfnc.remove(map);
	delete map;

	int count2 = 0;
	HD->FingerpointCount = count2;
	//
	if (HD->contour->newpointcnt < settings->MinimalpointsInContour)
	{
		return HD;
	}
	
	Fingerpoint** newFingerpoints = 0;
	newFingerpoints = DetectFingerpoints(HD->convexHull, HD->contour,&count2); //may return 0 if none found!
	HD->Fingerpoints = newFingerpoints;// = MapFingerpoints(HD->Fingerpoints, HD->FingerpointCount,newFingerpoints,count2,&HD->FingerpointCount);
	
	
	HD->FingerpointCount = count2;
	
	
	if (settings->DetectCenterOfPalm && HD->clusterdata->allpointpnt > 0 && HD->contour->newpointcnt > 0)
	{
		//HD->palm = palmFinder.FindCenter(HD->contour, HD->clusterdata->allpointpnt,HD->clusterdata->allpointscnt );
	}

	
	
	return HD;
}

Fingerpoint** HandDataFactory::MapFingerpoints(Fingerpoint** oldFingerpoints, int count, Fingerpoint** newFingerpoints, int count1, int* count2){
	
	distanceMap.set(oldFingerpoints, 100, count);
	distanceMap.map(newFingerpoints,count1);
	*count2 = count1;
	std::tr1::tuple<Fingerpoint*,Fingerpoint*>* tupple;
	
	int i = 0;
	for (i = 0;i<distanceMap.mappeditemcount;i) {

		tupple = distanceMap.mappeditems[i];
		idGenerator.SetUsed(std::get<0>(*tupple)->Id);
		std::get<1>(*tupple)->Id = std::get<0>(*tupple)->Id;
	}
	
	Fingerpoint* newFinger;
	Fingerpoint* otherFinger;
	for (i=0;i<distanceMap.unmappeditemcount;i++) {
		newFinger = distanceMap.UnmappedItems1[i];
		newFinger->Id = idGenerator.GetNextId();
	}
	
	Fingerpoint* out[100];
	*count2 = 0;
	
	int j = 0;
		for (i=0;i<distanceMap.unmappeditemcount;i++) {
		otherFinger = distanceMap.UnmappedItems1[i];
		for (j=0;j<distanceMap.mappeditemcount;j++) {
			tupple = distanceMap.mappeditems[j];

			newFinger = std::get<1>(*tupple);
			if (newFinger==otherFinger) {
				out[*count2] = newFinger;
				*count2++;
			}
		}
	}
	return out;
}


Fingerpoint** HandDataFactory::DetectFingerpoints(ConvexHull *convexHull, Contour* contour, int* outcount){
	if (!settings->DetectFingers)
	{
		*outcount = 0;
		return 0;
	}
	return fingerpointDetector.FindFingerpoints(contour, convexHull, outcount);
}

depthmapdat* HandDataFactory::CreateMap(clusterdat* clusterdat)        {
	depthmapdat* map = new depthmapdat;
	DepthMapFnc dfnc;
	dfnc.create(map,clusterdat->vol.width + 1, clusterdat->vol.height + 1);
	int i = 0;
	for (i = 0; i<clusterdat->allpointscnt; i++) {
		map->map[clusterdat->allpointpnt[i]->x - clusterdat->vol.location.x][clusterdat->allpointpnt[i]->y - clusterdat->vol.location.y] = 1;
	}

	return map;
}

HandDataFactory::HandDataFactory(){


}