#ifndef DATSRCPROCESS_H
#define DATSRCPROCESS_H
#include "idatasource.h"
template <class TValue, class TSourceData> class DataSourceProcessor: public IDataSourceT<TValue>
{
public:
	IDataSourceT<TSourceData>* dataSource;
	TValue data;

	DataSourceProcessor<TValue,TSourceData>(IDataSourceT<TSourceData>* dataSource1){
				            dataSource = dataSource1;
            //dataSource->NewDataAvailable += new NewDataHandler<TSourceData>(dataSource_NewDataAvailable);
	}



	bool IsRunning;

	TValue CurrentValue;

	void dataSource_NewDataAvailable(TSourceData sourceData);

	TValue Process(TSourceData sourceData);

};

#endif 