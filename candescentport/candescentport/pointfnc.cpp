#include "pointfnc.h"	
#include <math.h>
double pointfunctions::distance(Point *p1, Point *p2){
	return sqrt(pow((float)p1->x - p2->x, 2) + pow((float)p1->y - p2->y, 2) + pow((float)p1->z - p2->z, 2));
}
double pointfunctions::distance(float x1, float y1, float x2, float y2){
	return sqrt(pow((float)x1 - x2, 2) + pow((float)y1 - y2, 2));

}
Point pointfunctions::Center(Point *p1, Point *p2){
	return Point((p1->x + p2->x) / 2, (p1->y + p2->y) / 2, (p1->z + p2->z) / 2);


}