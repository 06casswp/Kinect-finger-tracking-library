#ifndef CLUSTERMERG_H
#define CLUSTERMERG_H

#include "clusterdatasrc.h"
#include "clusters.h"
#include "pointfnc.h"


class ClusterMerger
{
public:
	ClusterDataSourceSettings* settings;
	pointfunctions pntfnc;

	ClusterMerger(ClusterDataSourceSettings* settings);

	std::vector<Cluster*>* MergeClustersIfRequired(std::vector<Cluster*>* clusters);

	bool IsMergeRequired(Cluster* cluster1, Cluster* cluster2);

	void remove(std::vector<Cluster*>* clusters, Cluster* c1);

};

#endif 