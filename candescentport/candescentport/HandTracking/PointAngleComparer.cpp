

#include "PointAngleComparer.h"


PointAngleComparer2D::PointAngleComparer2D(Point* zeroPoint){
	p0 = new Point(zeroPoint->x,zeroPoint->y,zeroPoint->z);
}
PointAngleComparer2D::PointAngleComparer2D(){
	p0 = new Point(0,0,0);
}

int PointAngleComparer2D::Compare(Point* p1, Point* p2){
	if (p1->Equals((void*)&p2))
	{
		return 0;
	}
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

float PointAngleComparer2D::Compare(Point* p0, Point* p1, Point* p2){

	return (p1->x - p0->x) * (p2->y - p0->y) - (p1->y - p0->y) * (p2->x - p0->x);
}