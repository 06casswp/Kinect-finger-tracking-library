#ifndef DEPTHPNTDATSRC_H
#define DEPTHPNTDATSRC_H

#include "idepthpntdatsource.h"
#include "intsize.h"
#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "datasourcebase.h"


class DepthPointerDataSource : public DataSourceBase<int*, xn::DepthGenerator>, IDepthPointerDataSource
{
public:
	DepthPointerDataSource(xn::DepthGenerator generator);

	void InternalRun();

	intsize Size();

	int MaxDepth();
};




#endif 