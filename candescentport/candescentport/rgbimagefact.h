#ifndef RGBIMAGFACT_H
#define RGBIMAGFACT_H

#include "sysrect.h"
#include "bitmap.h"
#include <XnCppWrapper.h>
#include "XnVNite.h"

class RGBImageFactory
{
public:
	bitmap* target;
	sysrect* area;
	unsigned short min, max;
	RGBImageFactory(bitmap* target1, sysrect* area1);
	//RGBImageFactory(sysrect* area1);
	void CreateRgbImage(XnRGB24Pixel* pointer);
	void WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B);
	char Adjust(double color, double factor);
};


#endif