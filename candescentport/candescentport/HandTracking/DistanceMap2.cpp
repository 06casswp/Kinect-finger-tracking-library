#include "DistanceMap2.h"



void DistanceMap2a::set(HandData** originalitems1, double maxMoveDistance1, int count) {
	originalitems = originalitems1;
	originalitemscount = count;
	maxMoveDistance = maxMoveDistance1;
}


void DistanceMap2a::map(clusterdat** newitems, int count) {

	mappeditems = (std::tr1::tuple<HandData*, clusterdat*>**)malloc(count*sizeof(std::tr1::tuple<HandData*, clusterdat*>*));

	UnmappedItems1 = (clusterdat**)malloc(count*sizeof(clusterdat*));
	
	clusterdat* newItem;
	HandData* oldItem;
	HandData* minItem;
	int i = 0;
	for (i=0;i<count;i++) {
		newItem = newitems[i];
		double minDistance = 9999999999999999;

		int j = 0;
		if (originalitemscount>0) {
			for (j=0;j<originalitemscount;j++) {
				oldItem = originalitems[j];
				double distance = pntfnc.distance(oldItem->Center(), &newItem->center);
				if (distance < minDistance)
				{
					minItem = oldItem;
					minDistance = distance;
				}
			}
		}
		if (minDistance <= maxMoveDistance)
		{
			//remove minitem from original items, move to the tuple!
			if (originalitemscount>1) {
				for (j=0;j<originalitemscount-1;j++) {

					if (originalitems[j]==minItem) {
						originalitems[j] = 0;
					}
					if (originalitems[j] == 0) {
						originalitems[j] = originalitems[j+1];
					}
					originalitemscount--;
				}
				
			}
			else if(originalitemscount==1) {
				originalitems[0] = 0;
				originalitemscount = 0;
			}

			mappeditems[mappeditemcount] = new std::tr1::tuple<HandData*, clusterdat*>(minItem, newItem);
			mappeditemcount++;
		}
		else
		{
			UnmappedItems1[unmappeditemcount] = newItem; //if no handdata's are found/matched, the clusterdat goes here!
			unmappeditemcount++;
		}
	}
	

}

	void DistanceMap2a::reset(){
		//delete malloc'd (free()) stuff ie UnmappedItems1, mappeditems, DiscontinuedItems1
		//iterate through and delete tuple's!!!!!!!!!!!!!!!!!!!!!!_---------------------------
		if (UnmappedItems1) {
			free(UnmappedItems1);
			UnmappedItems1 = 0;
		}
		if (mappeditems) {
			free(mappeditems);
			mappeditems = 0;
		}
		
		unmappeditemcount = 0;
		mappeditemcount = 0;
		
		
		
		//original items is handdata i assume from last time round! (this is to ensure that the clusters are assigned to the same handdatas)


	}
	void DistanceMap2a::init() {
		unmappeditemcount = 0;
		mappeditemcount = 0;
		UnmappedItems1 = 0;
		mappeditems = 0;
		originalitems = 0;
		originalitemscount = 0;
}

	
void DistanceMap2b::set(Fingerpoint** originalitems1, double maxMoveDistance1, int count) {
	originalitems = originalitems1;
	originalitemscount = count;
	maxMoveDistance = maxMoveDistance1;
}

void DistanceMap2b::init() {
		unmappeditemcount = 0;
		mappeditemcount = 0;
		UnmappedItems1 = 0;
		mappeditems = 0;
		originalitems = 0;
		originalitemscount = 0;
}


	void DistanceMap2b::reset(){
		//delete malloc'd (free()) stuff ie UnmappedItems1, mappeditems, DiscontinuedItems1
		//iterate through and delete tuple's!!!!!!!!!!!!!!!!!!!!!!_---------------------------
		free(UnmappedItems1);
		free(mappeditems);
		
		
		unmappeditemcount = 0;
		mappeditemcount = 0;
		UnmappedItems1 = 0;
		mappeditems = 0;
		
		//original items is handdata i assume from last time round! (this is to ensure that the clusters are assigned to the same handdatas)


	}


void DistanceMap2b::map(Fingerpoint** newitems, int count) {

	mappeditems = (std::tr1::tuple<Fingerpoint*, Fingerpoint*>**)malloc(count*sizeof(std::tr1::tuple<Fingerpoint*, Fingerpoint*>*));

	UnmappedItems1 = (Fingerpoint**)malloc(count*sizeof(Fingerpoint*));
	unmappeditemcount = 0;
	Fingerpoint* newItem;
	Fingerpoint* oldItem;
	Fingerpoint* minItem;
	int i = 0;
	for (i=0;i<count;i++) {
		newItem = newitems[i];
		double minDistance = 9999999999999999;

		int j = 0;
		for (j=0;j<originalitemscount;j++) {
			oldItem = originalitems[j];
			double distance = pntfnc.distance(oldItem->location, newItem->location);
			if (distance < minDistance)
			{
				minItem = oldItem;
				minDistance = distance;
			}
		}
		if (minDistance <= maxMoveDistance)
		{
			//remove minitem from original items, move to the tuple!
			if (originalitemscount>1) {
				for (j=0;j<originalitemscount-1;j++) {

					if (originalitems[j]==minItem) {
						originalitems[j] = 0;
					}
					if (originalitems[j] == 0) {
						originalitems[j] = originalitems[j+1];
					}
				}
				originalitemscount--;
			}
			else if(originalitemscount==1) {
				originalitems[0] = 0;
				originalitemscount = 0;
			}

			mappeditems[mappeditemcount] = new std::tr1::tuple<Fingerpoint*, Fingerpoint*>(minItem, newItem);
			mappeditemcount++;
		}
		else
		{
			UnmappedItems1[unmappeditemcount] = newItem; //if no Fingerpoint's are found/matched, the Fingerpoint goes here!
			unmappeditemcount++;
		}
	}
	

}
