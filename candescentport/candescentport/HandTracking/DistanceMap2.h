#ifndef DISTMAP2_H
#define DISTMAP2_H
#include <vector>
#include <tuple>
#include <limits>
#include "HandData.h"
#include "../clusters.h"
#include "Fingerpoint.h"

class DistanceMap2a //this is to work out the distance between 2 ilocatable items
	//where HandData*: ILocatable
	//where clusterdat*: ILocatable
{
public:
	double maxMoveDistance;

	HandData** originalitems;
	int originalitemscount;
	pointman pntfnc;
	
	std::tr1::tuple<HandData*, clusterdat*>** mappeditems;
	int mappeditemcount;

	
	clusterdat** UnmappedItems1;
	int unmappeditemcount;

	


	void set(HandData** originalitems1, double maxMoveDistance1, int count);
	void reset();
	void map(clusterdat** newitems, int count);
	void init();

};

class DistanceMap2b //this is to work out the distance between 2 ilocatable items
	//where Fingerpoint*: ILocatable
	//where Fingerpoint*: ILocatable
{
public:
	double maxMoveDistance;

	Fingerpoint** originalitems;
	int originalitemscount;
	pointman pntfnc;

	std::tr1::tuple<Fingerpoint*, Fingerpoint*>** mappeditems;
	int mappeditemcount;

	Fingerpoint** UnmappedItems1;
	int unmappeditemcount;

	void set(Fingerpoint** originalitems1, double maxMoveDistance1, int count);
	void reset();
	void map(Fingerpoint** newitems, int count);
	void init();
};


#endif 