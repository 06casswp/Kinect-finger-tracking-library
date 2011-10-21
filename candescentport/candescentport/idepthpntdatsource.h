#ifndef IDEPTHPNTDATSRC_H
#define IDEPTHPNTDATSRC_H


#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "intsize.h"
#include "idatasource.h"

class IDepthPointerDataSource : public IDataSourceT<int*>
{
public:

	intsize *Size;
	int MaxDepth;


};

#endif 