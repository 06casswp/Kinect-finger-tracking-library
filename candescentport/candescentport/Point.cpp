#include "Point.h"

Point::Point(float x, float y, float z){
	Point::x = x;
	Point::y = y;
	Point::z = z;
}
Point::Point(void* p) {
	Point* p1 = (Point*)p;
	x = p1->x;
	y = p1->y;
	z = p1->z;
}

void Point::adapt(float x, float y, float z){
	Point::x = x;
	Point::y = y;
	Point::z = z;
}
bool Point::isZero(){
	if ((Point::x == 0)&&(Point::y == 0)&&(Point::z == 0)) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Point::Equals(void* pnt)
{

	Point *point = ((Point*)pnt);
	return point->x == x && point->y == y && point->z == z;            
}