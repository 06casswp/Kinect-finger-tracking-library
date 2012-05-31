#ifndef VOLUME_H
#define VOLUME_H

#include "point.h"


struct volumedat
{
	point location;
	float width;
	float height;
	float depth;

};

class volumefnc
{
public:
	bool contains(volumedat* vol, unsigned short x, unsigned short y, unsigned short z);
	void set(volumedat* vol, unsigned short x, unsigned short y, unsigned short z, float width, float height, float depth);
	void set(volumedat* vol, point* location, float width, float height, float depth);
	void reset(volumedat* vol);
};





#endif 