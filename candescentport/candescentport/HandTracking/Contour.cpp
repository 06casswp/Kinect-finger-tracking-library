#include "Contour.h"

Contour::Contour(){
	points = new std::vector<Point*>;
}

Contour::Contour(std::vector<Point*>* points1){
	points = points1;
}


int Contour::Count(){
	return points->size();
}

Contour* Contour::Empty(){
	return new Contour;
}