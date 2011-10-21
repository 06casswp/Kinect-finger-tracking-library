#ifndef ICLUSTDATSRC_H
#define ICLUSTDATSRC_H


#include "clusterdata.h"
#include "intsize.h"
#include "idatasource.h"

class IClusterDataSource : public IDataSourceT <ClusterData*>
{
public:
	intsize* Size;
};

#endif 