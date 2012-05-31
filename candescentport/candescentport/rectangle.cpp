#include "rectangle.h"	






	void rectfnc::set(rectdata* dest, point* location, sizedat* size){
		dest->location.x = location->x;
		dest->location.y = location->y;
		dest->location.z = location->z;
		dest->size.Height = size->Height;
		dest->size.Width = size->Width;
	}
	void rectfnc::set(rectdata* dest, unsigned short x, unsigned short y, float width, float height){
		dest->location.x = x;
		dest->location.y = y;
		dest->location.z = 0;
		dest->location.angle = 0.0f;
		dest->size.Height = height;
		dest->size.Width = width;
	}
	bool rectfnc::Contains(rectdata* dest, point * p){
		return (p->x >= dest->location.x && p->y >= dest->location.y && p->x <= dest->location.x + dest->size.Width && p->y <= dest->location.y + dest->size.Height);
	}
	bool rectfnc::Equals(rectdata* dest, rectdata* test){
		
		if ((pntfnc.Equals(&test->location,&dest->location))&&(szfnc.Equals(&dest->size,&test->size))) {
			return true;
		}
		return false;
	}








