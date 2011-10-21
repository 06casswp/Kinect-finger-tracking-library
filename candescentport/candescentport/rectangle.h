#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "size.h"
class Rectanglez
{
public:
	Point* location;
	Size* size;

	Rectanglez(Point* location, Size* size);
	Rectanglez(float x, float y, float width, float height);
	bool Contains(Point* p);
	bool Equals(void* p);
};

#endif 