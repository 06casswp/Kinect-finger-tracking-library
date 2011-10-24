#ifndef CLUSTFAC_H
#define CLUSTFAC_H

#include "clusters.h"
#include "intsize.h"

class ClusterFactory
{
public:
	//Random random = new Random();
	std::vector<Cluster*>* createdclusters;

	std::vector<Cluster*>* CreateClusters(int numberOfClusters, intsize* areaSize);

	Cluster* CreateClusterWithin(int minX, int maxX, int minY, int maxY);
};









#endif 