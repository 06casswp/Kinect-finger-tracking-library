#ifndef PNTANGCOMP_H
#define PNTANGCOMP_H

#include "..\point.h"


class pointAngleComparer2D //removed c# comparer interface
{
public:
	point* p0;

	void set(point* zeropoint);
	

	int Compare(point* p1, point* p2);

	float Compare(point* p0, point* p1, point* p2);
};

class pointAngleComparer2Da //removed c# comparer interface
{
public:
	
	pointman pntfnc;
	
    

   bool compare(point* p1,point* p2)
   {
      
	   if (p1->angle < p2->angle)      return true;
      else if (p1->angle > p2->angle) return false;
      else if (p1==p2)     return false;
      else if (pntfnc.distance(anchor->x, anchor->y, p1->x, p1->y) < pntfnc.distance(anchor->x, anchor->y, p2->x, p2->y))
         return false;
      else
	  
         return false;
   }


   point* anchor;

};


#endif 