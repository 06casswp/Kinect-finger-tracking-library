#ifndef HANDATSRC_H
#define HANDATSRC_H

#include "../size.h"
#include "../clusters.h"
#include "IHandDataSource.h"
#include "HandCollection.h"
#include "HandDataSourceSettings.h"
#include "HandDataFactory.h"
#include "../datasourceprocessor.h"
#include "../iclusterdatasrc.h"
#include "../clusterdatasrc.h"
#include "DistanceMap2.h"


class HandDataSource
{
public:
	
	HandDataSourceSettings settings;

	HandDataFactory factory;

	HandCollection handcoll;

	sizedat Size;

	DistanceMap2a map;
	HandData** results;

	int Width();

	int Height();

	void start();
	int resultcount;
	HandCollection* Process(clusterdat** ClusterData1,sizedat* size, int count);
	HandDataSource();
};

#endif 