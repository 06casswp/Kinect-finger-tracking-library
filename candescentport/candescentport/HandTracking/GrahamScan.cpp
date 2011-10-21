#include "GrahamScan.h"
#include "PointAngleComparer.h"

GrahamScan::GrahamScan(std::vector<Point*>* points1){

	points = points1;

}

ConvexHull* GrahamScan::FindHull(){
	PointAngleComparer2D *pntangcomp = new PointAngleComparer2D;
	std::vector<Point*>::iterator iter;
	int Count = 0;
	for (iter=points->begin();iter<points->end();iter++) {
		Count++;
	}
	
	if (Count <= 3)
	{
		return new ConvexHull(points);
	}

	std::vector<Point*>* pointsSortedByAngle = SortPointsByAngle();
	int index = 1;
	int Count1 = 0;
	for (iter=pointsSortedByAngle->begin(); iter<pointsSortedByAngle->end(); iter++) {
		Count1++;
	}
	std::vector<Point*>::iterator iter1;
	iter1 = pointsSortedByAngle->begin();
	iter1++;

	while (index + 1 < Count1)
	{

		float value = pntangcomp->Compare(pointsSortedByAngle->at(index - 1), pointsSortedByAngle->at(index + 1), pointsSortedByAngle->at(index));
		if (value < 0)
		{
			index++;
			iter1++;
		}
		else //Also removes points that are on a line when value == 0
		{
			pointsSortedByAngle->erase(iter1); //redo this whole function
			if (index > 1)
			{
				index--;
				iter1--;
			}
		}
	}

	pointsSortedByAngle->push_back(*pointsSortedByAngle->begin());
	return new ConvexHull(pointsSortedByAngle);


}

Point* GrahamScan::FindMinimalOrdinatePoint(){
	std::vector<Point*>::iterator iter;
	
	Point* minPoint = *points->begin();
	Point*p;
	for (iter=points->begin()+1;iter<points->end();iter++)
	{
		p = (Point*)*iter;
		minPoint = ReturnMinPoint(minPoint, p);
	}
	return minPoint;


}

Point* GrahamScan::ReturnMinPoint(Point* p1, Point* p2){
	if (p1->y < p2->y)
	{
		return p1;
	}
	else if (p1->y == p2->y)
	{
		if (p1->x < p2->x)
		{
			return p1;
		}
	}
	return p2;


}

std::vector<Point*>* GrahamScan::SortPointsByAngle(){
	Point* p0 = FindMinimalOrdinatePoint(); //move the minimum ordinate point to the start, run a comparer from the 2nd element to the end to sort those
	PointAngleComparer2D* comparer = new PointAngleComparer2D(p0);
	std::vector<Point*>* sortedPoints = new std::vector<Point*>;
	//copy points to the new points array
	std::vector<Point*>::iterator iter;
	sortedPoints->push_back(p0);
	Point* p1;
	int ret;
	for (iter = points->begin(); iter<points->end();iter++) {
		p1 = (Point*)*iter;
		if (!(p1==p0)) {
			sortedPoints->push_back(p1);
		}
	}
	Point* p2;
	//run through the list until u find something the comparer returns a value other than 0, then do the swap operation, then run through again and again until it reaches the end.
	bool sorting = true;
	while (sorting) {
		iter = sortedPoints->begin();
		iter++;
		for (iter;iter<sortedPoints->end()-1;iter++) {
			p1 = (Point*)*iter;
			iter++;
			p2 = (Point*)*iter;
			iter--;
			ret = comparer->Compare(p1,p2);
			if (ret==1){ //p1 greater than p2, swap them
				(Point*)*iter = p2;
				iter++;
				(Point*)*iter = p1;
				break;
			}
			if (iter==sortedPoints->end()-1) {
				sorting=false;
				break;
			}

		}
	}

	//sortedPoints.Remove(p0);
	//sortedPoints.Insert(0, p0);
	//sortedPoints.Sort(1, sortedPoints.Count - 1, comparer);

	return sortedPoints;



}