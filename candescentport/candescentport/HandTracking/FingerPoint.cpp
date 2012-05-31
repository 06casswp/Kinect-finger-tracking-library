#include "Fingerpoint.h"

float Fingerpoint::X(){
	return location->x;
}
float Fingerpoint::Y() {
	return location->y;
}
float Fingerpoint::Z() {
	return location->z;
}

void Fingerpoint::set(point* locationz){
	location = locationz;
}