#include "contextdatasourcebase.h"

template <typename TValue> ContextDataSourceBase<TValue>::ContextDataSourceBase():IDataSource<TValue>{
	imagedataptr = new std::vector<void*>;



}
template <typename TValue> void ContextDataSourceBase<TValue>::addImageData(void* pnt){

	imagedataptr->push_back(pnt);

}

template <typename TValue> void ContextDataSourceBase<TValue>::onnewdataavailable(void* imdat){





}