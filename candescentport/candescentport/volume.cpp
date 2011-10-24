
#include "volume.h"


volume::volume(float x, float y, float z, float width, float height, float depth){
	location = new Point(x,y,z);
	width = width;
	height = height;
	depth = depth;



}
volume::volume(Point* location1, float width, float height, float depth){
	location = location1;
	width = width;
	height = height;
	depth = depth;


}

volume::volume(){
	location = new Point(0,0,0);

	width = 0;
	height = 0;
	depth = 0;



}

bool volume::contains(int x, int y, int z){
	return (x >= location->x && x <= location->x + width && y >= location->y && y <= location->y + height && z >= location->z && z <= location->z + depth);
}

	float volume::X(){
		return location->x;


	}
	float volume::Y(){
		return location->y;


	}
	float volume::Z(){
		return location->z;


	}


