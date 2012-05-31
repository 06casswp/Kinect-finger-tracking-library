#include "point.h"
#include <math.h>


	void pointman::set (short x, short y, short z, point* dest){
		dest->x = x;
		dest->y = y;
		dest->z = z;
		dest->angle = 0.0f;
	}
	void pointman::set (point* dest, point* src){
		dest->x = src->x;
		dest->y = src->y;
		dest->z = src->z;
		dest->angle=src->angle;
	}
	void pointman::reset (point* dest){
		dest->x = 0;
		dest->y = 0;
		dest->z = 0; 
		dest->angle = 0.0f;
	}
	bool pointman::isZero(point* p){
		return ((p->x==0)&&(p->y==0)&&(p->z==0));
	}
	bool pointman::Equals(point* p1, point* p2){
		return ((p1->x==p2->x)&&(p1->y==p2->y)&&(p1->z==p2->z));
	}


	double pointman::distance(point *p1, point *p2){
		return sqrt(pow((float)p1->x - p2->x, 2) + pow((float)p1->y - p2->y, 2) + pow((float)p1->z - p2->z, 2));



	}
	double pointman::distance(float x1, float y1, float x2, float y2){
		return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));


	}
	void pointman::Center(point *p1, point *p2, point *dest){
		short x = (p1->x + p2->x) / 2;
		short y = (p1->y + p2->y) / 2;
		short z = (p1->z + p2->z) / 2;
		set(x, y, z,dest);
		
		
	}

