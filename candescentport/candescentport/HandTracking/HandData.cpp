#include "HandData.h"

HandData::HandData(int id1, Cluster *cluster1, ConvexHull *convexHull1, Contour *contour1, Palm *palm1, std::vector<FingerPoint*>* fingerPoints1){

	id = id1;
	cluster = cluster1;
	contour = contour1;
	convexHull = convexHull1;
	palm = palm1;
	fingerPoints = fingerPoints1;
}



Point* HandData::Center(){
	return cluster->center;


}

Point* HandData::Location(){
	return cluster->center;


}


bool HandData::HasPalm(){
	return (!palm==0);


}

Point* HandData::PalmPoint(){
	if (palm) {
		return palm->location;
	}
	return 0;//new Point(0,0,0);


}

double HandData::PalmDistance(){
	if (palm) {
	return palm->distanceToContour;
	}
	return 0;
}


int HandData::FingerPointCount(){
	std::vector<FingerPoint*>::iterator iter;
	int a = 0;
	for (iter=fingerPoints->begin(); iter<fingerPoints->end();iter++) {
		a++;


	}
	return a;


}

bool HandData::HasContour(){
	return (!contour==0);


}

bool HandData::HasFingerPoints(){
	return (FingerPointCount()>0);


}