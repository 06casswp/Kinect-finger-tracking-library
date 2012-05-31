
#include "clustermerger.h"



void ClusterMerger::MergeclusterdatsIfRequired(clusterdat** clusterdats, int* count){
	
	int index = 0;
	int index1 = 0;
	a:
		for (index=0;index<settings->clusterdatcount;index++) {
			if (clusterdats[index]) {
				for (index1=0;index1<settings->clusterdatcount;index1++) {
					if (clusterdats[index1]) {
						if (!(clusterdats[index]==clusterdats[index1])) {
							if (IsMergeRequired(clusterdats[index],clusterdats[index1])) {
								cfnc.Merge(clusterdats[index],clusterdats[index1]);
								*count--;
								clusterdats[index1]=0;
								int check = 0;
								while (check<(settings->clusterdatcount-1)) {
									if (clusterdats[check]==0) {
										clusterdats[check] = clusterdats[check+1];
									}
									check++;
								}
								goto a;
							}
						}
					}
				}
			}
		}
	}








bool ClusterMerger::IsMergeRequired(clusterdat* clusterdat1, clusterdat* clusterdat2)
{
	return cfnc.DistanceMetric(clusterdat1, clusterdat2) < settings->MergeMinimumDistanceToclusterdat || pntman.distance(&clusterdat1->center, &clusterdat2->center) < settings->MergeMaximumclusterdatCenterDistances || pntman.distance(clusterdat1->center.x, clusterdat1->center.y, clusterdat2->center.x, clusterdat2->center.y) < settings->MergeMaximumclusterdatCenterDistances2D;
}

