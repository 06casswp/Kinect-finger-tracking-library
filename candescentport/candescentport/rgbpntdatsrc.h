#ifndef RGBPNTDATSRC_H
#define RGBPNTDATSRC_H

#include "irgbpntdatsrc.h"

class RGBPointerDataSource : public DataSourceBase<int*, xn::ImageGenerator>, IRGBPointerDataSource 
{
public:
	RGBPointerDataSource(xn::ImageGenerator generator)
		: DataSourceBase(generator){};

	void InternalRun();

	int Width();

	int Height();

};







#endif 