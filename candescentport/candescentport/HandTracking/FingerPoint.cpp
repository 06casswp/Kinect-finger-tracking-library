#include "FingerPoint.h"

float FingerPoint::X(){
	return location->x;
}
float FingerPoint::Y() {
	return location->y;
}
float FingerPoint::Z() {
	return location->z;
}

FingerPoint::FingerPoint(Point* locationz){
	location = locationz;
}