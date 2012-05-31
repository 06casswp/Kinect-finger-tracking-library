#ifndef RGBPNTDATSRC_H
#define RGBPNTDATSRC_H

#include "irgbpntdatsrc.h"

class RGBpointerDataSource : public DataSourceBase<const XnUInt8*, xn::ImageGenerator*>, public IRGBpointerDataSource 
{
public:
	RGBpointerDataSource(xn::ImageGenerator* generator)
		: DataSourceBase(generator){};

	void InternalRun(){
		data = generator->GetImageMap();
		OnNewDataAvailable(data);
	}

	int Width();

	int Height();

};







#endif 