#include "Palm.h"

Palm::Palm(Point* locationz, double distanceToContourz){

	location= new Point(locationz->x,locationz->y,locationz->z);
	distanceToContour = distanceToContourz;

}
