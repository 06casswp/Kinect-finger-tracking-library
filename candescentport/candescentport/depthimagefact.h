#ifndef DEPTHIMAGFACT_H
#define DEPTHIMAGFACT_H


#include "bitmap.h"
#include "sysrect.h"
#include "histogram.h"
class DepthImageFactory
{
public:
	bitmap* target;
	sysrect* area;
	Histogram* histogram;
	unsigned short min, max;
	DepthImageFactory(bitmap* target1, Histogram* histogram1, sysrect* area1);

	void CreateDepthImage(int* pointer, int width, int height);


	void CreateHistogram(int* sourceData);

	void WavelengthToRGB(double wavelength, unsigned char* R,unsigned char* G,unsigned char* B);
	char Adjust(double color, double factor);
};

#endif