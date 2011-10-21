#include "ConvexHull.h"

ConvexHull::ConvexHull(std::vector<Point*>* points){
	Points = points;

}
int ConvexHull::Count(){
	int a = 0;
	std::vector<Point*>::iterator iter;
	for (iter=Points->begin();iter<Points->end();iter++) {
		a++;
	}
	return a;

}