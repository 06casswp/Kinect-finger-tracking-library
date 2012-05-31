#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "Range.h"
#include "clusters.h"
#include "size.h"



class KMeans
{
public:



	point** reducedpoints; //same as points
	int reducedcount;

	sizedat* size;

	rangedat* zrangedat;

	
	clusterfnc cfnc;

	clusterdat** clusterdatarr;
	int clusterdatcount;

	int setclustcount;

	void count(int* counts);

	void Initialize(point ** reduced);

	void IterateUntilStable();

	void IterateOnce();

	void Clearpoints();

	void DistributepointsToclusterdats();

	bool DetectCountChange(int* counts);
	void RecalculateCenters();


	double CalcDistance(clusterdat* c1, point* pnt);


	void AddToMinimalDistanceclusterdat(point* pnt);
};


#endif 