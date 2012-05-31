#ifndef clusterdatMERG_H
#define clusterdatMERG_H

#include "clusterdatasrc.h"
#include "clusters.h"
#include "point.h"


class ClusterMerger
{
public:
	ClusterDataSourceSettings* settings;
	pointman pntman;
	clusterfnc cfnc;
	


	void MergeclusterdatsIfRequired(clusterdat** clusterdats,int* count);


	bool IsMergeRequired(clusterdat* clusterdat1, clusterdat* clusterdat2);


};

#endif 