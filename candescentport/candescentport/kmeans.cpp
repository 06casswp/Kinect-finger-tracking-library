#include "kmeans.h"
#include <time.h>


#include <windows.h>






void KMeans::IterateUntilStable()
{
	//clear clusterdat*s
	int index = 0;
	int *counts = 0;//change this for cluster count change
	if (counts) {
		free(counts);
	}
	counts = (int*)malloc(sizeof(int)*setclustcount);
	//clear the clusterdats
	for (index = 0; index<setclustcount; index++) { //and this
		cfnc.clearall(clusterdatarr[index]);
	}

	do
	{
		count(counts);
		IterateOnce();
	} while (DetectCountChange(counts));
	
	clusterdatcount = 0;
	for (index = 0; index<setclustcount;index++) {
		if (counts[index]>0) {
			cfnc.CalculateVolume(clusterdatarr[index]);
			clusterdatarr[index]->pointspnt = &clusterdatarr[index]->points[0];
			clusterdatcount++;
		}
	}
	
	free(counts);

}

void KMeans::IterateOnce()
{
	Clearpoints();
	DistributepointsToclusterdats();
	RecalculateCenters();
}

void KMeans::count(int* counts) {
	int index = 0;
	int which = 0;
	memset(counts,0, setclustcount*sizeof(int));
	for (index = 0; index<setclustcount; index++) {
		for (which = 0; which<640*480; which++) {
			if (!(clusterdatarr[index]->points[which]==0)) { //if the pointer representing the point is null then dont add
				counts[index]++;
			}
		}
	}
}


void KMeans::Clearpoints() {
	int index = 0;
	for (index=0;index<setclustcount;index++) {
		cfnc.Clearpoints(clusterdatarr[index]);
	}

}

void KMeans::DistributepointsToclusterdats()
{
	int index = 0;
	//int reduced = 0;
	for (index=0;index<reducedcount;index++) {
	//	if (!(reducedpoints[index]==0)) {
			//reduced++;
			AddToMinimalDistanceclusterdat(reducedpoints[index]);
		//}
	}
	//printf("\n point count: %d",reduced);

}


bool KMeans::DetectCountChange(int* counts) //match up a vector of the counts with the counts of clusterdats in the clusterdat vector
{
	int index = 0;
	int which = 0;

	int *newcounts = 0;
	if (newcounts) {
		free(newcounts);
	}
	newcounts = (int*)malloc(sizeof(int)*setclustcount);
	
	count(newcounts);
	/*
	printf("\n");
	for (index = 0; index<setclustcount; index++) {
		printf("%d ",newcounts[index]);
	}
	printf(" - ");
	for (index = 0; index<setclustcount; index++) {
		printf("%d ",counts[index]);
	}
	*/
	for (index = 0; index<setclustcount; index++) {

		if (!(newcounts[index]==counts[index])) {
			return true;
		}
	}

	free(newcounts);

	return false;
}


void KMeans::RecalculateCenters() //this comes after the points are assigned
{
	
	clusterdat* c1;
	LARGE_INTEGER li;

	int index= 0;
	for (index=0;index<setclustcount;index++) { 
		if (clusterdatarr[index]->pointscnt==0) { //ensure that the first position for each is in a different area!
			QueryPerformanceCounter(&li) ;
			srand(li.QuadPart);
			unsigned short a = 639*index;
			unsigned short b = 479*index;
			unsigned short c = 0; 
			clusterdatarr[index]->center.x = a;
			clusterdatarr[index]->center.y = b;
			clusterdatarr[index]->center.z = 0;
		}
		else
		{
			cfnc.FindCenter(clusterdatarr[index]);
		}
		//printf("\n %d, %d, %d",clusterdatarr[index]->center.x,clusterdatarr[index]->center.z,clusterdatarr[index]->center.z);
	}
		
		
}

double KMeans::CalcDistance(clusterdat* c1, point* pnt)
{
	return cfnc.Calc2DDistance(c1,pnt);
}


void KMeans::AddToMinimalDistanceclusterdat(point* pnt)
{
	int clusterdatIndex = 0;

	double minDist = CalcDistance(clusterdatarr[0], pnt);
	clusterdat* closest = clusterdatarr[0];
	int index = 0;
	double dist = 0.0f;
	for (index=1;index<setclustcount;index++) { 
		dist = CalcDistance(clusterdatarr[index],pnt);
		if (dist < minDist)
		{
			closest = clusterdatarr[index];
			minDist = dist;
		}
	}
	cfnc.Addpoint(closest,pnt);
}
