#include "ContourFactory.h"


ContourFactory::ContourFactory(float lineThinningDistance, int maximumRetraceSteps){
	scanner = new ContourScanner();
	tracer = new ContourTracer(maximumRetraceSteps);
	thinner = new LineThinner(lineThinningDistance, false);
}

Contour* ContourFactory::CreateContour(BinaryMap* map, float left, float top){
	if (map->FillRate() < 0.01) 
	{
		return new Contour();
	}
	BinaryMap* binaryMap = scanner->Scan(map);
	std::vector<Point*>* points = Translate(tracer->GetContourPoints(binaryMap), (int)left, (int)top);
	points = thinner->Filter(points);
	return new Contour(points);



}

std::vector<Point*>* ContourFactory::Translate(std::vector<Point*>* points, int deltaX, int deltaY){
	std::vector<Point*>::iterator iter;
	std::vector<Point*>* output = new std::vector<Point*>;
	Point* p;
	Point* p1;
	for (iter = points->begin();iter<points->end();iter++) {
		p = (Point*)*iter;
		p1 = new Point(p->x + deltaX, p->y + deltaY, p->z);
		output->push_back(p1);
	}

	return output;
}