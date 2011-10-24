#include "clusterhelper.h"
#include "rectangle.h"
#include "kmeans.h"

ClusterHelper::ClusterHelper(ClusterDataSourceSettings* settings1, intsize* size){
	settings = *settings1;
	clusterMergerz = new ClusterMerger(settings);
	algorithm = new KMeans(settings.ClusterCount, settings.DepthRange(), size);
	value = new ClusterData();

}

ClusterData* ClusterHelper::Update(){


	std::vector<Point*>* reducedPoints = ReducePoints(localcpy);

	if (AreEnoughPointsForClustering((int)reducedPoints->size()))
	{
		FindClusters(reducedPoints);
		AssignAllPoints(localcpy);
	}
	else
	{
		if (value) {
			delete value;
		}
		value = new ClusterData();
	}
	return value;

}

bool ClusterHelper::AreEnoughPointsForClustering(int count){
	return count >= settings.MinimalPointsForClustering;

}

std::vector<Point*>* ClusterHelper::ReducePoints(std::vector<Point*>* points){
	std::vector<Point*>::iterator iter;
	outp = new std::vector<Point*>;
	Point* tmp;
	for (iter=points->begin();iter<points->end();iter++) {
		tmp = (Point*)*iter;
		int mod = settings.PointModulo;
		if (((int)tmp->x % mod == 0) && ((int)tmp->y%mod == 0)) {
			outp->push_back(new Point(tmp));
		}
	}//points.Where(p => p.X % ClusterHelper::settings.PointModulo == 0 && p.Y % ClusterHelper::settings.PointModulo == 0).ToList();

	return outp;

}

void ClusterHelper::FindClusters(std::vector<Point*>* pointList){
	InitializeAlgorithm(pointList);

	algorithm->IterateUntilStable();

	if (algorithm->ClusterCount() > 0)
	{
		value = new ClusterData(FlattenIfRequired(MergeClustersIfRequired(algorithm->Clusters)));
		printf("\nCluster Data Generated");
	}

}

std::vector<Cluster*>* ClusterHelper::FlattenIfRequired(std::vector<Cluster*>* clusters){
	if (settings.MaximumClusterDepth)
	{
		std::vector<Cluster*>::iterator iter;
		Cluster* c1;
		for (iter = clusters->begin();iter<clusters->end();iter++) 
		{
			c1 = (Cluster*)*iter;
			c1->Flatten(settings.MaximumClusterDepth);
		}
	}
	return clusters;

}

void ClusterHelper::InitializeAlgorithm(std::vector<Point*>* pointList){
	algorithm->Initialize(pointList);

}
void ClusterHelper::AssignAllPoints(std::vector<Point*>* fullList){
	std::vector<Cluster*>::iterator iter;

	std::vector<Point*>::iterator iter1;
	Rectanglez* area;
	Cluster* c1;
	Point* p1;
	for (iter=value->Clusters->begin(); iter<value->Clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		
		for (iter1=fullList->begin();iter1<fullList->end();iter1++) 
		{
			p1 = (Point*)*iter1;
			
			if (c1->Area().Contains(p1))
			{
				c1->AllPoints.push_back(new Point(p1));
			}
		}
		
	}
	printf("\nAssigned all Points to their classes");

}

std::vector<Cluster*>* ClusterHelper::MergeClustersIfRequired(std::vector<Cluster*>* clusters){
	std::vector<Cluster*>::iterator iter;
	std::vector<Cluster*>* localClusters = new std::vector<Cluster*>;
	Cluster* c1;
	for (iter=clusters->begin();iter<clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		if (c1->Count()>settings.MinimalPointsForValidCluster) {
			c1->CalculateVolume();
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