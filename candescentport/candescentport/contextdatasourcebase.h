#ifndef CONTEXTDAT_H
#define CONTEXTDAT_H

#include <vector>
#include "ImageData.h"
#include "idatasource.h"


template <typename T> class ContextDataSourceBase : public IDataSourceT<T>
{
public:
	xn::Context* context;

	T data;
	bool run;
	bool IsRunning(){
		return false;
	}
	//std::vector<void*>* imagedataptr;
	ContextDataSourceBase(xn::Context* context);
	//ImageDat* imdat;
	//void addImageData(void* imdat);
	void OnNewDataAvailable(T);
	//event NewDataHandler<TValue> NewDataAvailable;
	void Start(){
		if (!IsRunning()){
			context->StartGeneratingAll();
			Run();
			AfterRun();
		}
	}
	void Stop(){
		
	}
	void Run(){
		context->WaitAndUpdateAll();
		InternalRun(); //internal run is in samples
		
	}
	void AfterRun(){
		context->StopGeneratingAll();
	}
	virtual void InternalRun();

	T CurrentValue(){
		return data;
	}
	

};


#endif 