

#include "pointAngleComparer.h"


void pointAngleComparer2D::set(point* zeropoint){
	p0 = zeropoint;
}


int pointAngleComparer2D::Compare(point* p1, point* p2){
	//if (p1->Equals((void*)&p2))
	//{
	//	return 0;
	//}
	float value = Compare(p0, p1, p2);
	if (value == 0)
	{
		return 0;
	}
	if (value < 0)
	{
		return 1; //p1 is more than p2
	}
	return -1; //(p1 is less than p2)
}

float pointAngleComparer2D::Compare(point* p0, point* p1, point* p2){

	return (p1->x - p0->x) * (p2->y - p0->y) - (p1->y - p0->y) * (p2->x - p0->x);
}