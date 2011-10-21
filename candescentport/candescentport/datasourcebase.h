#ifndef DATASRCCLA_H
#define DATASRCCLA_H

#include <XnCppWrapper.h>
#include "XnVNite.h"
#include "contextdatasourcebase.h"
//#include "ImageData.h"

template <typename TValue, class TGenerator> class DataSourceBase : public IDataSourceT<typename TValue>
{
public:
	TValue data;
	TGenerator generator;
	DataSourceBase<TValue, TGenerator>(TGenerator generator1){
		generator = generator1;
		
	}






};

#endif 