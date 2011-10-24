#include "depthpntdatsrc.h"	


DepthPointerDataSource::DepthPointerDataSource(xn::DepthGenerator* generator)
		: DataSourceBase(generator){
			xn::DepthMetaData metaDat;
			bool check = generator->IsValid();
			generator->GetMetaData(metaDat);
			Size = new intsize(metaDat.XRes(),metaDat.YRes());
			MaxDepth = generator->GetDeviceMaxDepth();

	}