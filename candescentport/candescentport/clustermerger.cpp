
#include "clustermerger.h"


ClusterMerger::ClusterMerger(ClusterDataSourceSettings* settings1)
{
	settings = settings1;
}

std::vector<Cluster*>* ClusterMerger::MergeClustersIfRequired(std::vector<Cluster*>* clusters)
{
	std::vector<Cluster*>::iterator iter;
	std::vector<Cluster*>::iterator iter1;
	//check each against every other
	//check for 2 instances of each given comparing to several :(
	//iterate through each cluster, then iterate through each other cluster 
	Cluster* c1;
	Cluster* c2;

	for (iter=clusters->begin();iter<clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		for (iter1==clusters->begin();iter1<clusters->end();iter1++) {
			c2 = (Cluster*)*iter1;
			if (!(c1==c2)) {
				if (IsMergeRequired(c1,c2)) {
					Cluster* merged = c1->Merge(c2);
					remove(clusters, c1);
					remove(clusters, c2);
					clusters->push_back(merged);
				}
			}
		}
	}

	return clusters;
}

bool ClusterMerger::IsMergeRequired(Cluster* cluster1, Cluster* cluster2)
{
	return cluster1->DistanceMetric(cluster2) < settings->MergeMinimumDistanceToCluster || pntfnc.distance(cluster1->center, cluster2->center) < settings->MergeMaximumClusterCenterDistances || pntfnc.distance(cluster1->center->x, cluster1->center->y, cluster2->center->x, cluster2->center->y) < settings->MergeMaximumClusterCenterDistances2D;
}

void ClusterMerger::remove(std::vector<Cluster*>* clusters, Cluster* c1) {
	std::vector<Cluster*>::iterator iter;
	Cluster* tmp;
	for (iter=clusters->begin();iter<clusters->end();iter++) {
		tmp = (Cluster*)*iter;
		if (tmp==c1) {
			clusters->erase(iter);
			return;
		}
	}
}