#include "depthpntdatsrc.h"	


DepthpointerDataSource::DepthpointerDataSource(xn::DepthGenerator* generator)
		: DataSourceBase(generator){
			xn::DepthMetaData metaDat;
			
			
			generator->GetMetaData(metaDat);
			Size.Height = metaDat.XRes();
			Size.Width = metaDat.YRes();
			MaxDepth = generator->GetDeviceMaxDepth();

	}