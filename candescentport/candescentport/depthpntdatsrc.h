#ifndef DEPTHPNTDATSRC_H
#define DEPTHPNTDATSRC_H

#include "idepthpntdatsource.h"
#include "size.h"
#include <XnCppWrapper.h>
#include "datasourcebase.h"


class DepthpointerDataSource : public DataSourceBase<const XnDepthPixel*, xn::DepthGenerator*>, public IDepthpointerDataSource
{
public:
	DepthpointerDataSource(xn::DepthGenerator* generator);

	void InternalRun(){
		data = generator->GetDepthMap();
		OnNewDataAvailable(data);
	}



	int MaxDepth;
		 
	
};




#endif 