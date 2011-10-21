#ifndef HANDATSRC_H
#define HANDATSRC_H

#include "../intsize.h"
#include "../clusterdata.h"
#include "IHandDataSource.h"
#include "HandCollection.h"
#include "HandDataSourceSettings.h"
#include "HandDataFactory.h"
#include "../datasourceprocessor.h"
#include "../iclusterdatasrc.h"


class HandDataSource : public DataSourceProcessor<HandCollection*, ClusterData*>, public IHandDataSource
{
public:
	intsize* size;
	HandDataFactory* factory;

	HandCollection* CurrentValue;

	HandDataSource(IClusterDataSource* clusterDataSource);

	HandDataSource(IClusterDataSource* clusterDataSource, HandDataSourceSettings* settings);

	int Width();

	int Height();



	HandCollection* Process(ClusterData clusterData1);
};

#endif 