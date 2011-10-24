#ifndef PNTANGCOMP_H
#define PNTANGCOMP_H

#include "..\Point.h"
#include "../pointfnc.h"

class PointAngleComparer2D //removed c# comparer interface
{
public:
	Point* p0;

	PointAngleComparer2D(Point* zeroPoint);
	PointAngleComparer2D();

	int Compare(Point* p1, Point* p2);

	float Compare(Point* p0, Point* p1, Point* p2);
};

class PointAngleComparer2Da //removed c# comparer interface
{
public:
	
	pointfunctions pntfnc;
	
    PointAngleComparer2Da(Point* _anchor):anchor(_anchor){};

   bool operator()(Point* p1,Point* p2)
   {
      if (p1->angle < p2->angle)      return true;
      else if (p1->angle > p2->angle) return false;
      else if (p1->Equals((void*)p2))     return false;
      else if (pntfnc.distance(anchor->x, anchor->y, p1->x, p1->y) < pntfnc.distance(anchor->x, anchor->y, p2->x, p2->y))
         return true;
      else
         return false;
   }


   Point* anchor;

};


#endif 