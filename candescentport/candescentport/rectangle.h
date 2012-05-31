#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point.h"
#include "size.h"

struct rectdata
{
	point location;
	sizedat size;

};

class rectfnc
{
public:
	pointman pntfnc;
	sizefnc szfnc;
	void set(rectdata* dest, point* location, sizedat* size);
	void set(rectdata* dest, unsigned short x, unsigned short y, float width, float height);
	bool Contains(rectdata* dest, point * p);
	bool Equals(rectdata* dest, rectdata* test);



};



#endif 