#include "LineThinner.h"
#include "../pointfnc.h"

LineThinner::LineThinner(float mindDistBetweenPointsz, bool checkBoundaryz){

	checkBoundary = checkBoundaryz;
	mindDistBetweenPoints = mindDistBetweenPointsz;
}

std::vector<Point*>* LineThinner::Filter(std::vector<Point*>* points){

	std::vector<Point*>* result = new std::vector<Point*>;
	int Count = 0;
	std::vector<Point*>::iterator iter;
	for (iter = points->begin();iter<points->end();iter++){
		Count++;
	}

	if (Count == 0)
	{
		return result;
	}
	Count = 0;
	Point* p2;
	Point* p1 = (Point*)*points->begin();
	Point* point = new Point(p1->x,p1->y,p1->z);
	result->push_back(point);
	Count++;
	
	
		
	
	//run through every second, then run through the rest
	for (iter=points->begin();iter<points->end(); iter++) {
		iter++;
		p2 = (Point*)*iter;

		if (!MergeIfDistanceIsTooSmall(p2, point))
		{
			point = new Point(p2->x,p2->y,p2->z);
			result->push_back(point);
			Count++;
		}
	}
	for (iter=points->begin()+1;iter<points->end(); iter++) {
		iter++;
		p2 = (Point*)*iter;

		if (!MergeIfDistanceIsTooSmall(p2, point))
		{
			point = new Point(p2->x,p2->y,p2->z);
			result->push_back(point);
			Count++;
		}
	}

	if (checkBoundary && Count > 1)
	{
		CheckFirstAndLastPoint(result);
	}

	return result;
}

bool LineThinner::MergeIfDistanceIsTooSmall(Point* sourcePoint, Point* destPoint){
	pointfunctions pntfnc;
	if (pntfnc.distance(sourcePoint, destPoint) < mindDistBetweenPoints)
	{
		Point p = pntfnc.Center(sourcePoint, destPoint);
		destPoint = new Point(p.x,p.y,p.z);
		return true;
	}
	return false;
}

void LineThinner::CheckFirstAndLastPoint(std::vector<Point*>* points)        {
	Point *a = (Point*)*points->end();
	Point *b = (Point*)*points->begin();

	if (MergeIfDistanceIsTooSmall(a, b))
	{
		points->erase(points->end());
	}
}