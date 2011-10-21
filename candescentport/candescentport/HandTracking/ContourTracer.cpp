#include "ContourTracer.h"
#include "../pointfnc.h"
#include <math.h>

ContourTracer::ContourTracer(int maximumRetraceSteps1){
	maximumRetraceSteps = maximumRetraceSteps1;

}

std::vector<Point*>* ContourTracer::GetContourPoints(BinaryMap* contourMap1){
	contourMap = contourMap1;
	contourPoints = new std::vector<Point*>;
	Process();
	return contourPoints;

}

int ContourTracer::Width(){

	return contourMap->Width;
}

int ContourTracer::Height(){
	return contourMap->Height;

}

int ContourTracer::ResultCount(){
	int a =0;
	std::vector<Point*>::iterator iter;
	for (iter = contourPoints->begin(); iter< contourPoints->end();iter++) {
		a++;
	}

	return a;

}

Point* ContourTracer::FindFirstPoint(){
	int width = Width();
	int height = Width();
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (IsContourPoint(x, y))
			{
				return new Point(x, y, 0);
			}
		}
	}
	return NULL;

}

bool ContourTracer::IsContourPoint(int x, int y){
	return contourMap->IsSet(x, y);

}

bool ContourTracer::IsAllowed(int x, int y){
	std::vector<Point*>::iterator iter;
	Point* p;
	for (iter = contourPoints->begin()+std::max(0,ResultCount() - maximumRetraceSteps);iter<contourPoints->end();iter++) {
		p = (Point*)*iter;
		if (p->x == x && p->y == y)
		{
			return false;
		}
	}
	
	return true;

}

bool ContourTracer::IsSetAndAllowed(int x, int y){
	return contourMap->IsSet(x, y) && IsAllowed(x, y);

}

Point* ContourTracer::GetNextPoint(Point* p){
	int x;
	int y;
	std::vector<Point*>::iterator iter;
	PointRotation pntrot = PointRotation();
	Point* pnt;
	for (iter = pntrot.points->begin();iter < pntrot.points->end(); iter++)
	{
		pnt = (Point*)*iter;
		x = (int)(p->x + pnt->x);
		y = (int)(p->y + pnt->y);
		if (IsSetAndAllowed(x, y))
		{
			return new Point(x, y, p->z);
		}
	}
	return 0;

}

void ContourTracer::Process(){
	Point* firstPoint = FindFirstPoint();
	Point* currentPoint = firstPoint;
	contourPoints->push_back(currentPoint);
	int retraceCount = 0;
	pointfunctions pntfnc;
	//TODO: Find better stop condition
	while (retraceCount < maximumRetraceSteps && ResultCount() <= 1500 && !(ResultCount() > 10 && pntfnc.distance(currentPoint, firstPoint) < 2))
	{
		Point* nextPoint = GetNextPoint(currentPoint);
		if (nextPoint != NULL)
		{
			retraceCount = 0;
			contourPoints->push_back(nextPoint);
			currentPoint = nextPoint;
		}
		else
		{
			currentPoint = contourPoints->at(std::max(0, ResultCount() - retraceCount - 1));
			retraceCount++;
		}
	}
	contourPoints->push_back(firstPoint);
}




PointRotation::PointRotation(){
	points = new std::vector<Point*>;
	points->push_back(new Point(1, 0, 0));
	points->push_back(new Point(1, 1, 0));
	points->push_back(new Point(0, 1, 0));
	points->push_back(new Point(-1, 1, 0));
	points->push_back(new Point(-1, 0, 0));
	points->push_back(new Point(-1, -1, 0));
	points->push_back(new Point(0, -1, 0));
	points->push_back(new Point(1, -1, 0));


}