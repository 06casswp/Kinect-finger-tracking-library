#ifndef RGBPNTDATSRC_H
#define RGBPNTDATSRC_H

#include "irgbpntdatsrc.h"

class RGBPointerDataSource : public DataSourceBase<const XnUInt8*, xn::ImageGenerator*>, public IRGBPointerDataSource 
{
public:
	RGBPointerDataSource(xn::ImageGenerator* generator)
		: DataSourceBase(generator){};

	void InternalRun(){
		data = generator->GetImageMap();
		OnNewDataAvailable(data);
	}

	int Width();

	int Height();

};







#endif 