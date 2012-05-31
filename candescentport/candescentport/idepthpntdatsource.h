#ifndef IDEPTHPNTDATSRC_H
#define IDEPTHPNTDATSRC_H


#include <XnCppWrapper.h>

#include "size.h"
#include "idatasource.h"

class IDepthpointerDataSource : public IDataSourceT<const XnDepthPixel *>
{
public:

	sizedat Size;
	int MaxDepth;


};

#endif 