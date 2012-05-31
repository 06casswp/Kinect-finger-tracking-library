#include "ImageData.h"

ImageDat::ImageDat(const unsigned short * depthpointer1, const XnUInt8 * rgbpointer1) {
	depthPointer = depthpointer1;
	rgbPointer = rgbpointer1;
}