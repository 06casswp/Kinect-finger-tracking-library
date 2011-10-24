#ifndef DEPTHPNTDATSRC_H
#define DEPTHPNTDATSRC_H

#include "idepthpntdatsource.h"
#include "intsize.h"
#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "datasourcebase.h"


class DepthPointerDataSource : public DataSourceBase<const XnDepthPixel*, xn::DepthGenerator*>, public IDepthPointerDataSource
{
public:
	DepthPointerDataSource(xn::DepthGenerator* generator);

	void InternalRun(){
		data = generator->GetDepthMap();
		OnNewDataAvailable(data);
	}



	int MaxDepth;
		 
	
};




#endif 