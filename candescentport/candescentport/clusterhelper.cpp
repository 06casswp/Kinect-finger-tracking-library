#include "clusterhelper.h"
#include "rectangle.h"
#include "kmeans.h"

ClusterHelper::ClusterHelper(ClusterDataSourceSettings* settings1, intsize *size){
	settings = settings1;
	clusterMergerz = new ClusterMerger(settings);
	algorithm = new KMeans(settings->ClusterCount, settings1->DepthRange(), size);
	value = new ClusterData();

}

ClusterData* ClusterHelper::Update(std::vector<Point*>* allPointsInDepthRange){
	std::vector<Point*>* reducedPoints = ReducePoints(allPointsInDepthRange);

	if (AreEnoughPointsForClustering((int)reducedPoints->size()))
	{
		FindClusters(reducedPoints);
		AssignAllPoints(allPointsInDepthRange);
	}
	else
	{
		value = new ClusterData();
	}
	return value;

}

bool ClusterHelper::AreEnoughPointsForClustering(int count){
	return count >= settings->MinimalPointsForClustering;

}

std::vector<Point*>* ClusterHelper::ReducePoints(std::vector<Point*>* points){
	std::vector<Point*>::iterator iter;
	std::vector<Point*>* outp;
	Point* tmp;
	for (iter=points->begin();iter<points->end();iter++) {
		tmp = (Point*)*iter;
		int mod = settings->PointModulo;
		if (((int)tmp->x % mod == 0) && ((int)tmp->y%mod == 0)) {
			outp->push_back(tmp);
		}
	}//points.Where(p => p.X % ClusterHelper::settings.PointModulo == 0 && p.Y % ClusterHelper::settings.PointModulo == 0).ToList();

	return outp;

}

void ClusterHelper::FindClusters(std::vector<Point*>* pointList){
	InitializeAlgorithm(pointList);
	algorithm->IterateUntilStable();

	if (algorithm->ClusterCount > 0)
	{
		value = new ClusterData(FlattenIfRequired(MergeClustersIfRequired(algorithm->Clusters)));
	}

}

std::vector<Cluster*>* ClusterHelper::FlattenIfRequired(std::vector<Cluster*>* clusters){
	if (settings->MaximumClusterDepth)
	{
		std::vector<Cluster*>::iterator iter;
		Cluster* c1;
		for (iter = clusters->begin();iter<clusters->end();iter++) 
		{
			c1 = (Cluster*)*iter;
			c1->Flatten(settings->MaximumClusterDepth);
		}
	}
	return clusters;

}

void ClusterHelper::InitializeAlgorithm(std::vector<Point*>* pointList){
	ClusterHelper::algorithm->Initialize(pointList);

}
void ClusterHelper::AssignAllPoints(std::vector<Point*>* fullList){
	std::vector<Cluster*>::iterator iter;
	std::vector<Point*>* allPoints = new std::vector<Point*>;
	std::vector<Point*>::iterator iter1;
	Rectanglez* area;
	Cluster* c1;
	Point* p1;
	for (iter=value->Clusters->begin(); iter<value->Clusters->end();iter++) {
		c1 = (Cluster*)*iter;

		area = &c1->Area();
		for (iter1=fullList->begin();iter1<fullList->end();iter1++) 
		{
			p1 = (Point*)*iter1;
			if (area->Contains(p1))
			{
				allPoints->push_back(p1);
			}
		}
		c1->AllPoints = allPoints;
	}

}

std::vector<Cluster*>* ClusterHelper::MergeClustersIfRequired(std::vector<Cluster*>* clusters){
	std::vector<Cluster*>::iterator iter;
	std::vector<Cluster*>* localClusters = new std::vector<Cluster*>;
	Cluster* c1;
	for (iter=clusters->begin();iter<clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		if (c1->Count()>settings->MinimalPointsForValidCluster) {
			localClusters->push_back(c1);
		}
	}



	if (localClusters->size() > 1)
	{
		int clusterCount;
		do
		{
			clusterCount = localClusters->size();
			localClusters = clusterMergerz->MergeClustersIfRequired(localClusters);
		}             
		while (localClusters->size() != clusterCount);
	}
	return localClusters;

}