#include "bitmap.h"
#include <stdlib.h>
bitmap::bitmap(int width1, int height1){
	width = width1;
	height = height1;
	red = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	green = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
	blue = (unsigned char*)malloc(sizeof(unsigned char)*width*height);
}