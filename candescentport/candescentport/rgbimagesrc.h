#ifndef RGBIMGSRC_H
#define RGBIMGSRC_H

#include "sysrect.h"
#include "irgbpntdatsrc.h"
#include "Iimagesource.h"
#include "rgbimagefact.h"
#include "bitmap.h"

class RGBImageSource: public IImageSource
{
public:
	sysrect* area;
	RGBImageFactory* imageFactory;

	RGBImageSource(IRGBPointerDataSource* dataSource);

	int Width;

	int Height;

	bitmap Process(int* sourceData);


	bitmap ProcessUnsafe(int* sourceData);
};

#endif 