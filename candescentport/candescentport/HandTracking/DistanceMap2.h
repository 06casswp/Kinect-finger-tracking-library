#ifndef DISTMAP2_H
#define DISTMAP2_H
#include <vector>
#include <tuple>
#include <limits>

template <class TLeft, class TRight> class DistanceMap2 //this is to work out the distance between 2 ilocatable items
	//where TLeft: ILocatable
	//where TRight: ILocatable
{
public:
	double maxMoveDistance;
	std::vector<TLeft>* originalItems;
	std::vector<std::tuple<TLeft, TRight>*>* MappedItems;

	std::vector<TRight>* UnmappedItems;

	std::vector<TLeft>* DiscontinuedItems;

	DistanceMap2(std::vector<TLeft>* originalItems1, double maxMoveDistance1){
		originalItems = originalItems1;
		maxMoveDistance = maxMoveDistance1;


	}

	void Map(std::vector<TRight>* newItems){
		/*std::vector<std::tuple<TLeft, TRight>*>*MappedItems = new std::vector<std:tuple<TLeft, TRight>*>;
		std::vector<TRight>* UnmappedItems = new std::vector<TRight>;
		std::vector<TRight>::iterator iter;
		std::vector<TLeft>::iterator iter1;
		pointfunctions pntfnc;
		for (iter=newItems->begin();iter<newItems->end();iter++)
		{
			TRight newItem = (TRight*)*iter;
			TLeft minItem = default(TLeft);
			double minDistance = std::numeric_limits<double>::max();
			for (iter1=originalItems->begin();iter1<originalItems->end();iter1++) 
			{
				//oldItem
				TLeft oldItem = (TLeft*)*iter1;

				double distance = 0;//pntfnc.distance(oldItem.Location, newItem.Location);
				if (distance < minDistance)
				{
					minItem = oldItem;
					minDistance = distance;
				}
			}
			if (minDistance <= maxMoveDistance)
			{
				originalItems->erase(iter);
				MappedItems->push_back(new std::tuple<TLeft, TRight>(minItem, newItem));
			}
			else
			{
				UnmappedItems->push_back(newItem);
			}
		}


	*/}


};

#endif 