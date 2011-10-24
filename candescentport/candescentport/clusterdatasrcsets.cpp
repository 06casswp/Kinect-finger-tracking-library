#include "clusterdatasrc.h"


void ClusterDataSourceSettings::SetToDefault(){

	MinimalPointsForValidCluster = 10;
	MinimalPointsForClustering = 50;
	PointModulo = 5;
	LowerBorder = 0;
	MinimumDepthThreshold = 500;
	MaximumDepthThreshold = 700;
	ClusterCount = 2;

	MergeMinimumDistanceToCluster = 50;
	MergeMaximumClusterCenterDistances = 120;
	MergeMaximumClusterCenterDistances2D = 100;

	MaximumClusterDepth = 150;

}
void ClusterDataSourceSettings::SetToFast(){

	SetToDefault();
	PointModulo = 6;

}
void ClusterDataSourceSettings::SetToAccurate(){
	SetToDefault();
	PointModulo = 4;



}

Range* ClusterDataSourceSettings::DepthRange(){
	depth = new Range(MinimumDepthThreshold, MaximumDepthThreshold);
	return depth;


}

ClusterDataSourceSettings::ClusterDataSourceSettings(){
	SetToDefault();


}