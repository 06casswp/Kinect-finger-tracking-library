#ifndef IMAGEDAT_H
#define IMAGEDAT_H



#include <XnCppWrapper.h>



class ImageDat
{
public:
	const XnDepthPixel * depthPointer;
	const XnUInt8 * rgbPointer;
	ImageDat(const XnDepthPixel * depthPointer, const XnUInt8 * rgbPointer);
};


#endif 