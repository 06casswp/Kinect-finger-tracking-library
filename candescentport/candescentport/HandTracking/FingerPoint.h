#ifndef FINGERpoint_H
#define FINGERpoint_H

#include "..\point.h"


class Fingerpoint 
{
public:
	point *location;

	void set(point* location);

	int Id;

	float X();

	float Y();

	float Z();


};

#endif 