#include "ImageData.h"

ImageDat::ImageDat(const unsigned short * depthPointer, const XnUInt8 * rgbPointer) {
	ImageDat::depthPointer = depthPointer;
	ImageDat::rgbPointer = rgbPointer;
}