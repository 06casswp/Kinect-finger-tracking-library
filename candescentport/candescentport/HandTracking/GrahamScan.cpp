#include "GrahamScan.h"
#include "PointAngleComparer.h"
#include <algorithm>
#include <math.h>
#include <deque>

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
	std::vector<Point*>* hull = new std::vector<Point*>;
   const std::size_t HEAD     = 0;
   const std::size_t PRE_HEAD = 1;

   std::deque<Point*> pnt_queue;

   pnt_queue.push_front(pointsSortedByAngle->at(0));
   pnt_queue.push_front(pointsSortedByAngle->at(1));

   unsigned int i = 2;
   int    counter_clock_wise = +1;
	int    clock_wise         = -1;
   while(i < pointsSortedByAngle->size())
   {
      if (pnt_queue.size() > 1)
      {
         if (orientation(pnt_queue[PRE_HEAD],pnt_queue[HEAD],pointsSortedByAngle->at(i)) == counter_clock_wise)
            pnt_queue.push_front(pointsSortedByAngle->at(i++));
         else
          pnt_queue.pop_front();
      }
      else
         pnt_queue.push_front(pointsSortedByAngle->at(i++));
   }

   for(std::deque<Point*>::iterator it = pnt_queue.begin(); it != pnt_queue.end(); it++)
   {
      hull->push_back(new Point((*it)->x, (*it)->y,(*it)->z));
   }
	return new ConvexHull(hull);


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

int GrahamScan::orientation(Point* p1, Point* p2, Point* p3)
{
   return orientation(p1->x,p1->y,p2->x,p2->y,p3->x,p3->y);
}

int GrahamScan::orientation(int x1, int y1, int x2,int y2,int px, int py){
	   double orin = (x2 - x1) * (py - y1) - (px - x1) * (y2 - y1);

   if (is_equal(orin,0.0))
     return 0;              /* Orientaion is neutral aka collinear  */
   else if (orin < 0.0)
     return -1;             /* Orientaion is to the right-hand side */
   else
     return +1;             /* Orientaion is to the left-hand side  */

}
bool GrahamScan::is_equal(double v1,double v2){

	   double diff = v1 - v2;
   return  (-1.0e-12 <= diff) && (diff <= 1.0e-12);

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

double GrahamScan::cartesian_angle(int x, int y){
double _180DivPI  = 57.295779513082320876798154814105000;


  if      ((x >  0.0) && (y >  0.0)) return (atan((double) y / x) * _180DivPI);
  else if ((x <  0.0) && (y >  0.0)) return (atan((double)-x / y) * _180DivPI) +  90.0;
  else if ((x <  0.0) && (y <  0.0)) return (atan((double) y / x) * _180DivPI) + 180.0;
  else if ((x >  0.0) && (y <  0.0)) return (atan((double)-x / y) * _180DivPI) + 270.0;
  else if ((x == 0.0) && (y >  0.0)) return  90.0;
  else if ((x <  0.0) && (y == 0.0)) return 180.0;
  else if ((x == 0.0) && (y <  0.0)) return 270.0;
  else
    return 0.0;
}

std::vector<Point*>* GrahamScan::SortPointsByAngle(){
	Point* p0 = FindMinimalOrdinatePoint(); //move the minimum ordinate point to the start, run a comparer from the 2nd element to the end to sort those
	PointAngleComparer2D* comparer = new PointAngleComparer2D(p0);
	//copy points to the new points array

	std::vector<Point*>::iterator iter;
	for (iter = points->begin(); iter<points->end();iter++) {
		if (p0==(Point*)*iter) {
			points->erase(iter);
			break;
		}
	}
	points->insert(points->begin(),p0);
	Point* p1;
	int ret;
	for (iter = points->begin(); iter<points->end();iter++) {
		p1 = (Point*)*iter;
		p1->angle = cartesian_angle(p1->x - p0->x, p1->y - p0->y);
	}
	
	//run through the list until u find something the comparer returns a value other than 0, then do the swap operation, then run through again and again until it reaches the end.
	
	
	std::sort(++points->begin(),points->end(),PointAngleComparer2Da(p0));
	
	


	//sortedPoints.Remove(p0);
	//sortedPoints.Insert(0, p0);
	//sortedPoints.Sort(1, sortedPoints.Count - 1, comparer);

	return points;



}