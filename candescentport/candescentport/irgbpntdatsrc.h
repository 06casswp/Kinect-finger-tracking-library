#ifndef IRGBPNTDATSRC_H
#define IRGBPNTDATSRC_H
#include <XnCppWrapper.h>

#include "idatasource.h"


class IRGBpointerDataSource : public IDataSourceT<XnRGB24Pixel*>
{
public:
	int Width;
	int Height;
};


#endif 