
#include "volume.h"


volume::volume(float x, float y, float z, float width, float height, float depth){
	location->x = x;
	location->y = y;
	location->z = z;
	width = width;
	height = height;
	depth = depth;



}
volume::volume(Point* location, float width, float height, float depth){
	location = location;
	width = width;
	height = height;
	depth = depth;


}

/*volume::volume(){
	volume::location.x = 0;
	volume::location.y = 0;
	volume::location.z = 0;
	volume::width = 0;
	volume::height = 0;
	volume::depth = 0;



}
*/
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


