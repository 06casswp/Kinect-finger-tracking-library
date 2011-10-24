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
	bool run;
	DataSourceBase<TValue, TGenerator>(TGenerator generator1){
		generator = generator1;
		
		
	}

	bool IsRunning(){
		return run;


	}
	TValue CurrentValue(){
		return data;


	}
	void Start(){
		if (!IsRunning()){
			generator->StartGenerating();
			Run();
			AfterStop();
		}

		
	}
	void Stop(){
		

	}
	void Run(){
		generator->WaitAndUpdateData();
		InternalRun();


	}
	void AfterStop(){
		generator->StopGenerating();

	}
	void OnNewDataAvailable(TValue newData){
		//this is where we output data
		
	}

	virtual void InternalRun() = 0;


};

#endif 