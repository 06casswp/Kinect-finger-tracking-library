#include "clusters.h"	



Cluster::Cluster(Point* center1){          
	center = center1;
	points = new std::vector<Point*>;
}
Cluster::Cluster(int x, int y, int z){   
	center =  new Point(x, y, z);
}


Cluster::Cluster(Point* center1, std::vector<Point*>* points1){     
	center = center1;
	points = points1;
}
double Cluster::Calc2DDistance(Point* point){  
	return sqrt(pow(point->x - center->x, 2) + pow(point->y - center->y, 2) + pow(point->z - center->z, 2));
}

Point* Cluster::FindClosestPoint(std::vector<Point*>* points){
	std::vector<Point*>::iterator iter;
	double dist;
	Point* closest;
	iter=points->begin();
	Point *p = (Point*)*iter;
	double minDist = Calc2DDistance(p);
	closest = p;
	for (iter=points->begin(); iter<points->end();iter++) {
		p = (Point*)*iter;


		dist = Calc2DDistance(p);
		if (dist < minDist)
		{
			closest = p;
			minDist = dist;
		}
	}
	return p;
}

void Cluster::AddPoint(Point* point){
	points->push_back(point);

}

void Cluster::FindCenter(){               
	//iterator
	if (points->empty() == 1)
	{
		return;
	}
	std::vector<Point*>::iterator iter;
	iter = points->begin();
	center = (Point*)*iter;
	iter++;
	int i = 1;
	for (iter; iter < points->end(); iter++)
	{
		Point p = *(Point*)*iter;
		center->x += p.x;
		center->y += p.y;
		center->z += p.z;
		i++;
	}

	center->x /= i;
	center->y /= i;
	center->z /= i;
}

void Cluster::CalculateVolume(){   
	if (points->empty() == 1)
	{
		return;
	}



	std::vector<float> valuesx;
	std::vector<float> valuesy;
	std::vector<float> valuesz;

	std::vector<Point*>::iterator iter;

	for (iter=points->begin();iter<points->end();iter++) {
		Point p = *(Point*)*iter;
		valuesx.push_back(p.x);
		valuesy.push_back(p.y);
		valuesz.push_back(p.z);
	}
	Range rangeX = Range(valuesx);
	Range rangeY = Range(valuesy);
	Range rangeZ = Range(valuesz);

	vol->location->adapt(rangeX.Min, rangeY.Min, rangeZ.Min);

	vol->width = rangeX.value();
	vol->height = rangeY.value();
	vol->depth = rangeZ.value();
}

void Cluster::ClearPoints(){     
	points->clear();
}

void Cluster::Flatten(int maxDepth){    
	float maxZValue = vol->location->z + maxDepth;
	std::vector<Point*> newlist;
	std::vector<Point*>::iterator iter;
	if (vol->depth > maxDepth)
	{
		for (iter=points->begin();iter<points->end();iter++) {
			//go through list, make new list, apply to old list
			Point p = *(Point*)*iter;
			if (p.z<maxZValue) {
				newlist.push_back(&p);
			}
		}
		points->empty();
		delete points;
		points = &newlist;
		FindCenter();
		CalculateVolume();
	}
}
int Cluster::Count(){  
	int i =0;
	std::vector<Point*>::iterator iter;
	for (iter=points->begin();iter<points->end();iter++) {
		i++;
	}

	return i; 
}

Rectanglez Cluster::Area(){     
	return Rectanglez(vol->location->x, vol->location->y, vol->width, vol->height); 
}

double Cluster::DistanceMetric(Cluster* c1){
	Cluster* c2 = new Cluster(center, points);
	Point* p1 = FindClosestPoint(c1->points);
	Point* p2 = c2->FindClosestPoint(points);
	return pntfnc.distance(p1, p2);
}
Cluster* Cluster::Merge(Cluster* c){
	//form a new list of points which are common to both!
	std::vector<Point*>::iterator iter1;
	std::vector<Point*>::iterator iter2;
	Point *p1;
	Point *p2;
	std::vector<Point*>* pointout;
	for (iter1==points->begin();iter1<points->end();iter1++) {
		p1 = (Point*)*iter1;
		for (iter2==c->points->begin();iter2<c->points->end();iter2++) {
			p2 = (Point*)*iter2;
			if ((p1->x==p2->x)&&(p1->y==p2->y)&&(p1->z==p2->z)) {
				Point* pntptr = new Point(p2);
				pointout->push_back(pntptr);
			}
		}
	}
	Cluster *mergedCluster = new Cluster(&pntfnc.Center(center, c->center), pointout);
	mergedCluster->CalculateVolume();
	mergedCluster->FindCenter();
	return mergedCluster;

}