#ifndef CLUSTERS_H
#define CLUSTERS_H

#include "point.h"
#include "volume.h"
#include <vector>
#include "rectangle.h"
#include "Range.h"


struct clusterdat {
	

	point *points[640*480]; //holds the kmeans reduced lot
	point **pointspnt;
	int pointscnt;

	point center;

	volumedat vol;
	volumefnc volfnc;
	pointman pntfnc;


	point *Allpoints[640*480]; //validated, initial set of points after kmeans algorithm run
	point **allpointpnt;
	int allpointscnt;




};


class clusterfnc 
{
public:

	void set(clusterdat* dest, point* pnt);
	void set(clusterdat* dest, clusterdat* src);
	void set(clusterdat* dest, unsigned short x, unsigned short y, unsigned short z);
	void set(clusterdat* dest, point center, point** pnts);

	double Calc2DDistance(clusterdat* c1, point* pnt);
	point* FindClosestpoint(clusterdat* c1, point** pnts,int counts);
	void Addpoint(clusterdat* c1, point* pnt);
	void FindCenter(clusterdat* c1);
	void CalculateVolume(clusterdat* c1);
	void clearall(clusterdat* c1);
	void Clearpoints(clusterdat* c1);
	void Flatten(clusterdat* c1, int maxDepth);
	int Count(clusterdat* c1);
	void Area(rectdata* dest, clusterdat* src);
	double DistanceMetric(clusterdat* c1, clusterdat* c2);
	void Merge(clusterdat* c1, clusterdat* c2);
};

//point list
//find points within range function



#endif 