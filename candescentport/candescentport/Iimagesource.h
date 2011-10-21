#ifndef IIMAGESRC_H
#define IIMAGESRC_H


#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "idatasource.h"
#include "bitmap.h"

class IImageSource : public IDataSourceT<bitmap*>
{
public:
	int Width;
	int Height;
	


};


#endif 