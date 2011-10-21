#include "rectangle.h"	


Rectanglez::Rectanglez(Point* location1, Size* size1){
	location = location1;
	size = size1;


}
Rectanglez::Rectanglez(float x, float y, float width, float height){
	location = new Point(x, y, 0);
	size = new Size(width, height);


}
bool Rectanglez::Contains(Point* p){

	return (p->x >= location->x && p->y >= location->y && p->x <= location->x + size->Width && p->y <= location->y + size->Height);

}

bool Rectanglez::Equals(void* p) {
	Rectanglez* rec = (Rectanglez*)p;
	if ((rec->location->Equals((void*)&location))&&(rec->size->Equals((void*)size))) {
		return true;
	}
	return false;
}