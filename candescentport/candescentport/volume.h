#ifndef VOLUME_H
#define VOLUME_H

#include "Point.h"
class volume
{
public:
	Point* location;
	float width;
	float height;
	float depth;


	volume(float x, float y, float z, float width, float height, float depth);
	volume(Point* location, float width, float height, float depth);
	//volume();
	bool contains(int x, int y, int z);
	float X();
	float Y();
	float Z();





};

#endif 