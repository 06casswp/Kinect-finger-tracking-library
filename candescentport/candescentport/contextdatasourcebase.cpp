#include "contextdatasourcebase.h"

template <typename T> ContextDataSourceBase<T>::ContextDataSourceBase(xn::Context* context1):IDataSource<T>{
	//imagedataptr = new std::vector<void*>;

	context = context1;
	actionRunner = new ActionRunner(&Run,&AfterRun);

}
/*
template <typename TValue> void ContextDataSourceBase<TValue>::addImageData(void* pnt){

	imagedataptr->push_back(pnt);

}
*/

template <typename T> void ContextDataSourceBase<T>::OnNewDataAvailable(T){


//printf("last part");
int a = 1+5+imdat[0];

}
/*
template <typename TValue> void ContextDataSourceBase<TValue>::Start()
        {
            if (!IsRunning)
            {
                //context.StartGeneratingAll();
                //actionRunner.Start();
            }
        }

		*/