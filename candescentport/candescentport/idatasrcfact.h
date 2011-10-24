#ifndef IDATSRCFACT_H
#define IDATSRCFACT_H


#include "Iimagesource.h"
#include "iclusterdatasrc.h"
#include "clusterdatasrcsets.h"


class IDataSourceFactory{
public:

	IImageSource* CreateRGBImageDataSource();
	IImageSource* CreateDepthImageDataSource();


	IClusterDataSource* CreateClusterDataSource();
	IClusterDataSource* CreateClusterDataSource(ClusterDataSourceSettings* clusterDataSourceSettings);

};

#endif