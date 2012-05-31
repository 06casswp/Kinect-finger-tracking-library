#include "LineThinner.h"

void LineThinner::set(float mindDistBetweenpoints1, bool check) {
	mindDistBetweenpoints = mindDistBetweenpoints1;
	checkBoundary = check;
}



void LineThinner::Filter(Contour* cont){
	size = 0;
	if (cont->newpointcnt == 0)
	{
		return;
	}


	newstore[0] = &cont->newpoints[0];
	size++;
	int i = 0;

	point* pnt;
	pnt = newstore[0];


	for (i = 0;i<cont->newpointcnt;i++) {
		i++;
		if (!DistanceIsTooSmall(&cont->newpoints[i], pnt))
		{
			pnt = &cont->newpoints[i];
			newstore[size] = pnt;
			size++;
		}
	}

	for (i = 1;i<cont->newpointcnt;i++) {
		
		if (!DistanceIsTooSmall(&cont->newpoints[i], pnt))
		{
			pnt = &cont->newpoints[i];
			newstore[size] = pnt;
			size++;
			
		}
		i++;
	}



	if (checkBoundary && size > 1)
	{
		CheckFirstAndLastpoint(cont);
	}

	memcpy(&cont->contourpoints,&newstore, 640*480*sizeof(point*));
	cont->contourpntcnt = size;
	
	return;
}


void LineThinner::Filter1(ConvexHull* conv){
	size = 0;
	if (conv->Count == 0)
	{
		return;
	}


	newstore[0] = conv->points[0];
	size++;
	int i = 0;

	point* pnt;
	pnt = newstore[0];


	for (i = 1;i<conv->Count-1;i++) {
		
		if (conv->points[i]) {
			if (!DistanceIsTooSmall(conv->points[i], pnt))
			{
				pnt = conv->points[i];
				newstore[size] = pnt;
				size++;
			}
		}
	}





	if (checkBoundary && size > 1)
	{
		CheckFirstAndLastpoint1(conv);
	}

	memcpy(&conv->points,&newstore, 640*480*sizeof(point*));
	conv->Count = size;
	
	return;
}


bool LineThinner::DistanceIsTooSmall(point* sourcepoint, point* destpoint){
	pointman pntfnc;
	return pntfnc.distance(sourcepoint, destpoint) < mindDistBetweenpoints;
}

void LineThinner::CheckFirstAndLastpoint(Contour* cont)        {

	if (DistanceIsTooSmall(newstore[0], newstore[size-1]))
	{
		cont->newpointcnt--;
	}
}

void LineThinner::CheckFirstAndLastpoint1(ConvexHull* conv)        {
	if (DistanceIsTooSmall(newstore[0], newstore[size-1]))
	{
		conv->Count--;
	}
}