#ifndef IHANDDATASRC_H
#define IHANDDATASRC_H

#include "../intsize.h"
#include "HandCollection.h"
#include "../idatasource.h"


class IHandDataSource : public IDataSourceT<HandCollection>
{
public:
	int Width;

	int Height;

	intsize* Size;
};

#endif 