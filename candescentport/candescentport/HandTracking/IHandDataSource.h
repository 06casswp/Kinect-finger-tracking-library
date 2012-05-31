#ifndef IHANDDATASRC_H
#define IHANDDATASRC_H

#include "../size.h"
#include "HandCollection.h"
#include "../idatasource.h"


class IHandDataSource : public IDataSourceT<HandCollection>
{
public:
	int Width;

	int Height;

	sizedat Size;
};

#endif 