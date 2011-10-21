#ifndef CLUSTERDATSRCSET_H
#define CLUSTERDATSRCSET_H
#include "Range.h"

class ClusterDataSourceSettings
{
public:
	int ClusterCount;
	int LowerBorder;
	int PointModulo;
	int MinimumDepthThreshold;
	int MaximumDepthThreshold;
	Range* DepthRange();
	int MinimalPointsForClustering;
	int MinimalPointsForValidCluster;
	double MergeMinimumDistanceToCluster;
	double MergeMaximumClusterCenterDistances;
	double MergeMaximumClusterCenterDistances2D;
	int MaximumClusterDepth;
	void SetToDefault();
	void SetToFast();
	void SetToAccurate();
	ClusterDataSourceSettings();

};



#endif 