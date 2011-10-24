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
#include "../clusterdatasrc.h"


class HandDataSource : public IHandDataSource//, public DataSourceProcessor<HandCollection*, ClusterData*>,
{
public:
	
	HandDataFactory* factory;

	HandCollection* CurrentValue;

	HandDataSource(ClusterDataSource* clusterDataSource);

	HandDataSource(intsize* size1,/*ClusterDataSource* clusterDataSource, */HandDataSourceSettings* settings);

	int Width();

	int Height();



	HandCollection* Process(ClusterData* clusterData1);
};

#endif 