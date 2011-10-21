#ifndef CONTEXTDAT_H
#define CONTEXTDAT_H

#include <vector>
#include "ImageData.h"
#include "idatasource.h"

template <typename T> class ContextDataSourceBase : public IDataSourceT<T>
{
public:
	std::vector<void*>* imagedataptr;
	ContextDataSourceBase();
	ImageDat* imdat;
	void addImageData(void* imdat);
	void onnewdataavailable(void* imdat);


};


#endif 