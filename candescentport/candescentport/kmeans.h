#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "Range.h"
#include "clusters.h"
#include "intsize.h"
#include "clusterfactory.h"


class KMeans
{
public:
	ClusterFactory* clusterFactory;

	//Random random = new Random(); //sys fnc for random numbers
	std::vector<Point*>* points;
	intsize* size;
	Range* zRange;
	std::vector<Cluster*>* Clusters;
	int ClusterCount();

	KMeans(int numberOfClusters, Range* zRange1, intsize* size1);


	void Initialize(std::vector<Point*>* points1);


	void IterateUntilStable();

	void IterateOnce();

	void ClearPoints();

	void DistributePointsToClusters();

	bool DetectCountChange(std::vector<int>* counts);

	void RecalculateCenters();

	double CalcDistance(Cluster* c1, Point* point);

	void AddToMinimalDistanceCluster(Point* point);
};


#endif 