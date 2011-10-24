#include "Point.h"

Point::Point(int x1, int y1, int z1){
	x = x1;
	y = y1;
	z = z1;
}
Point::Point(void* p) {
	Point* p1 = (Point*)p;
	x = p1->x;
	y = p1->y;
	z = p1->z;
}
/*
void Point::adapt(float x1, float y1, float z1){
	x = x1;
	y = y1;
	z = z1;
}
*/
bool Point::isZero(){
	if ((x == 0)&&(y == 0)&&(z == 0)) {
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