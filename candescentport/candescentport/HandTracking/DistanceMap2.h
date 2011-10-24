#ifndef DISTMAP2_H
#define DISTMAP2_H
#include <vector>
#include <tuple>
#include <limits>
#include "HandData.h"
#include "../clusters.h"
#include "FingerPoint.h"

class DistanceMap2a //this is to work out the distance between 2 ilocatable items
	//where HandData*: ILocatable
	//where Cluster*: ILocatable
{
public:
	double maxMoveDistance;
	std::vector<HandData*>* originalItems;
	std::vector<std::tr1::tuple<HandData*, Cluster*>*>* MappedItems;

	std::vector<Cluster*>* UnmappedItems;

	std::vector<HandData*>* DiscontinuedItems;

	DistanceMap2a(std::vector<HandData*>* originalItems1, double maxMoveDistance1){
		originalItems = originalItems1;
		maxMoveDistance = maxMoveDistance1;


	}

	void Map(std::vector<Cluster*>* newItems){
		MappedItems = new std::vector<std::tr1::tuple<HandData*, Cluster*>*>;
		UnmappedItems = new std::vector<Cluster*>;
		DiscontinuedItems = new std::vector<HandData*>;
		std::vector<Cluster*>::iterator iter;
		std::vector<HandData*>::iterator iter1;
		pointfunctions pntfnc;
		Cluster* newItem;
		HandData* oldItem;
		HandData* minItem;
		for (iter=newItems->begin();iter<newItems->end();iter++)
		{
			newItem = (Cluster*)*iter;
			//HandData* minItem = default(HandData*);
			double minDistance = 9999999999999999;
			for (iter1=originalItems->begin();iter1<originalItems->end();iter1++) 
			{
				//oldItem
				oldItem = (HandData*)*iter1;

				double distance = pntfnc.distance(oldItem->Location(), newItem->Location);
				if (distance < minDistance)
				{
					minItem = oldItem;
					minDistance = distance;
				}
			}
			if (minDistance <= maxMoveDistance)
			{
				originalItems->erase(iter1);
				MappedItems->push_back(new std::tr1::tuple<HandData*, Cluster*>(new HandData(minItem->id,minItem->cluster,minItem->convexHull,minItem->contour,minItem->palm,minItem->FingerPoints), new Cluster(newItem->center,newItem->points)));
			}
			else
			{
				UnmappedItems->push_back(new Cluster(newItem->center,newItem->points));
			}
		}
		printf("\nClusters Mapped");

	}


};

class DistanceMap2b //this is to work out the distance between 2 ilocatable items
	//where FingerPoint*: ILocatable
	//where FingerPoint*: ILocatable
{
public:
	double maxMoveDistance;
	std::vector<FingerPoint*>* originalItems;
	std::vector<std::tr1::tuple<FingerPoint*, FingerPoint*>*>* MappedItems;

	std::vector<FingerPoint*>* UnmappedItems;

	std::vector<FingerPoint*>* DiscontinuedItems;

	DistanceMap2b(std::vector<FingerPoint*>* originalItems1, double maxMoveDistance1){
		originalItems = originalItems1;
		maxMoveDistance = maxMoveDistance1;


	}

	void Map(std::vector<FingerPoint*>* newItems){
		MappedItems = new std::vector<std::tr1::tuple<FingerPoint*, FingerPoint*>*>;
		UnmappedItems = new std::vector<FingerPoint*>;
		DiscontinuedItems = new std::vector<FingerPoint*>;
		std::vector<FingerPoint*>::iterator iter;
		std::vector<FingerPoint*>::iterator iter1;
		pointfunctions pntfnc;
		FingerPoint* newItem;
		FingerPoint* oldItem;
		FingerPoint* minItem;
		for (iter=newItems->begin();iter<newItems->end();iter++)
		{
			newItem = (FingerPoint*)*iter;
			//FingerPoint* minItem = default(FingerPoint*);
			double minDistance = 9999999999999999;
			for (iter1=originalItems->begin();iter1<originalItems->end();iter1++) 
			{
				//oldItem
				oldItem = (FingerPoint*)*iter1;

				double distance = pntfnc.distance(oldItem->Location, newItem->Location);
				if (distance < minDistance)
				{
					minItem = oldItem;
					minDistance = distance;
				}
			}
			if (minDistance <= maxMoveDistance)
			{
				originalItems->erase(iter1);
				MappedItems->push_back(new std::tr1::tuple<FingerPoint*, FingerPoint*>(minItem, newItem));
			}
			else
			{
				UnmappedItems->push_back(newItem);
			}
		}


	}


};


#endif 