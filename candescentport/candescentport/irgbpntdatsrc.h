#ifndef IRGBPNTDATSRC_H
#define IRGBPNTDATSRC_H
#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "idatasource.h"


class IRGBPointerDataSource : public IDataSourceT<XnRGB24Pixel*>
{
public:
	int Width;
	int Height;
};


#endif 