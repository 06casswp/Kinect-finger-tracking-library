#ifndef IDATSRCFACT_H
#define IDATSRCFACT_H


#include "Iimagesource.h"
#include "iclusterdatasrc.h"
#include "clusterdatasrcsets.h"
#include "OpenNIDataSourceFactory.h"

class IDataSourceFactory{
public:
	OpenNIDataSourceFactory* openni;
	IImageSource* rgbimagesrc;
	IImageSource* depthimagesrc;
	IClusterDataSource* iclustersrc;

	IDataSourceFactory();
	IDataSourceFactory(ClusterDataSourceSettings* clusterDataSourceSettings);

};

#endif