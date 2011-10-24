#include "clusters.h"	



Cluster::Cluster(Point center1){          
	center = center1;
	//vol = 0;
}
Cluster::Cluster(int x, int y, int z){   
	center =  Point(x, y, z);
	//vol = 0;
}


Cluster::Cluster(Point center1, std::vector<Point*> points1){     
	center = center1;
	points = points1;
	//vol = 0;
}
double Cluster::Calc2DDistance(Point* point){  
	return sqrt(pow((float)point->x - center.x, 2) + pow((float)point->y - center.y, 2) + pow((float)point->z - center.z, 2));
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
	points.push_back(new Point(point));

}

void Cluster::FindCenter(){               
	//iterator
	if (points.empty() == 1)
	{
		return;
	}
	std::vector<Point*>::iterator iter;
	iter = points.begin();
	center = (Point*)*iter;
	iter++;
	int i = 1;
	for (iter; iter < points.end(); iter++)
	{
		Point p = *(Point*)*iter;
		center.x += p.x;
		center.y += p.y;
		center.z += p.z;
		i++;
	}

	center.x /= i;
	center.y /= i;
	center.z /= i;
}

void Cluster::CalculateVolume(){   
	if (points.empty() == 1)
	{
		return;
	}



	std::vector<int> valuesx;
	std::vector<int> valuesy;
	std::vector<int> valuesz;

	std::vector<Point*>::iterator iter;

	for (iter=points.begin();iter<points.end();iter++) {
		Point p = *(Point*)*iter;
		valuesx.push_back(p.x);
		valuesy.push_back(p.y);
		valuesz.push_back(p.z);
	}
	Range *rangeX = new Range(valuesx);
	Range *rangeY = new Range(valuesy);
	Range* rangeZ = new Range(valuesz);
	Point* loca = new Point(rangeX->Min, rangeY->Min, rangeZ->Min);
	//if (!vol) {
		vol.location = loca;
		//new volume(loca,rangeX.value(),rangeY.value(),rangeZ.value());
	//}
	//else
	//{

	//	vol->location = new Point(rangeX.Min, rangeY.Min, rangeZ.Min);

		vol.width = rangeX->value();
		vol.height = rangeY->value();
		vol.depth = rangeZ->value();
	//}
}

void Cluster::ClearPoints(){     
	points.clear();
}

void Cluster::Flatten(int maxDepth){    
	float maxZValue = vol.location->z + maxDepth;
	std::vector<Point*> newlist;
	std::vector<Point*>::iterator iter;
	Point *p;
	if (vol.depth > maxDepth)
	{
		for (iter=points.begin();iter<points.end();iter++) {
			//go through list, make new list, apply to old list
			p = (Point*)*iter;
			if (p->z<maxZValue) {
				newlist.push_back(new Point(p));
			}
		}
		

		points = newlist;
		FindCenter();
		CalculateVolume();
	}
}
int Cluster::Count(){  
	return points.size();
	/*int i =0;
	std::vector<Point*>::iterator iter;
	for (iter=points.begin();iter<points.end();iter++) {
		i++;
	}

	return i; 
	*/
}

Rectanglez Cluster::Area(){     
	return Rectanglez(vol.location->x, vol.location->y, vol.width, vol.height); 
}

double Cluster::DistanceMetric(Cluster* c1){
	Cluster* c2 = new Cluster(center, points);
	Point* p1 = FindClosestPoint(&c1->points);
	Point* p2 = c2->FindClosestPoint(&points);
	return pntfnc.distance(p1, p2);
}
Cluster* Cluster::Merge(Cluster* c){
	//form a new list of points which are common to both!
	std::vector<Point*>::iterator iter1;
	std::vector<Point*>::iterator iter2;
	Point *p1;
	Point *p2;
	std::vector<Point*>* pointout = new std::vector<Point*>;
	for (iter1=points.begin();iter1<points.end();iter1++) {
		p1 = (Point*)*iter1;
		for (iter2=c->points.begin();iter2<c->points.end();iter2++) {
			p2 = (Point*)*iter2;
			if ((p1->x==p2->x)&&(p1->y==p2->y)&&(p1->z==p2->z)) {
				Point* pntptr = new Point(p2);
				pointout->push_back(pntptr);
			}
		}
	}
	Cluster *mergedCluster = new Cluster(pntfnc.Center(&center, &c->center), *pointout);
	mergedCluster->CalculateVolume();
	mergedCluster->FindCenter();
	return mergedCluster;

}

Cluster::Cluster(void * cl) {
	Cluster* clust = (Cluster*)cl;
	std::vector<Point*>::iterator iter;
	for (iter=clust->points.begin();iter<clust->points.end();iter++) {
		points.push_back(new Point(*iter));
	}
	for (iter=clust->AllPoints.begin();iter<clust->AllPoints.end();iter++) {
		AllPoints.push_back(new Point(*iter));
	}
	center.x = clust->center.x;
	center.y = clust->center.y;
	center.z = clust->center.z;
	vol.depth = clust->vol.depth;
	vol.width = clust->vol.width;
	vol.height = clust->vol.height;
	vol.location->x = clust->vol.location->x;
	vol.location->y = clust->vol.location->y;
	vol.location->z = clust->vol.location->z;
	//Point center;
	//volume vol;

	}