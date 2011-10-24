#include "kmeans.h"
#include <time.h>

KMeans::KMeans(int numberOfClusters, Range* zRange1, intsize* size1)
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
	Clusters->at(0)->AllPoints.clear();
	Clusters->at(0)->points.clear();
	if (Clusters->size()>1) {
		Clusters->at(1)->AllPoints.clear();
		Clusters->at(1)->points.clear();
	}
	std::vector<int>* counts = new std::vector<int>;
	do
	{

		std::vector<Cluster*>::iterator iter1;
		counts->clear();

		Cluster* c1;

		for (iter1=Clusters->begin();iter1<Clusters->end();iter1++){
			c1 = (Cluster*)*iter1;
			counts->push_back(c1->Count());
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
		AddToMinimalDistanceCluster(new Point(p));
	}
}

int KMeans::ClusterCount(){
	return Clusters->size();
}

bool KMeans::DetectCountChange(std::vector<int>* counts) //match up a vector of the counts with the counts of clusters in the cluster vector
{
	std::vector<Cluster*>::iterator iter1;
	std::vector<int>::iterator iter2;
	//form a new count vector and compare
	Cluster* c1;
	std::vector<int>* newcount = new std::vector<int>;

	for (iter1=Clusters->begin();iter1<Clusters->end();iter1++){
		c1 = (Cluster*)*iter1;
		newcount->push_back(c1->Count());
	}

	int number;

	int index = 0;
	for (iter2=counts->begin(); iter2 < counts->end(); iter2++)
	{
		
		number = (int)*iter2;
		if (!number==newcount->at(index)) {
			return true;
		}
		index++;
	}
	return false;
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
			int a = rand()%(size->Width - 1);
			int b = rand()%(size->Height - 1);
			int c = rand()%(zRange->Max-zRange->Min)+zRange->Min;

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
	double minDist = CalcDistance(*Clusters->begin(), point);
	std::vector<Cluster*>::iterator iter;
	Cluster* c1;
	Cluster* closest = *Clusters->begin();
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

