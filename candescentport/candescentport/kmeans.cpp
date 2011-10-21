#include "kmeans.h"
#include <time.h>

KMeans::KMeans(int numberOfClusters, Range* zRange1, intsize *size1)
{
	size = size1;
	zRange = zRange1;
	clusterFactory = new ClusterFactory();
	Clusters = clusterFactory->CreateClusters(numberOfClusters, size1);
}

void KMeans::Initialize(std::vector<Point*>* points1)
{
	points = points1;
}



void KMeans::IterateUntilStable()
{
	std::vector<int> counts;
	do
	{

		std::vector<Cluster*>::iterator iter1;


		Cluster* c1;

		for (iter1=Clusters->begin();iter1<Clusters->end();iter1++){
			c1 = (Cluster*)*iter1;
			counts.push_back(c1->Count());
		}
		IterateOnce();
	} while (DetectCountChange(counts));

	std::vector<Cluster*>::iterator iter;
	Cluster* c1;
	for (iter=Clusters->begin();iter<Clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		c1->CalculateVolume();
	}

}

void KMeans::IterateOnce()
{
	ClearPoints();
	DistributePointsToClusters();
	RecalculateCenters();
}

void KMeans::ClearPoints()
{
	std::vector<Cluster*>::iterator iter;
	Cluster* c1;
	for (iter=Clusters->begin();iter<Clusters->end();iter++) {
		c1 = (Cluster*)*iter;
		c1->ClearPoints();
	}
}

void KMeans::DistributePointsToClusters()
{
	std::vector<Point*>::iterator iter;
	Point* p;
	for (iter=points->begin();iter<points->end();iter++) {
		p = (Point*)*iter;
		AddToMinimalDistanceCluster(p);
	}
}

bool KMeans::DetectCountChange(std::vector<int> counts) //match up a vector of the counts with the counts of clusters in the cluster vector
{
	std::vector<Cluster*>::iterator iter1;
	std::vector<int>::iterator iter2;
	//form a new count vector and compare
	Cluster* c1;
	std::vector<int> newcount;
	for (iter1=Clusters->begin();iter1<Clusters->end();iter1++){
		c1 = (Cluster*)*iter1;
		newcount.push_back(c1->Count());
	}

	int number;
	int index = 0;
	for (iter2=counts.begin(); iter2 < counts.end(); iter2++)
	{
		number = (int)*iter2;
		if (!number==newcount.at(index)) {
			return false;
		}
	}
	return true;
}

void KMeans::RecalculateCenters()
{
	std::vector<Cluster*>::iterator iter;
	Cluster* c1;

	for (iter=Clusters->begin(); iter<Clusters->end();iter++) {
		c1 =(Cluster*)*iter;

		if (c1->Count() == 0) //If no points are assigned, the point is repositioned randomly
		{
			srand(time(NULL));
			float a = rand()%(size->Width - 1);
			float b = rand()%(size->Height - 1);
			float c = rand()%((int)zRange->Max-(int)zRange->Min)+(int)zRange->Min;

			c1->center= new Point(a, b, c);
		}
		else
		{
			c1->FindCenter();
		}
	}
}

double KMeans::CalcDistance(Cluster* c1, Point* point)
{
	return c1->Calc2DDistance(point);
}

void KMeans::AddToMinimalDistanceCluster(Point* point)
{
	int clusterIndex = 0;
	double minDist = CalcDistance(0, point);
	std::vector<Cluster*>::iterator iter;
	Cluster* c1;
	Cluster* closest;
	for (iter = Clusters->begin(); iter < Clusters->end(); iter++)
	{
		c1 = (Cluster*)*iter;
		double dist = CalcDistance(c1, point);
		if (dist < minDist)
		{
			closest = c1;
			minDist = dist;
		}
	}
	closest->AddPoint(point);
}

