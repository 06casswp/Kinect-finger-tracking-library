#include "HandDataSource.h"
#include "HandDataFactory.h"
#include "DistanceMap2.h"
#include "../clusterdatasrc.h"

void HandDataSource::start() {
	settings.SetToDefault();
	results = 0;
	map.init();
	factory.distanceMap.init();
	results = 0;
	handcoll.count = 0;
	handcoll.hands = 0;
	factory.idGenerator.usedIds = new std::vector<int>;
}

HandDataSource::HandDataSource() {

}

HandCollection* HandDataSource::Process(clusterdat** ClusterData1,sizedat* size, int count){
	Size = *size;
	factory.settings = &settings;
	factory.setsettings();

	if (count == 0)
	{
		factory.ClearIds();
		return 0;
	}
	
	//create max number of handdatas into handcollection

	map.reset();
	map.set(handcoll.hands, 100,handcoll.count); //give the new process the old results!
	map.map(ClusterData1, count);
	HandData** oldresults;
	if (results) {
		oldresults = results;
	}
	else
	{
		oldresults = 0;
	}
	results = (HandData**)malloc(sizeof(HandData*)*count);
	resultcount = 0;


	clusterdat * cl;

	std::tr1::tuple<HandData*,clusterdat*>* tupple;
	int i = 0;

	for (i = 0; i<map.mappeditemcount; i++) {
		tupple = map.mappeditems[i];
		results[resultcount] = factory.Create(std::get<0>(*tupple), std::get<1>(*tupple)); //doesnt create a new 1
		resultcount++;
	}
	for (i = 0; i<map.unmappeditemcount; i++) {
		cl = map.UnmappedItems1[i];
		results[resultcount] = factory.Create(cl); //creates a new 1
		resultcount++;
	}
	for (i = 0; i<map.originalitemscount; i++) {
		factory.ReturnId(map.originalitems[i]->id);
		free(map.originalitems[i]->convexHull);
		free(map.originalitems[i]->contour);
		extern int contours;
		contours--;
		extern int hulls;
		hulls--;
		free(map.originalitems[i]);//this is where the unused handdata's are removed!
		map.originalitems[i] = 0;
	}
	map.originalitemscount = 0;
	
	if (oldresults) {
		delete oldresults;
	}

	handcoll.hands = results;
	handcoll.count = resultcount;
	return &handcoll;
}



	int HandDataSource::Width(){
		return Size.Width;
	}


	int HandDataSource::Height(){
		return Size.Height;
	}