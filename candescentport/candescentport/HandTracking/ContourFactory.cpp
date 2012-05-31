#include "ContourFactory.h"




Contour* ContourFactory::CreateContour(depthmapdat* map, float left, float top){
	Contour* cont = new Contour;
	extern int contours;
	contours++;

	DepthMapFnc dfnc;
	if (dfnc.FillRate(map) < 0.01) 
	{
		return cont;
	}
	tracer.GetContourpoints(map,cont);
	Translate(cont, (int)left, (int)top);
	thinner.Filter(cont); 

	return cont;



}

	void ContourFactory::Translate(Contour* cont, int deltaX, int deltaY){
	int i = 0;
	for (i=0;i<cont->newpointcnt;i++) {
		cont->newpoints[i].x = cont->newpoints[i].x + deltaX;
		cont->newpoints[i].y = cont->newpoints[i].y + deltaY;
	}



}