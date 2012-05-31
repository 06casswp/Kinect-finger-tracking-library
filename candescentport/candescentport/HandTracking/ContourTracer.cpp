#include "ContourTracer.h"

#include <math.h>



void ContourTracer::GetContourpoints(depthmapdat* contourMap1, Contour* contour){
	contourMap = contourMap1;
	cont = contour;
	cont->contourpntcnt = 0;
	memset(cont->contourpoints,0,640*480*sizeof(point*));
	Process();
	//normally returns contourpoints!

}

int ContourTracer::Width(){

	return contourMap->Width;
}

int ContourTracer::Height(){
	return contourMap->Height;

}

int ContourTracer::ResultCount(){

	return cont->contourpntcnt;

}

point* ContourTracer::FindFirstpoint(){
	int width = Width();
	int height = Height();
	cont->newpointcnt = 0;
	DepthMapFnc dfnc;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (dfnc.IsSet(contourMap,x, y))
			{
				pntfnc.set(x,y,0, &cont->newpoints[0]);
				cont->newpointcnt++;
				return &cont->newpoints[0];
			}
		}
	}
	return NULL;

}







point* ContourTracer::GetNextpoint(point* currentPoint, point* directionPoint){
	DepthMapFnc dfnc;
	pntrot.set();
	int diffX = directionPoint->x - currentPoint->x;
    int diffY = directionPoint->y - currentPoint->y;
    int startIndex = GetStartIndex(diffX, diffY);

            for (int index = startIndex; index < startIndex + 8; index++)
            {


                point* rotationPoint = pntrot.points[index%8];
                int x = (int)(currentPoint->x + rotationPoint->x);
                int y = (int)(currentPoint->y + rotationPoint->y);
                if (dfnc.IsSet(contourMap,x, y))
                {
					pntfnc.set(x, y, dfnc.IsSet(contourMap,x, y),&cont->newpoints[cont->newpointcnt]);
					cont->newpointcnt++;
					return &cont->newpoints[cont->newpointcnt-1];
                    
                }
            }
            return 0;



}



void ContourTracer::Process(){
	        point* firstPoint = FindFirstpoint();
			point firstdirpnt;
			firstdirpnt.x = firstPoint->x;
			firstdirpnt.y = firstPoint->y-1;
			firstdirpnt.z = firstPoint->z;
			point* directionPoint = &firstdirpnt;
            point* currentPoint = firstPoint;

            cont->contourpoints[0] = currentPoint;
			cont->contourpntcnt = 1;

            point* nextPoint;
            do
            {
                nextPoint = GetNextpoint(currentPoint, directionPoint);
                if (nextPoint)
                {
                    directionPoint = currentPoint;

					cont->contourpoints[cont->contourpntcnt] = nextPoint;
					cont->contourpntcnt++;
                    currentPoint = nextPoint;
                }
            } while (nextPoint && !((firstPoint->x==nextPoint->x)&&(firstPoint->y==nextPoint->y)));
			

            //this.contourPoints.Add(firstPoint);

			/*

	FindFirstpoint();
	point* currentpoint = &cont->newpoints[0];//is an actual copy of points
	cont->contourpoints[0] = currentpoint;
	cont->contourpntcnt = 1;
	int retraceCount = 0;
	
	//TODO: Find better stop condition
	
	while (retraceCount < maximumRetraceSteps && ResultCount() <= 1500 && !(ResultCount() > 10 && pntfnc.distance(currentpoint, &cont->newpoints[0]) < 2))
	{
		point* nextpoint = GetNextpoint(currentpoint);
		if (nextpoint != NULL)
		{
			retraceCount = 0;
			cont->contourpoints[cont->contourpntcnt] = nextpoint;
			cont->contourpntcnt++;
			currentpoint = nextpoint;
		}
		else
		{
			currentpoint = cont->contourpoints[std::max(cont->contourpntcnt-retraceCount-1,0)];
			retraceCount++;
		}
	}
	*/
	printf("resultcount: %d", ResultCount());
	

}




void pointRotation::set(){

	points[0] = &p1;
	points[1] = &p2;
	points[2] = &p3;
	points[3] = &p4;
	points[4] = &p5;
	points[5] = &p6;
	points[6] = &p7;
	points[7] = &p8;


	pntfnc.set(1, 0, 0,&p1);
	pntfnc.set(1, 1, 0,&p2);
	pntfnc.set(0, 1, 0,&p3);
	pntfnc.set(-1, 1, 0,&p4);
	pntfnc.set(-1, 0, 0,&p5);
	pntfnc.set(-1, -1, 0,&p6);
	pntfnc.set(0, -1, 0,&p7);
	pntfnc.set(1, -1, 0,&p8);


}

        int ContourTracer::GetStartIndex(float diffX, float diffY)
        {
            if (diffY == -1)
            {
                if (diffX == -1)
                {
                    return 6;
                }
                if (diffX == 0)
                {
                    return 7;
                }
                if (diffX == 1)
                {
                    return 0;
                }
            }
            if (diffY == 0)
            {
                if (diffX == -1)
                {
                    return 5;
                }
                if (diffX == 1)
                {
                    return 1;
                }
            }
            if (diffY == 1)
            {
                if (diffX == -1)
                {
                    return 4;
                }
                if (diffX == 0)
                {
                    return 3;
                }
                if (diffX == 1)
                {
                    return 2;
                }
            }
            return 0;
        }
    