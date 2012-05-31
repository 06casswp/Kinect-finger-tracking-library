#include "clusterdatasrc.h"


void ClusterDataSourceSettings::SetToDefault(){

	MinimalpointsForValidclusterdat = 10;
	MinimalpointsForclusterdating = 50;
	pointModulo = 5;
	LowerBorder = 0;
	MinimumDepthThreshold = 0;
	MaximumDepthThreshold = 200;
	clusterdatCount = 2;
	clusterdatcount = 2;

	MergeMinimumDistanceToclusterdat = 50;
	MergeMaximumclusterdatCenterDistances = 120;
	MergeMaximumclusterdatCenterDistances2D = 100;

	MaximumclusterdatDepth = 150;

}
void ClusterDataSourceSettings::SetToFast(){

	SetToDefault();
	pointModulo = 6;

}
void ClusterDataSourceSettings::SetToAccurate(){
	SetToDefault();
	pointModulo = 4;



}


rangedat* ClusterDataSourceSettings::DepthRange() {
	 depth.max = MaximumDepthThreshold;
	 depth.min = MinimumDepthThreshold;
	 return &depth;
}

