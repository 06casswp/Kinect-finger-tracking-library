#ifndef ICLUSTDATSRC_H
#define ICLUSTDATSRC_H


#include "clusters.h"
#include "size.h"
#include "idatasource.h"

class IClusterDataSource : public IDataSourceT <clusterdat **>
{
public:
	sizedat* Size;
};

#endif 