
#ifndef CLUSTDAT_H
#define CLUSTDAT_H


#include <vector>
#include "clusters.h"


class ClusterData
{
public:
	ClusterData();

	ClusterData(std::vector<Cluster*>* clusters);

	std::vector<Cluster*>* Clusters;

	int Count();
};




#endif 