#ifndef CLUSTERHELPER_H
#define CLUSTERHELPER_H

//#include "clusterdatasrc.h"
#include "Point.h"
#include "clusters.h"

#include "clusterdata.h"
#include "kmeans.h"
#include "clustermerger.h"

class ClusterHelper
{

public:
	ClusterMerger* clusterMergerz;
	KMeans* algorithm;
	std::vector<Point*>* localcpy;
	ClusterDataSourceSettings settings;
	ClusterData* value;
	std::vector<Point*>* outp;

	ClusterHelper(ClusterDataSourceSettings* settings1, intsize* size);

	ClusterData* Update();

	bool AreEnoughPointsForClustering(int count);

	std::vector<Point*>* ReducePoints(std::vector<Point*>* points);

	void FindClusters(std::vector<Point*>* pointList);

	std::vector<Cluster*>* FlattenIfRequired(std::vector<Cluster*>* clusters);

	void InitializeAlgorithm(std::vector<Point*>* pointList);
	void AssignAllPoints(std::vector<Point*>* fullList);

	std::vector<Cluster*>* MergeClustersIfRequired(std::vector<Cluster*>* clusters);



};

#endif 