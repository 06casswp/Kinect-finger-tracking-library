#include "Palm.h"

Palm::Palm(Point* locationz, double distanceToContourz){

	location->adapt(locationz->x,locationz->y,locationz->z);
	distanceToContour = distanceToContourz;

}
