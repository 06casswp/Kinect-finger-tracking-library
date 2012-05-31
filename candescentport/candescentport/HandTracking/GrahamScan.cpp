#include "GrahamScan.h"
#include "pointAngleComparer.h"
#include <algorithm>
#include <math.h>
#include <deque>

bool myfunction (point* i, point* j) {return (i->angle<j->angle); }

void GrahamScan::set(point** points1, int count){

	points = points1;
	pointscnt = count;
}

ConvexHull* GrahamScan::FindHull(){
	
	
	ConvexHull* hull = new ConvexHull;
	extern int hulls;
	hulls++;
	if (pointscnt <= 3)
	{
		hull->pointspnt = points;
		hull->Count = pointscnt;
		return hull;
	}
	
	SortpointsByAngle();
	
   const std::size_t HEAD     = 0;
   const std::size_t PRE_HEAD = 1;

   std::deque<point*> pnt_queue;

   pnt_queue.push_front(points[0]);
   pnt_queue.push_front(points[1]);

   unsigned int i = 2;
   int    counter_clock_wise = +1;
	int    clock_wise         = -1;
   while(i < pointscnt)
   {
      if (pnt_queue.size() > 1)
      {
         if (orientation(pnt_queue[PRE_HEAD],pnt_queue[HEAD],points[i]) == counter_clock_wise)
            pnt_queue.push_front(points[i++]);
         else
          pnt_queue.pop_front();
      }
      else
         pnt_queue.push_front(points[i++]);
   }
   hull->Count = 0;
   std::deque<point*>::iterator it;
   for(it = pnt_queue.begin(); it != pnt_queue.end(); it++)
   {

	   hull->points[hull->Count] = (point*)*it;
	   hull->Count++;
   }
   hull->pointspnt = &hull->points[0];
	return hull;


}

point* GrahamScan::FindMinimalOrdinatepoint(){
	
	
	point* minpoint = points[0];
	
	int i=0;
	for (i=1;i<pointscnt;i++)
	{
		
		minpoint = ReturnMinpoint(minpoint, points[i]);
	}
	return minpoint;


}

int GrahamScan::orientation(point* p1, point* p2, point* p3)
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

point* GrahamScan::ReturnMinpoint(point* p1, point* p2){
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

void GrahamScan::SortpointsByAngle(){
	point* p0 = FindMinimalOrdinatepoint(); //move the minimum ordinate point to the start, run a comparer from the 2nd element to the end to sort those
	comparer.set(p0);
	//copy points to the new points array
	int i = 0;
	for (i=0; i<pointscnt;i++) {
		if (points[i] == p0) {
			points[i] = points[0];
			points[0] = p0;
			break;
		}
	}

	point* p1;
	int ret;
	for (i = 0; i<pointscnt;i++) {
		p1 = points[i];
		points[i]->angle = cartesian_angle(points[i]->x - p0->x, points[i]->y - p0->y);
	}
	



	//run through the list until u find something the comparer returns a value other than 0, then do the swap operation, then run through again and again until it reaches the end.
	
	//std::sort(++points->begin(),points->end(),pointAngleComparer2Da(p0));
	point* pointtemp;
	comparer1.anchor = p0;
	i = 0;
	int max = 0;
	printf("\n");

	std::vector<point*> myvector (points, points+pointscnt);
	std::vector<point*>::iterator it;

	std::sort(myvector.begin(),myvector.end(),myfunction);


	for (it = myvector.begin();it<myvector.end();it++) {
		points[i] = (point*)*it;
		i++;
	}



}