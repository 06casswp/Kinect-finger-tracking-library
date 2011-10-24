#include "clusterfactory.h"
#include "intsize.h"
#include <time.h>


std::vector<Cluster*>* ClusterFactory::CreateClusters(int numberOfClusters, intsize* areaSize){
	
	if ((numberOfClusters>=0)&&(areaSize->Width > 0 && areaSize->Height > 0)) {
		createdclusters = new std::vector<Cluster*>;


		float sliceWidth = areaSize->Width / numberOfClusters;
		float sliceHeight = areaSize->Height / numberOfClusters;

		for (int index = 0; index < numberOfClusters; index++)
		{
			int minX = (int)((index) * sliceWidth);
			int maxX = (int)((index + 1) * sliceWidth);
			int minY = (int)((index) * sliceHeight);
			int maxY = (int)((index + 1) * sliceHeight);
			createdclusters->push_back(CreateClusterWithin(minX, maxX, minY, maxY));
		}


	}
	return createdclusters;


}

Cluster* ClusterFactory::CreateClusterWithin(int minX, int maxX, int minY, int maxY){
	//next is random number between the ranges
	srand(time(NULL));
	int a = rand()%(maxX-minX-1)+minX;
	int b = rand()%(maxY-minY-1)+minY;
	return new Cluster(a, b, 0);


}