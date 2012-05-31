
#include "volume.h"



	bool volumefnc::contains(volumedat* vol, unsigned short x, unsigned short y, unsigned short z){
		return (x >= vol->location.x && x <= vol->location.x + vol->width && y >= vol->location.y && y <= vol->location.y + vol->height && z >= vol->location.z && z <= vol->location.z + vol->depth);


	}
	void volumefnc::set(volumedat* vol, unsigned short x, unsigned short y, unsigned short z, float width, float height, float depth){
		vol->depth = depth;
		vol->height = height;
		vol->width = width;
		vol->location.x = x;
		vol->location.y = y;
		vol->location.z = z;
		vol->location.angle = 0.0f;
	}
	void volumefnc::set(volumedat* vol, point* location, float width, float height, float depth){
		vol->depth = depth;
		vol->height = height;
		vol->width = width;
		vol->location.x = location->x;
		vol->location.y = location->y;
		vol->location.z = location->z;
		vol->location.angle = location->angle;
	}
	void volumefnc::reset(volumedat* vol){
		vol->width = 0;
		vol->height = 0;
		vol->depth = 0;
		vol->location.x = 0;
		vol->location.y = 0;
		vol->location.z = 0;
		vol->location.angle = 0.0f;
	}




