#ifndef CLUSTERS_H
#define CLUSTERS_H

#include "Point.h"
#include "volume.h"
#include <vector>
#include "rectangle.h"
#include "Range.h"
#include "pointfnc.h"
#include "ILocatable.h"
//point list
//find points within range function
class Cluster : public ILocatable
{
public:
	std::vector<Point*> points;
	Point center;
	volume vol;
	pointfunctions pntfnc;
	std::vector<Point*> AllPoints;

	Cluster(Point center1);
	Cluster(int x, int y, int z);
	Cluster(void* cl);
	Cluster(Point center, std::vector<Point*> points1);
	double Calc2DDistance(Point* point);
	Point* FindClosestPoint(std::vector<Point*>* points);
	void AddPoint(Point* point);
	void FindCenter();
	void CalculateVolume();
	void ClearPoints();
	void Flatten(int maxDepth);
	int Count();
	Rectanglez Area();
	double DistanceMetric(Cluster* c);
	Cluster* Merge(Cluster* c);
};



#endif 