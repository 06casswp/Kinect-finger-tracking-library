#include "sysrect.h"

sysrect::sysrect(int x, int y, int width1, int height1) {
	X = x;
	Y = y;
	width = width1;
	height = height1;

}

bool sysrect::contains(int x, int y){

	return (((x>X)&&(x<X+width))&&((y>Y)&&(y<Y+height)));



}