#include "HandData.h"

HandData::HandData(int id1, clusterdat *clusterdat1, ConvexHull *convexHull1, Contour *contour1, Palm *palm1, Fingerpoint** fingerpoints1){

	id = id1;
	clusterdata=clusterdat1;
	contour = contour1;
	convexHull = convexHull1;
	palm = palm1;
	Fingerpoints = fingerpoints1;
	FingerpointCount = 0;
}



point* HandData::Center(){
	return &clusterdata->center;


}

point* HandData::Location(){
	return &clusterdata->center;


}


bool HandData::HasPalm(){
	return (!palm==0);


}

point* HandData::Palmpoint(){
	if (palm) {
		return palm->location;
	}
	return 0;//new point(0,0,0);


}

double HandData::PalmDistance(){
	if (palm) {
	return palm->distanceToContour;
	}
	return 0;
}




bool HandData::HasContour(){
	return (!contour==0);


}

